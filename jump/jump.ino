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

byte pX = 32;
byte pY = 60;
byte pW = 8; 
byte pH = 8;
byte vY = 0;
int oX = -10;
int oX2 = -10;
byte oW = 2;
byte oH = 20;

int score = 0;

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
   if(digitalRead(bX) == LOW && pY >= 60)
   {

     vY = -8;
   }
   pY += vY;
   vY += 1;
   if(pY >= 60)
   {
    pY = 60;
    vY = 0;
   }

   if(oX <= -10)
   {
     if(random(2) == 1)
     {
      oX = 128+random(50);
     }
   } 
   else
   {
      oX -= 3;
   }

   if(o2X <= -10)
   {
     if(random(2) == 1)
     {
      o2X =128+random(50);
     }
   } 
   else
   {
      o2X -= 3;
   }


if((pX-pW<oX && oX-oW<pX && pY>40)||(pX-pW<oX2 && oX2-oW<pX && pY>40))
{
  Serial.println("crash");
  score = 0; 
}
else
{
  score++;
}
   
   
  display.clearDisplay();
  display.fillRect (pX-pW,pY-pH,  pW,  pH,WHITE);
  display.fillRect(0,     60, 128, 4, WHITE);
  display.fillRect(oX,   40,   oW,   oH, WHITE);
  display.fillRect(oX2,  40,   oW,   oH, WHITE);
  display.setCursor(100,1);
  display.setTextColor(WHITE);
  display.println(score);
  display.display();
}
