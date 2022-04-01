/* 
 * File:   main.c
 * Author: Michael Scholten
 *
 * Created on March 21, 2022, 7:06 PM
 */

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(USART1_RX_vect){
    const char c = UDR1;
    if(c >= '0' && c <= '7'){
        PORTA = (PORTA & ~7) | (c - '0');
    }
}

void usart_init(uint32_t baudRate){
    UCSR1B = (1 << RXEN) | (1 << RXCIE);
    UCSR1C = (3 << UCSZ0);
    UBRR1 = F_CPU / (baudRate << 4) - 1;
    sei();
}

void powerReduction(){
    PRR0 = (1 << PRTWI0) | (1 << PRTIM2) | (1 << PRTIM0) | (1 << PRTIM1) | (1 << PRUSART0) | (1 << PRADC);
    PRR1 |= (1 << PRTIM4) | (1 << PRTIM3);
    PRR2 |= (1 << PRPTC) | (1 << PRUSART2) | (1 << PRSPI1) | (1 << PRTWI1);
}

int main() {
    DDRA |= 7;
    PORTA |= 7;
    usart_init(9600);
    powerReduction();
    while(1){
    }
    return 0;
}

