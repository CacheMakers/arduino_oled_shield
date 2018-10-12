//#include <SPI.h>
//#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int buzz = 4;

int bA = 5;
int bX = 6;
int bB = 7;
int bY = 8;

int rgt = 9;
int up  = 10;
int dwn = 11;
int lft = 12;

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
}

void loop() 
{
  display.clearDisplay();
  display.fillCircle(64,32,10,WHITE);
  display.display();
}
