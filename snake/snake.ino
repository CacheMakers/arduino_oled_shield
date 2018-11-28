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

#define MAX_SIZE 20

#define FRAME_DELAY 5
int frameCnt = 0;

char xs[MAX_SIZE];
char ys[MAX_SIZE];

// 0=up,1=right,2=down,3=left
int dir = 0; 

void setup()   
{                
  Serial.begin(9600);

  // use internal 3.3v, and set the i2c address of the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // set buzzer to output, and each of the buttons to input_pullup
  pinMode(buzz , OUTPUT);
  digitalWrite(buzz, LOW);
  for(int i=5; i<=12; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }

  // initialize all position arrays to -1
  for(int i=0; i<MAX_SIZE; i++)
  {
    xs[i] = -1;
    ys[i] = -1;
  }

  // place initial snake
  xs[0] = 32;
  ys[0] = 16;
  xs[1] = 32;
  ys[1] = 17;
}

void loop() 
{
  if(frameCnt >= 5)
  {
    for(int i=MAX_SIZE-1; i>0; i++)
    {
      if(xs[i] >= 0)
      {
        xs[i]=xs[i-1];
        ys[i]=ys[i-1];
      }
    }
  
    if(dir == 0)
    {
      ys[0]++;
    }
    frameCnt = 0;
  }
  else
  {
    frameCnt++;
  }
  
  display.clearDisplay();
  for(int i=0; i<MAX_SIZE; i++)
  {
    if(xs[i] >= 0)
    {
      display.drawRect(xs[i]*2,ys[i]*2,2,2,WHITE);
    }
  }
  display.display();
}
