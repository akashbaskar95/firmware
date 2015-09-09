#!/usr/bin/python

'''
@file       test-serial.py
@author     Pere Tuset-Peiro  (peretuset@openmote.com)
@version    v0.1
@date       May, 2015
@brief      

@copyright  Copyright 2015, OpenMote Technologies, S.L.
            This file is licensed under the GNU General Public License v2.
'''

import serial
import struct
import os

def program():
    ser = serial.Serial(port     = '/dev/ttyO1',
                        baudrate = 115200,
                        parity   = serial.PARITY_NONE,
                        stopbits = serial.STOPBITS_ONE,
                        bytesize = serial.EIGHTBITS,
                        xonxoff  = False,
                        rtscts   = False,
                        dsrdtr   = False)
                        
    
    buff = list()
    while(True):
        data = struct.unpack("1b", ser.read(1))[0]
        c = chr(data)
        if (c == '\n'):
	    print(''.join(buff))
            buff = list()
        else:
            buff.append(c)

def main():
    program()
    
if __name__ == "__main__":
    main()
