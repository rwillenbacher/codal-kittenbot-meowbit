/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef MEOWBIT_IO_H
#define MEOWBIT_IO_H

#include "CodalConfig.h"
#include "ZPin.h"

//
// Unique Pin number for each pin (synonymous with mbedos PinName)
//


//
// Component IDs for each pin.
// The can be user defined, but uniquely identify a pin when using the eventing APIs/
//


/*
    from kittenbot meowbit bootloader github
    100, 0x00, // PIN_A0 PA0
    101, 0x01, // PIN_A1 PA1
    151, 0x02, // PIN_D1 PA2
    150, 0x03, // PIN_D0 PA3
    102, 0x04, // PIN_A2 PA4
    50, 0x05, // PIN_BTN_DOWN = PB10 PA_5
    49, 0x06, // PIN_BTN_UP = PA05 PA_6
    47, 0x07, // PIN_BTN_LEFT = PA15 PA_7
    36, 0x08, // PIN_DISPLAY_DC = PC05 PA08
    60, 0x9, // PIN_JACK_TX = PA09
    152, 0x0A, // PIN_D2 PA10
    103, 0x10, // PIN_A3 PB0
    48, 0x12, // PIN_BTN_RIGHT = PC13 PB_2
    44, 0x13, // PIN_DISPLAY_BL = PC07 PB03
    13, 0x14, // PIN_LED = PC09 PB4
    55, 0x15, // PIN_LED1 = PC08 PB5
    2, 0x16, // PIN_ACCELEROMETER_SCL = PIN_D6
    3, 0x17, // PIN_ACCELEROMETER_SDA = PIN_D7
    65, 0x18, // PIN_JACK_SND = PA08 PB_8
    4, 0x19, // PIN_BTN_A = PB01 PB_9
    43, 0x1A, // PIN_DISPLAY_RST = PC04 PB10
    35, 0x1c, // PIN_DISPLAY_CS = PB12
    32, 0x1d, // PIN_DISPLAY_SCK = PB13
    33, 0x1e, // PIN_DISPLAY_MISO = PB14
    34, 0x1f, // PIN_DISPLAY_MOSI = PB15
    105, 0x20, // PIN_A5 PC0
    104, 0x20, // PIN_A4 PC0
    14, 0x22, // PIN_LIGHT PC2
    5, 0x23, // PIN_BTN_B = PB00 PC_3
    64, 0x24, // PIN_JACK_PWREN = PA07
    27, 0x25, // TEMPERATURE = PC5
    153, 0x26, // PIN_D3 PC6
    159, 0x27, // PIN_D9 PC7
    // external spi
    23, 0x2A, // PIN_SCK PC10
    18, 0x2B, // PIN_MISO PC11
    19, 0x2C, // PIN_MOSI PC12
    1, 0x2e, // PIN_ACCELEROMETER_INT = PC14
    51, 0x2F, // PIN_BTN_MENU = PC10 PC_15
*/



