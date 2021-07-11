

#include "Meowbit.h"

typedef struct {
    bool b_0;
    bool b_1;
    bool b_left;
    bool b_right;
    bool b_up;
    bool b_down;
} keyboard_t;


Meowbit meow;

keyboard_t s_keyboard;

#define MIN( x, y ) ( (x) < (y) ? (x) : (y) )
#define MAX( x, y ) ( (x) < (y) ? (y) : (x) )
#define CLAMP( x, _min_, _max_ ) ( MAX( MIN( x, _max_ ), _min_ ) )

uint32_t rgui_palette[ 16 ] = {
    0x00000000,
    0x00555555,
    0x00aaaaaa,
    0x00ffffff,
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
    0x000000ff
};

uint8_t rgui8_screen[ ( 160 * 128 ) / 2 ];

void buttonPressed( Event e, void *p_arg )
{
    bool *pb_dst;
    keyboard_t *ps_keyboard = ( keyboard_t * )p_arg;

    switch( e.source )
    {
        case DEVICE_ID_BUTTON_A:
            pb_dst = &ps_keyboard->b_0;
            break;
        case DEVICE_ID_BUTTON_B:
            pb_dst = &ps_keyboard->b_1;
            break;
        case DEVICE_ID_BUTTON_LEFT:
            pb_dst = &ps_keyboard->b_left;
            break;
        case DEVICE_ID_BUTTON_RIGHT:
            pb_dst = &ps_keyboard->b_right;
            break;
        case DEVICE_ID_BUTTON_UP:
            pb_dst = &ps_keyboard->b_up;
            break;
        case DEVICE_ID_BUTTON_DOWN:
            pb_dst = &ps_keyboard->b_down;
            break;
        default:
            pb_dst = &ps_keyboard->b_0;
            break;
    }

    if( e.value == DEVICE_BUTTON_EVT_DOWN )
    {
        *pb_dst = true;
    }
    else if( e.value == DEVICE_BUTTON_EVT_UP)
    {
        *pb_dst = false;
    }
}


void lcd_refresh( Meowbit *meow, int32_t i_freq0, int32_t i_freq1, int32_t i_freq_sel )
{
    int32_t i_x, i_y;
    uint8_t ui8_pel_freq0, ui8_pel_freq1;

    memset( rgui8_screen, 0, sizeof( rgui8_screen ) );

    if( i_freq_sel == 0 )
    {
        ui8_pel_freq0 = 0x66;
        ui8_pel_freq1 = 0x22;
    }
    else
    {
        ui8_pel_freq0 = 0x22;
        ui8_pel_freq1 = 0x66;
    }

    for( i_x = 30; i_x < 70; i_x++ )
    {
        for( i_y = 120 - 1 - ( ( i_freq0 * 55 ) / 20000 ); i_y < 120; i_y++ )
        {
            rgui8_screen[ ( i_x * ( 128 >> 1 ) ) + i_y ] = ui8_pel_freq0;
        }
    }
    for( i_x = 90; i_x < 130; i_x++ )
    {
        for( i_y = 120 - 1 - ( ( i_freq1 * 55 ) / 20000 ); i_y < 120; i_y++ )
        {
            rgui8_screen[ ( i_x * ( 128 >> 1 ) ) + i_y ] = ui8_pel_freq1;
        }
    }

    meow->st7735->sendIndexedImage( rgui8_screen, 160, 128, rgui_palette );
    meow->st7735->waitForSendDone();
}


