#pragma once

#include "extensions.h"

#define UART_BASE   0x10000000UL
#define UART_THR    (*(volatile unsigned char *)(UART_BASE + 0x00))
#define UART_LSR    (*(volatile unsigned char *)(UART_BASE + 0x05))
#define LSR_THRE    (1 << 5)

#define UART0(S)    UART_SendString(S)

force_inline void UART_SendByte(char c)
{
    while (!(UART_LSR & LSR_THRE)) { /* spin */ }
    UART_THR = c;
}

force_inline void UART_SendString(const char* s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        UART_SendByte(s[i]);
    }
}