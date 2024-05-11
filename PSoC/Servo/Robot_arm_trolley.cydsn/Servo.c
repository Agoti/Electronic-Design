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

#include <project.h>
#include "defs.h"
#include "param.h"



void SetServoLimit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit)
{
    unsigned short int temp_ccw = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
    unsigned short int temp_cw = 0;
    unsigned char temp_ccw_h = 0; // 待发送数据h位 // (h bits to be sended)
    unsigned char temp_ccw_l = 0; // 待发送数据l位 // (l bits to be sended)
    unsigned char temp_cw_h = 0;
    unsigned char temp_cw_l = 0;
    unsigned char temp_sum = 0; // 校验和寄存变量 // (temp variable to save checksum)
    if (ccw_limit > 1023)
    {
        temp_ccw = 1023;
        // 限制速度值在可用范围内 // (limit the velocity to 0-1023)
    }
    else
    {
        temp_ccw = ccw_limit;
    }
    if (cw_limit > 1023)
    {
        temp_cw = 1023;
    }
    else
    {
        temp_cw = cw_limit;
    }
    temp_ccw_h = (unsigned char)(temp_ccw >> 8);
    temp_ccw_l = (unsigned char)temp_ccw; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    temp_cw_h = (unsigned char)(temp_cw >> 8);
    temp_cw_l = (unsigned char)temp_cw; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    // PORTA &= ~_BV(PA1);
    // PORTA |= _BV(PA0); // 使总线处于主机发送状态 // (Set the bus to host transmit state)
    // UCSR0A |= (1<<TXC0); // 清除UART_10写完成标志 // (Clear written flag of UART_10)
    UART_PutChar(0xFF);       // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_PutChar(0xFF);       // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_PutChar(id);         // 发送id // (Send the servo’s ID)
    UART_PutChar(7);          // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
    UART_PutChar(0x03);       // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
    UART_PutChar(0x06);       // 舵机控制寄存器首地址
    UART_PutChar(temp_cw_l);  // 发送顺时针位置限制低位 // (Send the low byte of clockwise position limit)
    UART_PutChar(temp_cw_h);  // 发送顺时针位置限制高位 //(Send the high byte of clockwise position limit)
    UART_PutChar(temp_ccw_l); // 发送逆时针位置限制低位 // (Send the low byte of counterclockwise position limit)
    UART_PutChar(temp_ccw_h); // 发送逆时针位置限制高位 // (Send the low byte of counterclockwise position limit)
    temp_sum = id + 7 + 0x03 + 0x06 + temp_cw_l + temp_cw_h + temp_ccw_l + temp_ccw_h;
    temp_sum = ~temp_sum;   // 计算校验和 // (Calculate the checksum)
    UART_PutChar(temp_sum); // 发送校验和 // (Send checksum)
    // while ( !( UCSR0A & (1<<TXC0)) ) ;
    // PORTA |= _BV(PA1);
    // PORTA &= ~_BV(PA0); // 使总线处于主机接收状态 // (Set the UART bus to host receiving state)
    CyDelay(WAITING_TIME); // 送完成后，总线会被从机占用，反馈应答数据，所以进行延时 // (The bus will be overrode by slave after finishing sending // to receive the answer, so here delays 2 ms.) }
}