int main()
{
    volatile float f_freq0, f_freq1;
    volatile int32_t i_flipperA, i_flipperB, i_freq_sel, i_freq0, i_freq1;
    volatile bool b_refresh_lcd = false;
    volatile keyboard_t *ps_key = &s_keyboard;

    memset( &s_keyboard, 0, sizeof( s_keyboard ) );

    meow.init();

    i_flipperA = i_flipperB = 0;
    i_freq0 = 10000;
    i_freq1 = 1000;
    i_freq_sel = 0;

    EventModel::defaultEventBus->listen( DEVICE_ID_BUTTON_A, DEVICE_EVT_ANY, &buttonPressed, &s_keyboard );
    EventModel::defaultEventBus->listen( DEVICE_ID_BUTTON_B, DEVICE_EVT_ANY, &buttonPressed, &s_keyboard );
    EventModel::defaultEventBus->listen( DEVICE_ID_BUTTON_LEFT, DEVICE_EVT_ANY, &buttonPressed, &s_keyboard );
    EventModel::defaultEventBus->listen( DEVICE_ID_BUTTON_RIGHT, DEVICE_EVT_ANY, &buttonPressed, &s_keyboard );
    EventModel::defaultEventBus->listen( DEVICE_ID_BUTTON_UP, DEVICE_EVT_ANY, &buttonPressed, &s_keyboard );
    EventModel::defaultEventBus->listen( DEVICE_ID_BUTTON_DOWN, DEVICE_EVT_ANY, &buttonPressed, &s_keyboard );

    meow.mixerc0->volume = 0;
    meow.mixerc1->volume = 0;
    meow.synth0.setVolume( 1000 );
    meow.synth1.setVolume( 1000 );
    meow.synth0.setFrequency( i_freq0 );
    meow.synth1.setFrequency( i_freq1 );

    lcd_refresh( &meow, i_freq0, i_freq1, i_freq_sel );

    while(1)
    {
        fiber_sleep( 20 );

        if( ps_key->b_0 )
        {
            if( !i_flipperA )
            {
                meow.io.led0.setDigitalValue( 1 );
//                meow.synth0.setVolume( 1000 );
                meow.mixerc0->volume = 1000;
                i_flipperA = 1;
            }
        }
        else if( i_flipperA )
        {
            meow.io.led0.setDigitalValue( 0 );
//            meow.synth0.setVolume( 0 );
            meow.mixerc0->volume = 0;

            i_flipperA = 0;
        }

        if( ps_key->b_1 )
        {
            if( !i_flipperB )
            {
                meow.io.led1.setDigitalValue( 1 );
//                meow.synth1.setVolume( 1000 );
                meow.mixerc1->volume = 1000;
                i_flipperB = 1;
            }
        }
        else if( i_flipperB )
        {
            meow.io.led1.setDigitalValue( 0 );
//            meow.synth1.setVolume( 0 );
            meow.mixerc1->volume = 0;
            i_flipperB = 0;
        }

        if( ps_key->b_left )
        {
            i_freq_sel = ( i_freq_sel - 1 ) & 1;
            ps_key->b_left = false;
            b_refresh_lcd = true;
        }
        if( ps_key->b_right )
        {
            i_freq_sel = ( i_freq_sel + 1 ) & 1;
            ps_key->b_right = false;
            b_refresh_lcd = true;
        }
        if( ps_key->b_up )
        {
            if( i_freq_sel == 0 && i_freq0 <= 10000 )
            {
                i_freq0 = i_freq0 * 2;
                i_freq0 = CLAMP( i_freq0, 20, 10000 );
                //meow.synth0.setFrequency( ( float )i_freq0 );
                b_refresh_lcd = true;
            }
            else if( i_freq_sel == 1 && i_freq1 <= 10000 )
            {
                i_freq1 = i_freq1 * 2;
                i_freq1 = CLAMP( i_freq1, 20, 10000 );
                //meow.synth1.setFrequency( ( float )i_freq1 );
                b_refresh_lcd = true;
            }
            ps_key->b_up = false;
        }
        if( ps_key->b_down )
        {
            if( i_freq_sel == 0 && i_freq0 >= 20 )
            {
                i_freq0 = i_freq0 / 2;
                i_freq0 = CLAMP( i_freq0, 20, 10000 );
                //meow.synth0.setFrequency( ( float )i_freq0 );
                b_refresh_lcd = true;
            }
            else if( i_freq_sel == 1 && i_freq1 >= 20 )
            {
                i_freq1 = i_freq1 / 2;
                i_freq1 = CLAMP( i_freq1, 20, 10000 );
                //meow.synth1.setFrequency( ( float )i_freq1 );
                b_refresh_lcd = true;
            }
            ps_key->b_down = false;
        }

        b_refresh_lcd = true;
        f_freq0 = ( float )i_freq0;
        f_freq1 = ( float )i_freq1;
        meow.synth0.setFrequency( f_freq0 );
        meow.synth1.setFrequency( f_freq1 );

        if( b_refresh_lcd )
        {
            lcd_refresh( &meow, i_freq0, i_freq1, i_freq_sel );
            b_refresh_lcd = false;
        }
    }
}





