import cv2 
from image_processing import palette
import serial
import time

# TODO: establish movement tracking with stepper motor steps

xy_pos = (0, 0)

arduino = serial.Serial(port = '/dev/cu.usbmodem1101', baudrate=9600, timeout=10)
time.sleep(2)

def calc_steps_needed(xy_current, dest):
    x_current = xy_current[0]
    y_current = xy_current[1]
    x_dest = dest[0]
    y_dest = dest[1]
    x_adjusted = x_dest - x_current
    y_adjusted = y_dest - y_current
    xy_adjusted = (x_adjusted, y_adjusted)
    return xy_adjusted

def go_to(xdest, ydest, zdest):
    global xy_pos
    xy_pos = (xy_pos[0], xy_pos[1])

    while True:
        bytes = arduino.readline()
        decoded = bytes[0:len(bytes)].decode("utf-8")
        # print(decoded)
        adjusted = calc_steps_needed(xy_pos, (xdest, ydest))
        destination = "G01 X{} Y{} Z{}\n".format(adjusted[0], adjusted[1], zdest)
        arduino.write(str.encode(destination))
        if decoded == 'ok':
            xy_pos = (adjusted[0], adjusted[1])
            break

def change_succ(vstate):
    while True:
        bytes = arduino.readline()
        decoded = bytes[0:len(bytes)].decode("utf-8")
        # print(decoded)
        if vstate == 0:
            destination = "M400"
        else:
            destination = "M401"
        arduino.write(str.encode(destination))
        #time.sleep(1)
        if decoded == 'ok':
            break

def retrieve_mm(dest_color):
    # move xy to m&m
    go_to(dest_color[0], dest_color[1], -80)
    # move z down to m&m
    go_to(dest_color[0], dest_color[1], 0)
    # turn suction on
    change_succ(1)
    # move z back up
    go_to(dest_color[0], dest_color[1], -80)

def create_mm_image(path):

    dest_yellow = (0,0)
    dest_orange = (0,0)
    dest_red = (0,0)
    dest_brown = (0,0)
    # make sure z starts in up position
    go_to(0, 0, -80)
    pixels = cv2.imread("./result7.png")
    for array in pixels:
        counter = 0
        # x_counter = 0
        y_counter = 0
        for pixel in array:
            pixel = (str(pixel))
            pixel_x = counter%x_dimension
            pixel_y = y_counter
            if pixel == "[255 255 255]":
                # move xy to yellow m&m
                retrieve_mm(dest_yellow)
                # move pixel_y down if row is complete
                if pixel_x == 0 and counter != 0:
                    y_counter+=1
                # move to position of pixel
                go_to(pixel_x, pixel_y, -80)
                # move z position down
                go_to(pixel_x, pixel_y, 0)
                # turn off suction
                change_succ(0)
                # move z back up
                go_to(pixel_x, pixel_y, -80)
                counter+=1

            elif pixel == "[63 63 63]":
                # get brown m&m
                retrieve_mm(dest_brown)
                # move pixel_y down if row is complete
                if pixel_x == 0 and counter != 0:
                    y_counter+=1
                # move to position of pixel
                go_to(pixel_x, pixel_y, -80)
                # move z position down
                go_to(pixel_x, pixel_y, 0)
                # turn off suction
                change_succ(0)
                # move z back up
                go_to(pixel_x, pixel_y, -80)
                counter+=1

            elif pixel == "[91 91 91]":
                # get red m&m
                retrieve_mm(dest_red)
                # move pixel_y down if row is complete
                if pixel_x == 0 and counter != 0:
                    y_counter+=1
                # move to position of pixel
                go_to(pixel_x, pixel_y, -80)
                # move z position down
                go_to(pixel_x, pixel_y, 0)
                # turn off suction
                change_succ(0)
                # move z back up
                go_to(pixel_x, pixel_y, -80)
                counter+=1

            elif pixel == "[127 127 127]":
                # get orange m&m
                retrieve_mm(dest_orange)
                # move pixel_y down if row is complete
                if pixel_x == 0 and counter != 0:
                    y_counter+=1
                # move to position of pixel
                go_to(pixel_x, pixel_y, -80)
                # move z position down
                go_to(pixel_x, pixel_y, 0)
                # turn off suction
                change_succ(0)
                # move z back up
                go_to(pixel_x, pixel_y, -80)
                counter+=1

if __name__ == "__main__":
    x_dimension = 100
    y_dimension = 100
    original_image = "./images/sample4.jpg"
    create_mm_image(original_image)
