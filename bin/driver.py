import pigpio
import time

pi = pigpio.pi()

RP_DIN1 = 4
RP_DIN2 = 12
RP_DIN3 = 14
RP_DIN4 = 17
RP_LE = 13
RP_CLK = 18
RP_POL = 27
RP_Boost = 22

def Initial():
    pi.set_mode(RP_DIN1, pigpio.OUTPUT)
    pi.set_mode(RP_DIN2, pigpio.OUTPUT)
    pi.set_mode(RP_DIN3, pigpio.OUTPUT)
    pi.set_mode(RP_DIN4, pigpio.OUTPUT)
    pi.set_mode(RP_LE, pigpio.OUTPUT)
    pi.set_mode(RP_CLK, pigpio.OUTPUT)
    pi.set_mode(RP_POL, pigpio.OUTPUT)
    pi.set_mode(RP_Boost, pigpio.OUTPUT)
    pi.write(RP_POL,1)
    pi.write(RP_DIN1,1)
    pi.write(RP_DIN2,1)
    pi.write(RP_DIN3,1)
    pi.write(RP_DIN4,1)
    pi.write(RP_CLK,0)
    pi.write(RP_LE,0)
    pi.write(RP_Boost,0)
    return()

def SendData(string):
    index = 5
    data = 0
    for i in string:
        if i == '0':
            seg = 0b1111111110
        elif i == '9':
            seg = 0b1111111101
        elif i == '8':
            seg = 0b1111111011
        elif i == '7':
            seg = 0b1111110111
        elif i == '6':
            seg = 0b1111101111
        elif i == '5':
            seg = 0b1111011111
        elif i == '4':
            seg = 0b1110111111
        elif i == '3':
            seg = 0b1101111111
        elif i == '2':
            seg = 0b1011111111
        elif i == '1':
            seg = 0b0111111111
        data = data + (seg<<(index*10+4))
        index -= 1
    data = data + 0xF
    for j in range(16):
        flag = 0x0000000000000001
        pi.write(RP_CLK,0)
        if (data & flag) == 1:
            pi.write(RP_DIN4,1)
        else:
            pi.write(RP_DIN4,0)
        data = data >> 1
        if (data & flag) == 1:
            pi.write(RP_DIN3,1)
        else:
            pi.write(RP_DIN3,0)
        data = data >> 1
        if (data & flag) == 1:
            pi.write(RP_DIN2,1)
        else:
            pi.write(RP_DIN2,0)
        data = data >> 1
        if (data & flag) == 1:
            pi.write(RP_DIN1,1)
        else:
            pi.write(RP_DIN1,0)
        data = data >> 1
        time.sleep(0.01)
        pi.write(RP_CLK,1)
        time.sleep(0.01)
        pi.write(RP_CLK,0)

def Latch():
    pi.write(RP_LE,1)
    time.sleep(0.01)
    pi.write(RP_LE,0)
    time.sleep(0.01)

Initial()
# SendData('223333')
# Latch()