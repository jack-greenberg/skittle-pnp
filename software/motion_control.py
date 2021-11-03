"""
Arduino output: "ok\n"
Sprint 1: Move 3 skittles
Bed: 12"
Skittle width: 0.1435"
Skittle height: 0.0130
z distance to pick up skittle: h_head - 0.0130
"""

import serial
import time

arduino = serial.Serial(port = '/dev/cu.usbmodem1101', baudrate=9600, timeout=0)
time.sleep(2)

def move_xyz(xpos, ypos, zpos):
    while True:
        bytes = arduino.readline()
        decoded = float(bytes[0:len(bytes)-2].decode("utf-8"))
        if decoded == 'ok':
            destination = "G01 X{} Y{} Z{}\n".format(xpos, ypos, zpos)
            arduino.write(str.encode(destination))
            time.sleep(1)
            break

def change_succ(vstate):
    while True:
        bytes = arduino.readline()
        decoded = float(bytes[0:len(bytes)-2].decode("utf-8"))
        if decoded == 'ok':
            if vstate == 0:
                destination = "M400"
            else:
                destination = "M401"
            arduino.write(str.encode(destination))
            time.sleep(1)
            break

def move_skittle(xpos, ypos, xdest, ydest):
    # move to skittle x and y
    move_xyz(xpos, ypos, 0)

    # move down
    move_xyz(xpos, ypos, 1)

    # succ skittle
    change_succ(1)

    # move back up
    move_xyz(xpos, ypos, 0)

    # move to skittle destination x and y
    move_xyz(xdest, ydest, 0)

    # move down
    move_xyz(xdest, ydest, 1)

    # unsucc skittle
    change_succ(0)

    # move back up
    move_xyz(xdest, ydest, 0)

if __name__ == "__main__":
    # wait for initiation command?

    # skittles start at 0.5", 1.0", 1.5"

    # move first skittle
    xpos_s1, ypos_s1, xdest_s1, ydest_s1 = .5, 0, 2, 0
    move_skittle(xpos_s1, ypos_s1, xdest_s1, ydest_s1)

    # move second skittle
    xpos_s2, ypos_s2, xdest_s2, ydest_s2 = 1, 0, 2.5, 0
    move_skittle(xpos_s2, ypos_s2, xdest_s2, ydest_s2)

    # move third skittle
    xpos_s3, ypos_s3, xdest_s3, ydest_s3 = 1.5, 0, 3, 0
    move_skittle(xpos_s3, ypos_s3, xdest_s3, ydest_s3)

    # return to origin
    move_xyz(0, 0, 0)

    # xpos_return, ypos_return, zpos_return = 0, 0, 0