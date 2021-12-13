import cv2 
# from image_processing import palette
import serial
import time

# xy_pos = (0, 0)

arduino = serial.Serial(port = '/dev/cu.usbmodem1101', baudrate=9600, timeout=1)
# time.sleep(2)

def check_for_ok():
    while True:
        r = arduino.readline()
        decoded = r.decode()
        if (decoded == "ok") or (decoded == "ok\r") or (decoded == "ok\n") or (decoded == "ok\r\n"):
            print("ok")
            time.sleep(1)
            break

def home():
    print("home")
    # move x and y to (0,0) for calibration purposes
    arduino.write(str.encode("G28\r", "ascii"))
    check_for_ok()

def z_up():
    print('z_up')
    # move z to up position
    arduino.write(str.encode("G01 Z950\r", "ascii"))
    check_for_ok()

def z_down():
    print("z_down")
    # move z to down position
    arduino.write(str.encode("G01 Z1400\r", "ascii"))
    check_for_ok()

def refresh_feeder():
    print("refresh")
    # move feeder in
    arduino.write(str.encode("M411\r", "ascii"))
    check_for_ok()
    # move feeder out
    arduino.write(str.encode("M410\r", "ascii"))
    check_for_ok()

def go_to(xdest, ydest):
    destination = "G01 X{} Y{}".format(xdest, ydest)
    print("go to {}".format(destination))
    arduino.write(str.encode(destination+"\r", "ascii"))
    check_for_ok()

def change_succ(vstate):
    print("change succ!")
    if vstate == 0:
        destination = "M400"
    else:
        destination = "M401"
    arduino.write(str.encode(destination+"\r", 'ascii'))
    check_for_ok()
    time.sleep(.5)

def retrieve_mm(dest_color):
    print("retrieve {}".format(dest_color))
    # move xy to m&m
    go_to(dest_color[0], dest_color[1])
    # move z down to m&m
    z_down()
    # turn suction on
    change_succ(1)
    time.sleep(.5)
    # move z back up
    z_up()

def complete_pixel(pixel_x, pixel_y):
    print("complete pixel")
    # move to position of pixel
    go_to(pixel_x, pixel_y)
    # move z position down
    z_down()
    # turn off suction
    change_succ(0)
    time.sleep(1)
    # move z back up
    z_up()

def create_mm_image(path):
    home()
    dest_yellow = (180,0)
    dest_orange = (90,0)
    dest_red = (270,0)
    dest_brown = (0,0)
    pixels = cv2.imread("./result7.png")
    for (row_number, row) in enumerate(pixels):
        # print("this is array: ", array)
        counter = 0
        y_counter = 180
        for (column_number, pixel) in enumerate(row):
            pixel = (str(pixel))
            pixel_x = (column_number*70) + 200
            pixel_y = (row_number*70)+500#180
            if pixel == "[255 255 255]":
                print("255")
                dest = dest_yellow
            elif pixel == "[63 63 63]":
                print("63")
                dest = dest_brown
            elif pixel == "[91 91 91]":
                print("91")
                dest = dest_red

            elif pixel == "[127 127 127]":
                print("127")
                dest = dest_orange
            
            # get orange m&m
            retrieve_mm(dest)
            # home()
            complete_pixel(pixel_x-dest[0], pixel_y-dest[1])
            home()
            # refresh feeder twice to ensure Skittle is correctly refreshed
            refresh_feeder()
            time.sleep(1)

if __name__ == "__main__":
    x_dimension = 2
    y_dimension = 2
    original_image = "./images/result7.png"
    create_mm_image(original_image)