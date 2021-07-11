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

/**
  * Class definition for Meowbit IO.
  * Represents a collection of all I/O pins on the device.
  */

#include "CodalConfig.h"
#include "MeowbitIO.h"

using namespace codal;

/**
  * Constructor.
  *
  * Create a representation of all given I/O pins
  *
  */
MeowbitIO::MeowbitIO() :
    buttonUp( ID_PIN_BUTTON_UP, PA_6, PIN_CAPABILITY_AD ),
    buttonDown( ID_PIN_BUTTON_DOWN, PA_5, PIN_CAPABILITY_AD ),
    buttonLeft( ID_PIN_BUTTON_LEFT, PA_7, PIN_CAPABILITY_AD ),
    buttonRight( ID_PIN_BUTTON_RIGHT, PB_2, PIN_CAPABILITY_AD ),
    buttonA( ID_PIN_BUTTON_A, PB_9, PIN_CAPABILITY_AD ),
    buttonB( ID_PIN_BUTTON_B, PC_3, PIN_CAPABILITY_AD ),
 
    led0( ID_PIN_LED0, PB_4, PIN_CAPABILITY_AD ),
    led1( ID_PIN_LED1, PB_5, PIN_CAPABILITY_AD ),

    dispBl( ID_PIN_DISP_BL, PB_3, PIN_CAPABILITY_AD ),
    dispDc( ID_PIN_DISP_DC, PA_8, PIN_CAPABILITY_AD ),
    dispCs( ID_PIN_DISP_CS, PB_12, PIN_CAPABILITY_AD ),
    dispRst( ID_PIN_DISP_RST, PB_10, PIN_CAPABILITY_AD ),

    dispSck( ID_PIN_DISP_SCK, PB_13, PIN_CAPABILITY_AD ),
    dispMiso( ID_PIN_DISP_MISO, PB_14, PIN_CAPABILITY_AD ),
    dispMosi( ID_PIN_DISP_MOSI, PB_15, PIN_CAPABILITY_AD ),

    buzzer( ID_PIN_JACK_SND, PB_8, PIN_CAPABILITY_AD )
{

}
