#define WINDOW_BASE 0
#define DEBUG 1

#if WINDOW_BASE
using namespace std;
#else
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = ON          // Code Protection bit (Program memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#endif

#include "common.h"
#include "bit_operator.h"
#include "bit_matrix.h"
#if !WINDOW_BASE
#include "usart_pic16.h"
#include "max7219.h"
#endif
#include "debug.h"
#include "array_control.h"
#include "math_control.h"
#include "memory_control.h"
#include "eeprom_operator.h"
#include "hal.h"
#include "logic.h"

#if WINDOW_BASE
#include "unittest.h"
#endif

void dbg_print_all_MATRIX4x4(uint8_t enable)
{
    if((DEBUG) && (enable))
    {
    	MATRIX4x4* matrix;
        dbg_print_line(1, "printf_all_MATRIX4x4");
        dbg_print1(1, "size = %d", CHARACTER_MAX);

        for(uint8_t index = 0; index < CHARACTER_MAX; index++)
        {
            for(uint8_t sub_index = 0; sub_index < g_char_info[index].num; sub_index++)
            {
                dbg_print2(1, "index = %d, sub_index = %d", index, sub_index);

            	matrix = lg_get_MATRIX4x4(index, sub_index);
                dbg_print_MATRIX4x4(1, NULL, 0, 0, matrix);
            }
        }

    }
}

void main_init()
{
#if !WINDOW_BASE
    max7219_init1();
#endif
    dbg_init();

#if WINDOW_BASE
    srand(time(NULL));
#else
    Seed = eeprom_read_int(SEED_EEPROM_INDEX);
	srand(Seed);
#endif
}     

void main_close()
{
    dbg_close();
}     

int main()
{
    main_init();
    
    uint8_t hit_res;
__start:
#if !WINDOW_BASE
	Seed++;
	eeprom_write_int(SEED_EEPROM_INDEX, Seed);
#endif
    lg_clear_matrix();
    while(1)
    {
        cur_x = 2, cur_y = 0;
        g_char_info_index = lg_char_info_index_rand();
        g_char_info_sub_index = 0;

        dbg_print1(DEBUG_ENABLE, "g_char_info_index = %d", g_char_info_index);
        if(lg_find_best_solution() == 0)
        {
            dbg_print_line(DEBUG_ENABLE, "GAME OVER!!!");
            goto __start;
        }
        g_cur_matrix4x4 = &g_matrix4x4[g_char_info[g_char_info_index].start_index + g_char_info_sub_index];
        while(1)
        {
#if !WINDOW_BASE
        	Seed++;
#endif
            hit_res = lg_hit_land(cur_x, cur_y, g_cur_matrix4x4, &g_matrix16x8);
            dbg_print1(DEBUG_DISABLE, "hit_res = %d", hit_res);
            lg_merge(cur_x, cur_y, g_cur_matrix4x4, &g_matrix16x8);
            if(hit_res == 1)
            {
                hal_print_Screen();
#if WINDOW_BASE
                Sleep(100);
#else
                __delay_ms(100);
#endif
                lg_delete_matrix(&g_matrix16x8);
            }
            dbg_print_MATRIX16x8(DEBUG_ENABLE, "Main screen", &g_matrix16x8);
            hal_print_Screen();
            if(hit_res == 0)
            {
                lg_clear(cur_x, cur_y, g_cur_matrix4x4, &g_matrix16x8);
            }
            else
            {
                break;
            }
#if WINDOW_BASE
            Sleep(500);
#else
            __delay_ms(200);
#endif
            cur_y++;
        }
    }
__exit:

#if WINDOW_BASE
    fclose(fp);
    system("PAUSE");
    return EXIT_SUCCESS;
#else
    return 0;
#endif
}
