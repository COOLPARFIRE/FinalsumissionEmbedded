#include <avr/io.h>
#include <util/delay.h>
#include "DIO.h"
#include "ADC.h"
#include "UART.h"

//mohammed abbas 202000957
int main(){

  init();//Callingthe init function
  int ADC_REG_READING;//using it as value to use  later in the itoa fuction and making it carry the value of the ADC register
  unsigned char buffer[4];//making a string that carry the values
  while(1)
  {
    v_resistor();//the variable resistor function
    LED_BUZZER();//the warning function that light up the led and buzzer
    ADC_REG_READING = Adc_ReadChannel(5);//making the int carry the read channel value
    itoa(ADC_REG_READING,buffer,10);//function that transform the integer to string
    Uart_SendString(buffer);//function  that send string to monitor
    Uart_SendString("\n");//function to make space after line



  }
}

void init(){
    v_resistor();//intializing the var resisor function 
    LED_BUZZER();//intializing the led and buzzer warning function
    Uart_Init();//intializing the uart function 
}

void v_resistor(void){//this function utilizes variable resistor to change the led brightness 
  float reg_val;//value to carry the adc register value
  
  Dio_SetPinDirection('C',2,0);//setting port c pin 2 as input

  Adc_Init();//adc intialzingfunction

  reg_val = Adc_ReadChannel(2);//making res carry the adc register value


  if(reg_val>500){//function that work when volatge pass the variable resistor and the res value greater than 500

    

     Dio_SetPinDirection('D',6,1);//DDRD pin 6 output 
    Dio_SetPortDirection('D',6,1);//Port D pin 6 output
    
  }
    if(reg_val<400 & reg_val>200){//if res value is less than 400 and greater than 200 and this function makes the led dim light
    Dio_SetPinDirection('D',6,0);//DDRD pin 6 work as input
    Dio_SetPortDirection('D',6,1);//PortD pin 6 work as output
   
    }
    if(reg_val<200 & reg_val>0){//if res value less than 200 and greater than 0 makes the led off
     Dio_SetPinDirection('D',6,0);//DDRD pin 6 input
    Dio_SetPortDirection('D',6,0);//Port D pin 6 off
  
}
}

void LED_BUZZER (void){//this function makes the warning function where switch act as led lights flash and buzzer work 
float volt;//value to carry the adc register value
  Dio_SetPinDirection('D',3,1);//DDRD Pin 3 work as Out put
   Dio_SetPinDirection('D',7,1);//DDRD Pin 7 work as out put
   Dio_SetPinDirection('D',5,1);//DDRD Pin 5 work as Out put
 
  Dio_SetPinDirection('C',5,0);//DDRC Pin 5 work as input

  Adc_Init();//adc intialization function

  volt = Adc_ReadChannel(5);//Making the volt carry the adc reg value

  
  if(volt>700){//Function that run when volt passes through the switch and make the flash and buzzer work
    

    
   Dio_SetPortDirection('D',3,1);//PORTD pin 3 output
   _delay_ms(100);//delay function
   Dio_SetPortDirection('D',3,0);//PORTD pin 3 input
   _delay_ms(100);//delay function
   Dio_SetPortDirection('D',7,1);//PORTD pin 7 output
  _delay_ms(100);//delay function
  Dio_SetPortDirection('D',7,0);//PORTD pin 7 input
   _delay_ms(100);//delay function
  Dio_SetPortDirection('D',5,1);//PORTD pin 5 output
  _delay_ms(100);//delay function
  Dio_SetPortDirection('D',5,0);//PORTD pin 5 input
   _delay_ms(100);//delay function
  //This function makes led flash and buzze make warning

  }
    else

    Dio_SetPortDirection('D',3,0);//PORTD pin 3 input
    Dio_SetPortDirection('D',7,0);//PORTD pin 7 input
     Dio_SetPortDirection('D',5,0);//PORTD pin 5 input
 //this function turns off the warning
}
