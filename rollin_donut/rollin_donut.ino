//#include <SPI.h>
//#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

byte buzz = 4;

byte bA = 5;
byte bX = 6;
byte bB = 7;
byte bY = 8;

byte rgt = 9;
byte up  = 10;
byte dwn = 11;
byte lft = 12;

int x = -32;
int t = 0;

int getX(int t, int r)
{
  return r*cos(t*6.28/360);
}

int getY(int t, int r)
{
  return r*sin(t*6.28/360);
}

void setup()   
{                
  Serial.begin(9600);

  // use internal 3.3v, and set the i2c address of the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // set buzzer to output, and each of the buttons to input_pullup
  pinMode(buzz , OUTPUT);
  for(int i=5; i<=12; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
  display.clearDisplay();
}

void loop() 
{
  x++;
  t+=2;
  if(x >=160)
  {
    x=-32;
  }
  
  display.clearDisplay();
  display.fillCircle(x,32,30,WHITE);
  display.fillCircle(x+getX(t,20), 32+getY(t,20),5,BLACK);
  display.fillCircle(x+getX(t+120,20), 32+getY(t+120,20),5,BLACK);
  display.fillCircle(x+getX(t+240,20), 32+getY(t+240,20),5,BLACK);
  display.fillCircle(x,32,10,BLACK);
  display.display();
}
