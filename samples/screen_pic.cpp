

#include "Meowbit.h"

Meowbit meow;

static uint8_t rgui8_db[ ( 160 * 128 ) / 2 ];
static uint32_t rgui_palette[ 16 ] = {
    0x003f0000,
    0x007f0000,
    0x00af0000,
    0x00ff0000,
    0x00003f00,
    0x00007f00,
    0x0000af00,
    0x0000ff00,
    0x0000003f,
    0x0000007f,
    0x000000af,
    0x000000ff,
    0x003f3f3f,
    0x007f7f7f,
    0x00afafaf,
    0x00ffffff
};

int main()
{
    int32_t i_y, i_x, i_flipper;
    uint32_t ui_time_old, ui_time_new;

    meow.init();

    memset( rgui8_db, 0, sizeof( rgui8_db ) );
    for( i_y = 0; i_y < 128; i_y += 2 )
    {
        uint8_t ui8_pel = ( i_y & 0xf ) | ( ( ( i_y + 1 ) & 0xf ) << 4 );
        for( i_x = 0; i_x < 160; i_x++ )
        {
            rgui8_db[ i_x * ( 128 >> 1 ) + ( i_y >> 1 ) ] = ui8_pel;
        }
    }

    ui_time_old = meow.timer.getTime();
    i_flipper = 0;

    while(1)
    {
        uint8_t ui8_pel_0 = 0xff;
        uint8_t ui8_pel_1 = ( 0 & 0xf ) | ( ( ( 1 ) & 0xf ) << 4 );

        meow.io.led0.setDigitalValue( !!( i_flipper & 0x10 ) );
        
        meow.st7735->sendIndexedImage( &rgui8_db[ 0 ], 160, 128, rgui_palette );
        meow.st7735->waitForSendDone();

        ui_time_new = meow.timer.getTime();

        for( i_x = 0; i_x < 160; i_x++ )
        {
            if( i_x < ( int32_t )( ui_time_new - ui_time_old ) )
            {
                rgui8_db[ i_x * ( 128 >> 1 ) + ( i_y >> 1 ) ] = ui8_pel_0;
            }
            else
            {
                rgui8_db[ i_x * ( 128 >> 1 ) + ( i_y >> 1 ) ] = ui8_pel_1;
            }
        }

        ui_time_old = ui_time_new;
        i_flipper++;
    }
}





