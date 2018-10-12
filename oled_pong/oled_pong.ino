//#include <SPI.h>
//#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int upL = 9;
int dnL = 10;
int upR = 11;
int dnR = 12;

int ballX = 64;
int ballY = 32;
int velX = 4;
int velY = 4;

int padW = 5;
int padH = 25;

int padL = 32;
int padR = 32;

int spdL = 1;
int spdR = 1;

void setup()   
{                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // changed this to 0x3C to make it work

  pinMode(upL, INPUT_PULLUP);
  pinMode(dnL, INPUT_PULLUP);
  pinMode(upR, INPUT_PULLUP);
  pinMode(dnR, INPUT_PULLUP);
}

void loop() 
{
  ballX += velX;
  ballY += velY;

  if(ballX >= 128 || ballX <= 0)
  {
    velX = -velX;
  }
  if(ballY >= 64 || ballY <= 0)
  {
    velY = -velY;
  }

  if(digitalRead(upL) == LOW)
  {
    padL -= spdL;
  }
  if(digitalRead(dnL) == LOW)
  {
    padL += spdL;
  }
  if(digitalRead(upR) == LOW)
  {
    padR -= spdR;
  }
  if(digitalRead(dnR) == LOW)
  {
    padR += spdR;
  }
  
  display.clearDisplay();
  display.fillCircle(ballX, ballY, 2, WHITE);
  display.fillRect(10,padL-(padH/2),padW,padH, WHITE);
  display.fillRect(118,padR-(padH/2),padW,padH, WHITE);
  display.display();
  delay(1);
}
