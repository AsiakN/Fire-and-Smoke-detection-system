// Program for LCD Interfacing with 8051 Microcontroller (AT89S52) 
#include<reg51.h>
#define display_port P2      //Data pins connected to port 2 on microcontroller
sbit rs = P3^2;  //RS pin connected to pin 2 of port 3
sbit rw = P3^3;  // RW pin connected to pin 3 of port 3
sbit e =  P3^4;  //E pin connected to pin 4 of port 3
sbit buzzer = P0^0 //buzzer connected to port 0 bit 0
sbit fsensor = P1^6 //connection of flame sensor
sbit motor =  P1^7 //motor connection
sbit gsensor = P1^4  //gas sensor connection
sbit LED = P0^2     //bulb connection

void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)    
    for(j=0;j<1275;j++);
}
void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    display_port = command;
    rs= 0;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = disp_data;
    rs= 1;
    rw=0;
    e=1;
    msdelay(1);
    e=0;
}

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(10);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    msdelay(10);
    lcd_cmd(0x01);  //clear screen
    msdelay(10);
    lcd_cmd(0x81);  // bring cursor to position 1 of line 1
    msdelay(10);
}
 
void flame_detection() //function  for flame detection
{
        if(fsensor) {
            cmd(0xc0);
            lcd_string("Flame Detected");
            delay();
            buzzer() ;//call the buzzer function
            pump() ;   //call the turn on pump function
            bulb();    //call the turn on bulb function  
        } else {
            cmd(0xc0);
            lcd_string("                ");
        }
void main()
{
    buzzer = 0
    fsensor = 0
    gsensor = 0
    unsigned char a[15]="CIRCUIT DIGEST";    //string of 14 characters with a null terminator.
    int l=0;
    lcd_init();
    while(a[l] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(a[l]);
        l++;
        msdelay(50);
    }
}

 