#include "Meowbit.h"

Meowbit meow;

int main()
{
    meow.init();

    int state = 0;

    while(1)
    {
        meow.io.led0.setDigitalValue( state );
        meow.io.led1.setDigitalValue( !state );
        fiber_sleep(300);
        state = !state;
    }
}
