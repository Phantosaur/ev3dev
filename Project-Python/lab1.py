#!/usr/bin/env python3 
from ev3dev2.led import Leds
import time
import random

from ev3dev2.button import Button
led=Leds()
led.all_off() # Turn all LEDs off
time.sleep(1)
but = Button()
mybutt=""
mini_level=[]
show=1
myvib=0
butt = ["up","down","left","right"]
def up(time1):
    led.set_color("LEFT", "GREEN")
    led.set_color("RIGHT", "GREEN")
    time.sleep(time1)
    led.all_off()
def down(time1):
    led.set_color("LEFT", "RED")
    led.set_color("RIGHT", "RED")
    time.sleep(time1)
    led.all_off()
def left(time1):
    led.set_color("LEFT", "RED")
    led.set_color("LEFT", "GREEN")
    time.sleep(time1)
    led.all_off()
def right(time1):
    led.set_color("RIGHT", "GREEN")
    led.set_color("RIGHT", "RED")
    time.sleep(time1)
    led.all_off()
def showbut(butt,time1):
    if butt =="left":
        left(time1)
    elif butt =="right":
        right(time1)
    elif butt =="up":
        up(time1)
    elif butt =="down":
        down(time1)


for i in range(5):
    mini_level.append(random.choice(butt))
for i in range(len(mini_level)):
    if (show):
        for j in range(len(mini_level)):
            showbut(mini_level[j],2)
        show =0
    while(1):
        
        if but.Up:
            showbut("up",2)
            if 
        

        


if mini_level == mybutt:
    led.set_color("RIGHT", "GREEN")
    led.set_color("LEFT", "RED")
time.sleep(10)

        





    
    
        

        