#define ID_PIN_P0           (DEVICE_ID_IO_P0 + 0)
#define ID_PIN_P1           (DEVICE_ID_IO_P0 + 1)
#define ID_PIN_P2           (DEVICE_ID_IO_P0 + 2)
#define ID_PIN_P3           (DEVICE_ID_IO_P0 + 3)
#define ID_PIN_P4           (DEVICE_ID_IO_P0 + 4)
#define ID_PIN_BUTTON_DOWN  (DEVICE_ID_IO_P0 + 5)
#define ID_PIN_BUTTON_UP    (DEVICE_ID_IO_P0 + 6)
#define ID_PIN_BUTTON_LEFT  (DEVICE_ID_IO_P0 + 7)
#define ID_PIN_DISP_DC      (DEVICE_ID_IO_P0 + 8)
#define ID_PIN_JACK_TX      (DEVICE_ID_IO_P0 + 9)
#define ID_PIN_SDA          (DEVICE_ID_IO_P0 + 10)
#define ID_PIN_P11          (DEVICE_ID_IO_P0 + 11)
#define ID_PIN_P12          (DEVICE_ID_IO_P0 + 12)
#define ID_PIN_P13          (DEVICE_ID_IO_P0 + 13)
#define ID_PIN_P14          (DEVICE_ID_IO_P0 + 14)
#define ID_PIN_P15          (DEVICE_ID_IO_P0 + 15)
#define ID_PIN_P16          (DEVICE_ID_IO_P0 + 16)
#define ID_PIN_P17          (DEVICE_ID_IO_P0 + 17)
#define ID_PIN_BUTTON_RIGHT (DEVICE_ID_IO_P0 + 18)
#define ID_PIN_DISP_BL      (DEVICE_ID_IO_P0 + 19)
#define ID_PIN_LED0         (DEVICE_ID_IO_P0 + 20)
#define ID_PIN_LED1         (DEVICE_ID_IO_P0 + 21)
#define ID_PIN_ACCL_SCL     (DEVICE_ID_IO_P0 + 22)
#define ID_PIN_ACCL_SDA     (DEVICE_ID_IO_P0 + 23)
#define ID_PIN_JACK_SND     (DEVICE_ID_IO_P0 + 24)
#define ID_PIN_BUTTON_A     (DEVICE_ID_IO_P0 + 25)
#define ID_PIN_DISP_RST     (DEVICE_ID_IO_P0 + 26)
#define ID_PIN_P27          (DEVICE_ID_IO_P0 + 27)
#define ID_PIN_DISP_CS      (DEVICE_ID_IO_P0 + 28)
#define ID_PIN_DISP_SCK     (DEVICE_ID_IO_P0 + 29)
#define ID_PIN_DISP_MISO    (DEVICE_ID_IO_P0 + 30)
#define ID_PIN_DISP_MOSI    (DEVICE_ID_IO_P0 + 31)
#define ID_PIN_P32          (DEVICE_ID_IO_P0 + 32)
#define ID_PIN_P33          (DEVICE_ID_IO_P0 + 33)
#define ID_PIN_LIGHT        (DEVICE_ID_IO_P0 + 34)
#define ID_PIN_BUTTON_B     (DEVICE_ID_IO_P0 + 35)
#define ID_PIN_JACK_PWREN   (DEVICE_ID_IO_P0 + 36)
#define ID_PIN_TEMPRATURE   (DEVICE_ID_IO_P0 + 37)
#define ID_PIN_P38          (DEVICE_ID_IO_P0 + 38)
#define ID_PIN_P39          (DEVICE_ID_IO_P0 + 39)
#define ID_PIN_P40          (DEVICE_ID_IO_P0 + 40)
#define ID_PIN_P41          (DEVICE_ID_IO_P0 + 41)
#define ID_PIN_EXT_SCK      (DEVICE_ID_IO_P0 + 42)
#define ID_PIN_EXT_MISO     (DEVICE_ID_IO_P0 + 43)
#define ID_PIN_EXT_MOSI     (DEVICE_ID_IO_P0 + 44)
#define ID_PIN_P45          (DEVICE_ID_IO_P0 + 45)
#define ID_PIN_ACCL_INT     (DEVICE_ID_IO_P0 + 46)
#define ID_PIN_BUTTON_MENU  (DEVICE_ID_IO_P0 + 47)

namespace codal
{
    /**
     * Represents a collection of all I/O pins exposed by the device.
     */
    class MeowbitIO
    {
        public:

            ZPin        buttonUp;
            ZPin        buttonDown;
            ZPin        buttonLeft;
            ZPin        buttonRight;
            ZPin        buttonA;
            ZPin        buttonB;
            
            ZPin        led0;
            ZPin        led1;

            ZPin        dispBl;
            ZPin        dispDc;
            ZPin        dispCs;
            ZPin        dispRst;
            
            ZPin        dispSck;
            ZPin        dispMiso;
            ZPin        dispMosi;

            ZPin        buzzer;

            /**
             * Constructor.
             */
            MeowbitIO();
    };
}

#endif
