#include<reg51.h>

void delay(unsigned int i);
void lcd_cmd(unsigned char a);
void lcd_data(unsigned char b);
void lcd_init(void);
void lcd_str(unsigned char *str);
sbit rs = P2^0;
sbit en = P2^1;
sfr ldata = 0xb0; // port3
sbit rd = P2^2;
sbit wr = P2^3;
sbit intr = P2^4;
sfr adc = 0x90; // port1

sbit dcMotor = P2^5; // Assuming P2.5 controls the DC motor
sbit dcMotor2 = P2^6;

void hex2ascii(unsigned char value);

void main()
{
    lcd_init();
    lcd_str("   WELCOME TO   ");
    lcd_cmd(0xc0);
    lcd_str("   MY PROJECT   ");
    
    delay(65000);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_str("   rollno.67   ");
    lcd_cmd(0xc0);
    lcd_str("   rollno.63   ");
    delay(65000);
    lcd_cmd(0x01);
    
    while(1)
    {
        rd = 1;
        wr = 0;
        delay(100);
        wr = 1;
        while(intr == 1); // Wait until conversion is finished
        delay(100);
        rd = 0;
        lcd_cmd(0x8c);
        hex2ascii(adc * 2);
        intr = 1; // Start the next conversion 
        
        // Check if temperature is greater than 35 degrees Celsius
        if (adc * 2 > 35)
        {
					
            dcMotor = 1; // Turn on the DC motor
					delay(10000);
						dcMotor2=1;
					delay(10000);
        }
        else
        {
            dcMotor = 0; // Turn off the DC motor
						dcMotor2=0;
        }
    }
}

// Rest of your code...
void hex2ascii(unsigned char value)//0xff-255
{
	unsigned char x,d1,d2,d3;
	x=value/10;//25
	d3=value%10;//5
	d2=x%10;//5
	d1=x/10;//2
	lcd_data(d1+0x30);
lcd_data(d2+0x30);
	lcd_data(d3+0x30);


}
void lcd_init()
{
lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
	lcd_cmd(0x80);


}
void delay(unsigned int i)
{
unsigned int j;
	for(j=0;j<i;j++);
}

void lcd_cmd(unsigned char a)
{
  rs=0;//cmd 
	ldata=a;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_data(unsigned char b)
{
  rs=1;//data 
	ldata=b;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_str(unsigned char *str)
{
while(*str)
{
	lcd_data(*str++);
}}