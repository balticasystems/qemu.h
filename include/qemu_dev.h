#pragma once

#include "extensions.h"

// IO

#define UART_BASE   (0x10000000UL)
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

// CTL

// SiFive
#define SIFIVE_TEST             (*(volatile uint32_t*)0x100000)

#define SIFIVE_TEST_PASS_FLAG   (0x5555)
#define SIFIVE_TEST_FAIL_FLAG   (0x3333)
#define SIFIVE_TEST_RESET_FLAG  (0x7777)

#define SIFIVE_TEST_PASS()      (SIFIVE_TEST = SIFIVE_TEST_PASS_FLAG)
#define SIFIVE_TEST_FAIL(code)  (SIFIVE_TEST = (((code) << 16) | SIFIVE_TEST_FAIL_FLAG))
#define SIFIVE_TEST_RESET()     (SIFIVE_TEST = SIFIVE_TEST_RESET_FLAG)
