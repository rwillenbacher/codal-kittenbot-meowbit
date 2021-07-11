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

#ifndef MEOWBIT_H
#define MEOWBIT_H

#include "CodalHeapAllocator.h"
#include "codal-core/inc/types/Event.h"
#include "CodalDevice.h"
#include "ErrorNo.h"
#include "CodalCompat.h"
#include "CodalComponent.h"
#include "CodalDmesg.h"
#include "ManagedType.h"
#include "ManagedString.h"
#include "NotifyEvents.h"

#include "Button.h"
#include "MultiButton.h"
#include "MeowbitIO.h"
#include "CodalFiber.h"
#include "MessageBus.h"

#include "ZPWM.h"
#include "Synthesizer.h"
#include "Mixer.h"

#include "ZSingleWireSerial.h"
#include "ZSPI.h"
#include "STMLowLevelTimer.h"

#include "SPIScreenIO.h"
#include "ST7735.h"


// Status flag values
#define DEVICE_INITIALIZED                    0x01

/**
 * Class definition for a Meowbit device.
 *
 * Represents the device as a whole, and includes member variables that represent various device drivers
 * used to control aspects of the Kittenbot Meowbit.
 */
namespace codal
{
    class Meowbit : public CodalComponent
    {
        public:
            STMLowLevelTimer            tim2;
            STMLowLevelTimer            tim5;
            Timer                       timer;
            MessageBus                  messageBus;
            MeowbitIO                   io;
            ZSPI                        spi;
            SPIScreenIO                *screenIo;
            ST7735                     *st7735;


            Button buttonUp;
            Button buttonDown;
            Button buttonLeft;
            Button buttonRight;
            Button buttonA;
            Button buttonB;

#define MEOWBIT_BUZZER_FREQUENCY 22050
            Synthesizer synth0;
            Synthesizer synth1;
            Mixer mixer;
            MixerChannel *mixerc0;
            MixerChannel *mixerc1;
            ZPWM *dac;

            /**
             * Constructor.
             */
            Meowbit();

            /**
             * Post constructor initialisation method.
             */
            int init();

            /**
             * Delay execution for the given amount of time.
             *
             * If the scheduler is running, this will deschedule the current fiber and perform
             * a power efficient, concurrent sleep operation.
             *
             * If the scheduler is disabled or we're running in an interrupt context, this
             * will revert to a busy wait.
             *
             * Alternatively: wait, wait_ms, wait_us can be used which will perform a blocking sleep
             * operation.
             *
             * @param milliseconds the amount of time, in ms, to wait for. This number cannot be negative.
             *
             */
            void sleep(uint32_t milliseconds);

            /**
             * A periodic callback invoked by the fiber scheduler idle thread.
             * We use this for any low priority, background housekeeping.
             */
            virtual void idleCallback();

            /**
             * Determine the time since this Meowbit was last reset.
             *
             * @return The time since the last reset, in milliseconds.
             *
             * @note This will value overflow after 1.6 months.
             */
            //TODO: handle overflow case.
            unsigned long systemTime();
    };


    /**
     * Delay execution for the given amount of time.
     *
     * If the scheduler is running, this will deschedule the current fiber and perform
     * a power efficient, concurrent sleep operation.
     *
     * If the scheduler is disabled or we're running in an interrupt context, this
     * will revert to a busy wait.
     *
     * Alternatively: wait, wait_ms, wait_us can be used which will perform a blocking sleep
     * operation.
     *
     * @param milliseconds the amount of time, in ms, to wait for. This number cannot be negative.
     *
     */
    inline void Meowbit::sleep(uint32_t milliseconds)
    {
        fiber_sleep(milliseconds);
    }

    /**
     * Determine the time since this Meowbit was last reset.
     *
     * @return The time since the last reset, in milliseconds.
     *
     * @note This will value overflow after 1.6 months.
     */
    inline unsigned long Meowbit::systemTime()
    {
        return system_timer_current_time();
    }
}

void meowbit_dmesg_flush();

using namespace codal;

#endif
