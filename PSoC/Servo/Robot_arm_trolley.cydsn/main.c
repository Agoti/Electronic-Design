/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#include "defs.h"
#include "param.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g., MyInst_Start()) */
    // Initialize UARTs
    UART_Start();
    UART_1_Start();
    UART_2_Start();

    // Initialize servos
    servos_motormode();
    stop();

    // Initialize ranging probes
    ranging_init();

    // Initialize LCD
    LCD_Start();
    
    // Local variables
    char operation_char;    // Operation received from Zigbee
    int d1, d2;             // Distance from ranging probes

    // initialize antman mode(currently unuseful)
    antman_init();

    for (;;)
    {
        
        /* Place your application code here. */
        d1 = get_millimeter1();
        d2 = get_millimeter2();

        LCD_Position(0, 0);
        LCD_PrintString(LCD_CLEAR);
        LCD_Position(1, 0);
        LCD_PrintString(LCD_CLEAR);
        LCD_Position(0, 0);
        LCD_PrintInt32(d1);
        LCD_Position(1, 0);
        LCD_PrintInt32(d2);

        // antman(d1, d2, SPEED);

        if(UART_2_GetRxBufferSize() > 0)
		{		
            operation_char = UART_2_GetChar();
            switch (operation_char)
            {
            case 'w':go_forward(SPEED); break;
            case 'a':turn_left(SPEED); break;
            case 's':go_forward(-SPEED); break;
            case 'd':turn_right(SPEED); break;
            case 'q':turn_left_precise(SPEED, 0); break;
            case 'e':turn_right_precise(SPEED, 0); break;
            case 'z':reverse_turn_left(SPEED); break;
            case 'c':reverse_turn_right(SPEED); break;
            case '1':m1_left_unit(); break;
            case '2':m1_right_unit(); break;
            case '3':m2_forward_unit(); break;
            case '4':m2_backward_unit(); break;
            case '5':m3_up_unit(); break;
            case '6':m3_down_unit(); break;
            case '7':m4_up_unit(); break;
            case '8':m4_up_unit(); break;
            case '9':grab(); break;
            case '0':drop(); break;
            case '-':reset_init_pos(); break;
            case '+':pause(); break;
            case ' ':stop(); break;
            
            default: stop();pause();
            }       
		}
        else{
            stop();pause();
        }
        CyDelay(INTERVAL);
    }
}

/* [] END OF FILE */
