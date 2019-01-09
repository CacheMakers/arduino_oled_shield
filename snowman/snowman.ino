//#include <SPI.h>
//#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int buzz = 4;

const byte bA = 5;
const byte bX = 6;
const byte bB = 7;
const byte bY = 8;

const byte rgt = 9;
const byte up  = 10;
const byte dwn = 11;
const byte lft = 12;

int frameCount = 0;
int headX = 64;
bool headR = true;
int midX = 64;
int botX = 64;

class Snowflake
{
  public:
    byte x;
    byte y;
    Snowflake()
    {
      x = -1;
      y = -1;
    }
    Snowflake(char xIn, char yIn)
    {
      x = xIn;
      y = yIn;
    }
};

Snowflake snowflakes[200];

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
  snowflakes[0].x = 10;
  snowflakes[0].y = 10;
}

void loop() 
{
  frameCount++;
  if(frameCount >= 500)
  {
    botX = midX;
    midX = headX;
    if(headX == 64)
    {
      if (headR)
      {
        headX = 66;
      }
      else
      {
        headX = 62;
      }
      headR = !headR;
    }
    else if(headX == 66 || headX == 62)
    {
      headX = 64;
    }
    
    display.clearDisplay();
    display.fillRect(0,60,128,64,WHITE);              //ground
    display.fillCircle(headX,20,8,WHITE);             //top
    display.fillCircle(midX,32,10,WHITE);             //middle 
    display.fillCircle(botX,48,12,WHITE);             //bottom
    display.fillCircle(headX,22,4,BLACK);             //mouth
    display.fillRect(headX-4,18,9,4,WHITE);           //mouth top
    display.fillCircle(headX-2,18,1,BLACK);           //left eye
    display.fillCircle(headX+2,18,1,BLACK);           //right eye
    display.fillCircle(midX,30,1,BLACK);              //button1
    display.fillCircle(midX,34,1,BLACK);              //button2
    display.fillCircle(midX,38,1,BLACK);              //button3
    display.drawLine(midX+12,32,midX+22,28,WHITE);    //right arm
    display.drawLine(midX-12,32,midX-22,28,WHITE);    //left arm
    
    display.display();
    frameCount = 0;
  }
  else
  {
    delay(1);
  }
}
