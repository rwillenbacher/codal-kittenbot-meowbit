/*
The MIT License (MIT)

Copyright (c) 2016 Lancaster University, UK.

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


#include "Meowbit.h"
#include "Timer.h"

using namespace codal;

static Meowbit *device_instance = NULL;



/**
  * Constructor.
  *
  * Create a representation of a Meowbit device, which includes member variables
  * that represent various device drivers used to control aspects of the Kittenbot Meowbit.
  */
Meowbit::Meowbit() :
    tim2(TIM2, TIM2_IRQn),
    tim5(TIM5, TIM5_IRQn),
    timer(tim5),
    messageBus(),
    io(),
    spi(io.dispMosi, io.dispMiso, io.dispSck),
    buttonUp( io.buttonUp, DEVICE_ID_BUTTON_UP, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullMode::Up ),
    buttonDown( io.buttonDown, DEVICE_ID_BUTTON_DOWN, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullMode::Up ),
    buttonLeft( io.buttonLeft, DEVICE_ID_BUTTON_LEFT, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullMode::Up ),
    buttonRight( io.buttonRight, DEVICE_ID_BUTTON_RIGHT, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullMode::Up ),
    buttonA( io.buttonA, DEVICE_ID_BUTTON_A, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullMode::Up ),
    buttonB( io.buttonB, DEVICE_ID_BUTTON_B, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW, PullMode::Up ),
    synth0( MEOWBIT_BUZZER_FREQUENCY, false ),
    synth1( MEOWBIT_BUZZER_FREQUENCY, false )
{
    // Clear our status
    status = 0;

    device_instance = this;
}

/**
  * Post constructor initialisation method.
  *
  * This call will initialised the scheduler, memory allocator and other things.
  *
  * This is required as certain things cannot be done in a
  * static context i.e. in a constructor.
  *
  * @code
  * meowbit.init();
  * @endcode
  *
  * @note This method must be called before user code utilises any functionality
  *       contained within the Meowbit class.
  */
int Meowbit::init()
{
    if (status & DEVICE_INITIALIZED)
        return DEVICE_NOT_SUPPORTED;

    status |= DEVICE_INITIALIZED;

    // Bring up fiber scheduler.
    scheduler_init(messageBus);

    for(int i = 0; i < DEVICE_COMPONENT_COUNT; i++)
    {
        if(CodalComponent::components[i])
            CodalComponent::components[i]->init();
    }

    codal_dmesg_set_flush_fn(meowbit_dmesg_flush);
    status |= DEVICE_COMPONENT_STATUS_IDLE_TICK;

    screenIo = new SPIScreenIO( spi );
    st7735 = new ST7735( *screenIo, io.dispCs, io.dispDc );

   // init spi
    spi.setFrequency( 22 * 1000000 );
    spi.setMode( 0 );
    io.dispCs.setDigitalValue( 1 );
    if( spi.write( 0 ) == DEVICE_SPI_ERROR )
    {
        //io.led1.setDigitalValue( 1 );
    }

    // reset display
    io.dispRst.setDigitalValue( 0 );
    fiber_sleep( 20 );
    io.dispRst.setDigitalValue( 1 );
    fiber_sleep( 20 );

    // init lcd
    io.dispBl.setDigitalValue( 1 );
    st7735->init();
    st7735->configure( MADCTL_MX, 0x603 );
    st7735->setAddrWindow( 0, 0, 160, 128 );

    // link buzzer
    dac = new ZPWM( io.buzzer, mixer, MEOWBIT_BUZZER_FREQUENCY );

    target_disable_irq();

    synth0.setSampleRate( dac->getSampleRate() );
    synth1.setSampleRate( dac->getSampleRate() );
    //synth0.setTone(Synthesizer::SineTone);
    //synth1.setTone(Synthesizer::SineTone);
    //synth0.setBufferSize( 512 );
    //synth1.setBufferSize( 512 );
    mixerc0 = mixer.addChannel(synth0.output);
    mixerc1 = mixer.addChannel(synth1.output);
    mixerc0->isSigned = false;
    mixerc1->isSigned = false;

    target_enable_irq();

    mixer.pullRequest(); /* pull lol */

    return DEVICE_OK;
}

/**
  * A periodic callback invoked by the fiber scheduler idle thread.
  * We use this for any low priority, background housekeeping.
  *
  */
void Meowbit::idleCallback()
{
    codal_dmesg_flush();
}

void meowbit_dmesg_flush()
{
}
