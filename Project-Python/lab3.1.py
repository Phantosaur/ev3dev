#!/usr/bin/env python3
import time
import math
from ev3dev2.motor import MoveTank, OUTPUT_A, OUTPUT_B

tank_pair = MoveTank(OUTPUT_A, OUTPUT_B)
def moveEnc(long,speed=50):
    tank_pair.on_for_rotations(speed, speed, 1.0/30.0*long)
def turnEnc(angle,speed=50):
    k= 1.0/44
    if (angle>0):
        tank_pair.on_for_rotations(-speed, speed, k*angle/2)
    else:
        tank_pair.on_for_rotations(speed, -speed, k*angle/2)

angle =-90
longl =440
longm =200
turnEnc(-angle)
moveEnc(longm)
turnEnc(-angle)
moveEnc(longl)
turnEnc(-angle)
moveEnc(longm)
turnEnc(-angle)
moveEnc(longl)
turnEnc(2*angle)

time.sleep(1)
     