void SetServoPosition(unsigned char id, unsigned short int position, unsigned short int velocity)
{
    unsigned short int temp_velocity = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
    unsigned short int temp_position = 0;
    unsigned char temp_velocity_h = 0; // 待发送数据h位 // (h bits to be sended)
    unsigned char temp_velocity_l = 0; // 待发送数据l位 // (l bits to be sended)
    unsigned char temp_position_h = 0;
    unsigned char temp_position_l = 0;
    unsigned char temp_sum = 0; // 校验和寄存变量 // (temp variable to save checksum)
    if (velocity > 1023)
    {
        temp_velocity = 1023;
        // 限制速度值在可用范围内 // (limit the velocity to 0-1023)
    }
    else
    {
        temp_velocity = velocity;
    }
    if (position > 1023)
    {
        temp_position = 1023;
    }
    else
    {
        temp_position = position;
    }
    temp_velocity_h = (unsigned char)(temp_velocity >> 8);
    temp_velocity_l = (unsigned char)temp_velocity; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    temp_position_h = (unsigned char)(temp_position >> 8);
    temp_position_l = (unsigned char)temp_position; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    // PORTA &= ~_BV(PA1);
    // PORTA |= _BV(PA0); // 使总线处于主机发送状态 // (Set the bus to host transmit state)
    // UCSR0A |= (1<<TXC0); // 清除UART0写完成标志 // (Clear written flag of UART0)
    UART_PutChar(0xFF);            // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_PutChar(0xFF);            // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_PutChar(id);              // 发送id // (Send the servo’s ID)
    UART_PutChar(7);               // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
    UART_PutChar(0x03);            // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
    UART_PutChar(0x1E);            // 舵机控制寄存器首地址
    UART_PutChar(temp_position_l); // 发送顺时针位置限制低位 // (Send the low byte of clockwise position limit)
    UART_PutChar(temp_position_h); // 发送顺时针位置限制高位 //(Send the high byte of clockwise position limit)
    UART_PutChar(temp_velocity_l); // 发送逆时针位置限制低位 // (Send the low byte of counterclockwise position limit)
    UART_PutChar(temp_velocity_h); // 发送逆时针位置限制高位 // (Send the low byte of counterclockwise position limit)
    temp_sum = id + 7 + 0x03 + 0x1E + temp_position_l + temp_position_h + temp_velocity_l + temp_velocity_h;
    temp_sum = ~temp_sum;   // 计算校验和 // (Calculate the checksum)
    UART_PutChar(temp_sum); // 发送校验和 // (Send checksum)
    // while ( !( UCSR0A & (1<<TXC0)) ) ;
    // PORTA |= _BV(PA1);
    // PORTA &= ~_BV(PA0); // 使总线处于主机接收状态 // (Set the UART bus to host receiving state)
    CyDelay(WAITING_TIME); // 送完成后，总线会被从机占用，反馈应答数据，所以进行延时 // (The bus will be overrode by slave after finishing sending // to receive the answer, so here delays 2 ms.) }
}

void SetServoVelocity(unsigned char id, signed short int velocity)
{
    unsigned char temp_sign = 0;          // 临时符号，用于进行方向判别 // (temp variable to judge the direction)
    unsigned short int temp_velocity = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
    unsigned char temp_value_h = 0;       // 待发送数据h位 // (h bits to send)
    unsigned char temp_value_l = 0;       // 待发送数据l位 // (l bits to send)
    unsigned char temp_sum = 0;           // 校验和寄存变量 // (temp variable to save checksum)
    if (velocity < 0)
    {
        temp_velocity = -velocity; // 如果为负数，则取绝对值 // (if negative, get the absolute value)
        temp_sign = 1;             // 设置负数符号标志 // (Set negative flag)
    }
    else
    {
        temp_velocity = velocity;
        temp_sign = 0; // 设置正数符号标志 // (Set positive flag)
    }
    if (temp_velocity > 1023)
    {
        temp_velocity = 1023; // 限制速度值在可用范围内 // (Limit the velocity to 0-1023)
    }                         // 设置bit10为方向位，这时temp_velocity就是待发送的速度数据了 // (Set bit0 as direction bit, then temp_velocity is the data to be sended)
    temp_velocity |= (temp_sign << 10);
    temp_value_h = (unsigned char)(temp_velocity >> 8); // 将16bit数据拆为2个8bit数据 // (Split the 16 bits to 2 bytes)
    temp_value_l = (unsigned char)temp_velocity;
    UART_PutChar(0xFF);         // 发送启动符号0xFF // (Send the start byte 0xFF)
    UART_PutChar(0xFF);         // 发送启动符号0xFF // (Send the start byte 0xFF)
    UART_PutChar(id);           // 发送id // (Send the servo’s ID)
    UART_PutChar(5);            // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
    UART_PutChar(0x03);         // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
    UART_PutChar(0x20);         // 舵机控制寄存器首地址 // (Send the start address of control register)
    UART_PutChar(temp_value_l); // 发送速度数据低位 // (Send the low byte of velocity)
    UART_PutChar(temp_value_h); // 发送速度数据高位 // (Send the high byte of velocity)
    temp_sum = id + 5 + 0x03 + 0x20 + temp_value_l + temp_value_h;
    temp_sum = ~temp_sum;    // 计算校验和 // (Calculate the checksum)
    UART_PutChar(temp_sum); // 发送校验和 // (Send the checksum)
    CyDelay(WAITING_TIME);
}

