// Program for LCD Interfacing with 8051 Microcontroller (AT89S52) 
#include <reg51.h>
#define lcd P2      //Data pins connected to port 2 on microcontroller
sbit rs = P3^2;  //RS pin connected to pin 2 of port 3
sbit rw = P3^3;  // RW pin connected to pin 3 of port 3
sbit e =  P3^4;  //E pin connected to pin 4 of port 3
sbit buzzer = P0^0; //buzzer connected to port 0 bit 0
sbit fsensor = P1^6; //connection of flame sensor
sbit pump = P1^7;   //motor connection
sbit gsensor = P1^4; //gas sensor connection
sbit bulb = P0^2;     //bulb connection
unsigned char a[10]= "Welcome";    //string of 14 characters with a null terminator.
int n;
void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)    
    for(j=0;j<1275;j++);
}

void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    lcd = command;
    rs= 0;
    rw=0;
    e=1;
    msdelay(1);
    e = 0;
}
void lcd_data(unsigned char data)
{
    lcd = data;
    rs = 1; 
    rw = 0;
    e = 1;
    msdelay(1);
    e = 0; 

}
void lcd_string(char *s)
{
    while(*s) {
       lcd_data(*s++);
     }
}
 

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    msdelay(5);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    msdelay(5);
    lcd_cmd(0x01);  //clear screen
    msdelay(5);
    lcd_cmd(0x80);  // bring cursor to position 1 of line 1
    msdelay(5);
}
 
void flame_detection() //function  for flame detection
{
        if(fsensor == 1) {
            lcd_cmd(0xc0);
            lcd_string("Smoke and Fire Detected");
            msdelay(100);
            buzzer = 1;//call the buzzer function
            pump = 1;   //call the turn on pump function
            bulb = 1;    //call the turn on bulb function  
        } else {
            lcd_cmd(0xc0);
            lcd_string("No fire detected");
        }

}

void smoke_detection(){
    if (gsensor==1){
        lcd_cmd(0xc0);
            lcd_string("smoke Detected");
            msdelay(100);
            buzzer = 1;
            pump = 1; 
        } else {
            buzzer = 0;
            pump = 0;
            lcd_cmd(0xc0);
            lcd_string("                ");
        }
 }

void main()
{
    buzzer = 0;
    fsensor = 0;
    gsensor = 0;
    n = 0;
    lcd_init();
    while(a[n] != '\0') // searching the null terminator in the sentence
    {
        lcd_data(a[n]);
        n++ ;
        msdelay(10);
    }
    while(1){
        flame_detection();
        smoke_detection();
    }
}

 
 