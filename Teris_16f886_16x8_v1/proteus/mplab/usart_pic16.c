/******************************************************************************

 Serial communication library for PIC16F series MCUs.

 Compiler: Microchip XC8 v1.12 (http://www.microchip.com/xc)

 Version: 1.0 (21 July 2013)

 MCU: PIC16F877A
 Frequency: 20MHz

                                     NOTICE

NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
me@avinashgupta.com

 *******************************************************************************/
#include <stdint.h>
#include <xc.h>

#include "usart_pic16.h"

void USARTInit(uint16_t baud_rate) {
    //SPBRG
    switch (baud_rate) {
        case 9600:
            SPBRG = 129;
            break;
        case 19200:
            SPBRG = 64;
            break;
        case 28800:
            SPBRG = 42;
            break;
        case 33600:
            SPBRG = 36;
            break;
    }

    //TXSTA
    TXSTAbits.TX9 = 0; //8 bit transmission
    TXSTAbits.TXEN = 1; //Transmit enable
    TXSTAbits.SYNC = 0; //Async mode
    TXSTAbits.BRGH = 1; //High speed baud rate

    //RCSTA
    RCSTAbits.SPEN = 1; //Serial port enabled
    RCSTAbits.RX9 = 0; //8 bit mode
    RCSTAbits.CREN = 1; //Enable receive
    RCSTAbits.ADDEN = 0; //Disable address detection

    //Receive interrupt
    RCIE = 1;
    PEIE = 1;

    ei();
}

void USARTWriteChar(char ch) {
    while (!PIR1bits.TXIF);

    TXREG = ch;
}

void USARTWriteString(const char *str) {
    while (*str != '\0') {
        USARTWriteChar(*str);
        str++;
    }
}

void USARTWriteLine(const char *str) {
    USARTWriteChar('\r'); //CR
    USARTWriteChar('\n'); //LF

    USARTWriteString(str);
}

void USARTWriteInt(int16_t val, int8_t field_length) {
    char str[5] = {0, 0, 0, 0, 0};
    int8_t i = 4, j = 0;

    //Handle negative integers
    if (val < 0) {
        USARTWriteChar('-'); //Write Negative sign
        val = val*-1; //convert to positive
    } else {
        USARTWriteChar(' ');
    }

    if (val == 0 && field_length < 1) {
        USARTWriteChar('0');
        return;
    }
    while (val) {
        str[i] = val % 10;
        val = val / 10;
        i--;
    }

    if (field_length == -1)
        while (str[j] == 0) j++;
    else
        j = 5 - field_length;


    for (i = j; i < 5; i++) {
        USARTWriteChar('0' + str[i]);
    }
}

void USARTGotoNewLine() {
    USARTWriteChar('\r'); //CR
    USARTWriteChar('\n'); //LF
}