void set_servo_limit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit)
{
    unsigned short int temp_ccw = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
    unsigned short int temp_cw = 0;
    unsigned char temp_ccw_h = 0; // 待发送数据h位 // (h bits to be sended)
    unsigned char temp_ccw_l = 0; // 待发送数据l位 // (l bits to be sended)
    unsigned char temp_cw_h = 0;
    unsigned char temp_cw_l = 0;
    unsigned char temp_sum = 0; // 校验和寄存变量 // (temp variable to save checksum)
    if (ccw_limit > 1023)
    {
        temp_ccw = 1023;
        // 限制速度值在可用范围内 // (limit the velocity to 0-1023)
    }
    else
    {
        temp_ccw = ccw_limit;
    }
    if (cw_limit > 1023)
    {
        temp_cw = 1023;
    }
    else
    {
        temp_cw = cw_limit;
    }
    temp_ccw_h = (unsigned char)(temp_ccw >> 8);
    temp_ccw_l = (unsigned char)temp_ccw; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    temp_cw_h = (unsigned char)(temp_cw >> 8);
    temp_cw_l = (unsigned char)temp_cw; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    // PORTA &= ~_BV(PA1);
    // PORTA |= _BV(PA0); // 使总线处于主机发送状态 // (Set the bus to host transmit state)
    // UCSR0A |= (1<<TXC0); // 清除UART0写完成标志 // (Clear written flag of UART0)
    UART_1_PutChar(0xFF);       // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_1_PutChar(0xFF);       // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_1_PutChar(id);         // 发送id // (Send the servo’s ID)
    UART_1_PutChar(7);          // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
    UART_1_PutChar(0x03);       // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
    UART_1_PutChar(0x06);       // 舵机控制寄存器首地址
    UART_1_PutChar(temp_cw_l);  // 发送顺时针位置限制低位 // (Send the low byte of clockwise position limit)
    UART_1_PutChar(temp_cw_h);  // 发送顺时针位置限制高位 //(Send the high byte of clockwise position limit)
    UART_1_PutChar(temp_ccw_l); // 发送逆时针位置限制低位 // (Send the low byte of counterclockwise position limit)
    UART_1_PutChar(temp_ccw_h); // 发送逆时针位置限制高位 // (Send the low byte of counterclockwise position limit)
    temp_sum = id + 7 + 0x03 + 0x06 + temp_cw_l + temp_cw_h + temp_ccw_l + temp_ccw_h;
    temp_sum = ~temp_sum;   // 计算校验和 // (Calculate the checksum)
    UART_1_PutChar(temp_sum); // 发送校验和 // (Send checksum)
    // while ( !( UCSR0A & (1<<TXC0)) ) ;
    // PORTA |= _BV(PA1);
    // PORTA &= ~_BV(PA0); // 使总线处于主机接收状态 // (Set the UART_1 bus to host receiving state)
    CyDelay(WAITING_TIME); // 送完成后，总线会被从机占用，反馈应答数据，所以进行延时 // (The bus will be overrode by slave after finishing sending // to receive the answer, so here delays 2 ms.) }
}

