#include <avr/io.h>
#include <util/delay.h>
#define _BV(bit) (1 << (bit))
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))
#define loop_until_bit_is_set(sfr, bit) do { } while (bit_is_clear(sfr, bit))
#define loop_until_bit_is_clear(sfr, bit) do { } while (bit_is_set(sfr, bit))
#include "uart.h"


void Uart_SetBaudRate(unsigned short BuadRate)
{
    unsigned short UBBR = ( (F_CPU / 16) /  BuadRate ) - 1;
    UBRR0L = (UBBR & 0xFF);//use all 8 bits in LOW
    UBRR0H = (( UBBR >> 8 ) & 0xFF);//use last 2 bits of HIGH to have a toatal of 10 bits
}

void Uart_Init(){
  UCSR0B=UCSR0B| (1<<3); //or (1<<TXEN0) enable transmission
  UCSR0B=UCSR0B| (1<<4); //or (1<<RXEN0) reciever enable
  UCSR0C= UCSR0C &~ (1<<6);
  UCSR0C= UCSR0C |(1<<1) |(1<<2); //OR (3<<1) OR REGISTOR NAME
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  
  

}

void sent_uartdata(char data){
  while(UCSR0A & (1<<UDRE0)==0){// wait till write buffer is empty

  }
  UDR0= data;
}

char recieve_uartdata(){
  while ( ! (UCSR0A & ( 1 << RXC0)) );
    return UDR0;// wait for data to be recieved 
}

void Uart_SendString(const char DataString[]){
    int i;
    for (i=0; DataString[i]; i++)
    {
        Uart_SendString(DataString[i]);
    }
}