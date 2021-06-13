#include <reg51.h>
#define lcd P2

sbit rw = P0 ^ 6;
sbit rs = P0 ^ 5;
sbit en = P0 ^ 7;

void delay(unsigned int time){
    for (int i = 0; i < time; i++)
        ;
    for (int j = 0; j < 1275; j++)
        ;
}

void lcd_cmd (unsigned char cmd){
    lcd = cmd; 
    rs = 0;
    rw = 0; 
    en = 1;
    delay(10);
    en = 0;
}

void lcd_init(){
    lcd_cmd(0x38);
    lcd_cmd(0x0c);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void lcd_data(unsigned char data){
    lcd = data;
    rs = 1;
    rw = 0;
    en = 1;
    delay(5);
    en = 0;
}

void lcd_string(char *s){
    while(*s){
        lcd_data(*s++);
    }
}
void main(){
    lcd_init();
    while(1){
    lcd_string("Academic City");
    lcd_cmd(0xc0);
    lcd_string("presents");
    delay(2000);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string("Fire and Smoke");
    }
}
