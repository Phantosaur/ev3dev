#!/usr/bin/env python3

import time
import math
from ev3dev2.motor import MoveTank, OUTPUT_A, OUTPUT_B
from ev3dev2.display import Display
lcd = Display()
tank_pair = MoveTank(OUTPUT_A, OUTPUT_B)
def moveEnc(long,speed=50):
    tank_pair.on_for_rotations(speed, speed, long*2/(math.pi*(3**2)))
def turnEnc(angle,speed=50):
    k= 1.0/44
    if (angle>0):
        tank_pair.on_for_rotations(-1*speed, speed, k*angle/2)
    else:
        tank_pair.on_for_rotations(speed,-1*speed, -k*angle/2)
def turnEnverse(angle, enverse: bool = False, speed=50):
    if enverse:
        turnEnc(-angle,speed)
    else:
        turnEnc(angle,speed)
def elmove(long1,long2, storona: bool = False, speed = 50):
    if storona:
        moveEnc(long1,speed)
    else:
        moveEnc(long2,speed)
def obezd( storona: bool,speed):
    angle = 90
    move =60 
    turnEnverse(angle,storona,speed)
    moveEnc(move)
    turnEnverse(-angle,storona,speed)
    moveEnc(move)
    turnEnverse(-angle,storona,speed)
    moveEnc(move)
    turnEnverse(angle,storona,speed)

angle =-90
longl =220
longm =100
longob =90
stor =0
# turnEnc(angle)
# moveEnc(longm)
# turnEnc(-angle)
# moveEnc(90)
# turnEnc(-angle)
# moveEnc(longm)
# turnEnc(-angle)
# moveEnc(longl)
# turnEnc(-2*angle)
# time.sleep(1)

turnEnverse(angle,stor)
elmove(longm,longl,stor)
turnEnverse(-angle,stor)
elmove(longl,longm,stor)
turnEnverse(-angle,stor)
elmove(longm,longl,stor)
turnEnverse(-angle,stor)
elmove(longl,longm,stor)
turnEnverse(-angle,stor)
time.sleep(1)