void set_servo_pos(unsigned char id, unsigned short int position, unsigned short int velocity)
{
    unsigned short int temp_velocity = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
    unsigned short int temp_position = 0;
    unsigned char temp_velocity_h = 0; // 待发送数据h位 // (h bits to be sended)
    unsigned char temp_velocity_l = 0; // 待发送数据l位 // (l bits to be sended)
    unsigned char temp_position_h = 0;
    unsigned char temp_position_l = 0;
    unsigned char temp_sum = 0; // 校验和寄存变量 // (temp variable to save checksum)
    if (velocity > 1023)
    {
        temp_velocity = 1023;
        // 限制速度值在可用范围内 // (limit the velocity to 0-1023)
    }
    else
    {
        temp_velocity = velocity;
    }
    if (position > 1023)
    {
        temp_position = 1023;
    }
    else
    {
        temp_position = position;
    }
    temp_velocity_h = (unsigned char)(temp_velocity >> 8);
    temp_velocity_l = (unsigned char)temp_velocity; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    temp_position_h = (unsigned char)(temp_position >> 8);
    temp_position_l = (unsigned char)temp_position; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
    // PORTA &= ~_BV(PA1);
    // PORTA |= _BV(PA0); // 使总线处于主机发送状态 // (Set the bus to host transmit state)
    // UCSR0A |= (1<<TXC0); // 清除UART_10写完成标志 // (Clear written flag of UART_10)
    UART_1_PutChar(0xFF);            // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_1_PutChar(0xFF);            // 发送启动符号0xFF // (Send the start byte 0xff)
    UART_1_PutChar(id);              // 发送id // (Send the servo’s ID)
    UART_1_PutChar(7);               // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
    UART_1_PutChar(0x03);            // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
    UART_1_PutChar(0x1E);            // 舵机控制寄存器首地址
    UART_1_PutChar(temp_position_l); // 发送顺时针位置限制低位 // (Send the low byte of clockwise position limit)
    UART_1_PutChar(temp_position_h); // 发送顺时针位置限制高位 //(Send the high byte of clockwise position limit)
    UART_1_PutChar(temp_velocity_l); // 发送逆时针位置限制低位 // (Send the low byte of counterclockwise position limit)
    UART_1_PutChar(temp_velocity_h); // 发送逆时针位置限制高位 // (Send the low byte of counterclockwise position limit)
    temp_sum = id + 7 + 0x03 + 0x1E + temp_position_l + temp_position_h + temp_velocity_l + temp_velocity_h;
    temp_sum = ~temp_sum;   // 计算校验和 // (Calculate the checksum)
    UART_1_PutChar(temp_sum); // 发送校验和 // (Send checksum)
    // while ( !( UCSR0A & (1<<TXC0)) ) ;
    // PORTA |= _BV(PA1);
    // PORTA &= ~_BV(PA0); // 使总线处于主机接收状态 // (Set the UART_1 bus to host receiving state)
    CyDelay(WAITING_TIME); // 送完成后，总线会被从机占用，反馈应答数据，所以进行延时 // (The bus will be overrode by slave after finishing sending // to receive the answer, so here delays 2 ms.) }
}

void set_servo_velocity(unsigned char id, signed short int velocity)
{
    unsigned char temp_sign = 0;          // 临时符号，用于进行方向判别 // (temp variable to judge the direction)
    unsigned short int temp_velocity = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
    unsigned char temp_value_h = 0;       // 待发送数据h位 // (h bits to send)
    unsigned char temp_value_l = 0;       // 待发送数据l位 // (l bits to send)
    unsigned char temp_sum = 0;           // 校验和寄存变量 // (temp variable to save checksum)
    if (velocity < 0)
    {
        temp_velocity = -velocity; // 如果为负数，则取绝对值 // (if negative, get the absolute value)
        temp_sign = 1;             // 设置负数符号标志 // (Set negative flag)
    }
    else
    {
        temp_velocity = velocity;
        temp_sign = 0; // 设置正数符号标志 // (Set positive flag)
    }
    if (temp_velocity > 1023)
    {
        temp_velocity = 1023; // 限制速度值在可用范围内 // (Limit the velocity to 0-1023)
    }                         // 设置bit10为方向位，这时temp_velocity就是待发送的速度数据了 // (Set bit0 as direction bit, then temp_velocity is the data to be sended)
    temp_velocity |= (temp_sign << 10);
    temp_value_h = (unsigned char)(temp_velocity >> 8); // 将16bit数据拆为2个8bit数据 // (Split the 16 bits to 2 bytes)
    temp_value_l = (unsigned char)temp_velocity;
    UART_1_PutChar(0xFF);         // 发送启动符号0xFF // (Send the start byte 0xFF)
    UART_1_PutChar(0xFF);         // 发送启动符号0xFF // (Send the start byte 0xFF)
    UART_1_PutChar(id);           // 发送id // (Send the servo’s ID)
    UART_1_PutChar(5);            // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
    UART_1_PutChar(0x03);         // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
    UART_1_PutChar(0x20);         // 舵机控制寄存器首地址 // (Send the start address of control register)
    UART_1_PutChar(temp_value_l); // 发送速度数据低位 // (Send the low byte of velocity)
    UART_1_PutChar(temp_value_h); // 发送速度数据高位 // (Send the high byte of velocity)
    temp_sum = id + 5 + 0x03 + 0x20 + temp_value_l + temp_value_h;
    temp_sum = ~temp_sum;    // 计算校验和 // (Calculate the checksum)
    UART_1_PutChar(temp_sum); // 发送校验和 // (Send the checksum)
    CyDelay(WAITING_TIME);
}

/* [] END OF FILE */
