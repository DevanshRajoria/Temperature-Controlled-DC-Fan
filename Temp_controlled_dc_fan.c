#include<avr/io.h>
#include<util/delay.h>

void cmd()  // Command functions for LCD
{ 
 PORTC = 0x04;
 _delay_ms(5);
 PORTC = 0x00;
}
void dat()  // Data functions for display on LCD
{ 
 PORTC = 0x05;
 _delay_ms(5);
 PORTC = 0x01;
} 
void splfn() // Functions for LCD
{
 int f[] = {0x01,0x06,0x38,0x0e,0x80};
 for(int i=0;i<5;i++)
 {
  PORTD = f[i];
  cmd();
 }
}

void disp_int(int x) // Integer display on LCD
{
  int y=1;
  int a=x;
  while(a>9)
  {
   y = y*10;
   a = a/10;
  }
  while(y>0 )
  {
   PORTD = ((x/y)+48);
   dat();
   x = x%y;
   y = y/10;
  }
}
 
int main()
{
 DDRA = DDRB = DDRC = DDRD = 0xff; // Ports Declaration
 splfn(); 
 unsigned int x;
 while(1)
 {
  ADMUX = 0b01000000;             // Register of ADC
  ADCSRA = 0b11101110;            // Register of ADC
  x = ADC;
  while(!(ADCSRA & (1<<ADIF)));   // Analog to Digital Conversion
  disp_int(x);                    // Displaying digital value on LCD   
  _delay_ms(100);
  if(x <= 72)
  { 
   PORTB =  0x00;                  // Driving Motor
   _delay_ms(100);
  }
  else
  { 
   PORTB = 0x01;
   _delay_ms(100);
  }
  PORTD = 0x01;                   // Clearing Screen of LCD
  cmd();
 }
return 0;
}
