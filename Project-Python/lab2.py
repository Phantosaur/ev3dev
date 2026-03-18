#!/usr/bin/env python3
import time

from ev3dev2.motor import LargeMotor, OUTPUT_A 
from ev3dev2.motor import LargeMotor, OUTPUT_B
lm = LargeMotor(OUTPUT_A)
rm = LargeMotor(OUTPUT_B)

# 90 degree rotation
def turn90( sleep_time,storona):

    turn = 725
    if storona == "L" or storona == "l":
    
        lm.on_for_degrees(50,turn )
    else:
        rm.on_for_degrees(50,turn )
    time.sleep(sleep_time)
def putt(sleep_time,position):
    lm = LargeMotor(OUTPUT_A)
    rm = LargeMotor(OUTPUT_B)
    lm.on_for_seconds(50, position,1,0)
    rm.on_for_seconds(50, position,1,1)
    time.sleep(sleep_time)

# Return to 0 degrees
time_hod =2
putt(0.001,time_hod)
turn90(1,"l")
putt(0.001,time_hod)
turn90(1,"l")
putt(0.001,time_hod)
turn90(1,"l")
putt(0.001,time_hod)
turn90(1,"r")
putt(0.001,time_hod)
turn90(1,"r")
putt(0.001,time_hod)
turn90(1,"r")
putt(0.001,time_hod)