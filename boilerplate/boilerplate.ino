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
  display.clearDisplay();
  display.fillCircle(64,32,10,WHITE);
  display.display();
}
