#ifndef UART_h
#define UART_h
void Uart_SetBaudRate(unsigned short BuadRate);
void Uart_Init();
void sent_uartdata(char data);
char recieve_uartdata();
void Uart_SendString(const char DataString[]);
#endif