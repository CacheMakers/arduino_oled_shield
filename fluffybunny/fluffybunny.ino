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

int bodyX = 64;
int bodyY = 50;
int rFootX = 10;
int rFootY = 7;
int lFootX = -10;
int lFootY = 7;
int headX = 0;
int headY = -10;
int noseY = 0;
int rArmX = 0;
int lArmX = 0;

bool rightEyeOpen = true;
bool leftEyeOpen = true;

int hunger = 50;
bool isCarrot = false;
int carrotX = 0;

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
  draw();
}

void loop() 
{  
  int action = random(10);
  if(action == 0)
  {
    noseWiggle();
  }
  else if(action == 1)
  {
    blinkEyes();
  }
  else if(action == 2)
  {
    int dir = random(2);
    int hops = random(4);
    if(dir == 0)
    {
      for(int i=0; i<hops; i++)
      {
        hop(true);  
      }
    }
    else
    {
      for(int i=0; i<hops; i++)
      {
        hop(false);  
      }
    }
  }
  else if(action == 3)
  {
    armWiggle();
  }
  else
  {
    draw();
  }
  int hungerDecay = random(100);
  if(hungerDecay == 0)
  {
    hunger -= 1;
  }
  delay(10);
}

void armWiggle()
{
  for(int i=0; i<4; i++)
  {
    if(rArmX == 0)
    {
      rArmX = 2;
      lArmX = -2;
    }
    else
    {
      rArmX = 0;
      lArmX = 0;
    }
    delay(100);
    draw();
  }
}

void hop(bool right)
{
  rFootY+=2;
  lFootY+=2;
  if(right && bodyX < 100)
  {
    bodyX+=1;
    bodyY-=2;
    draw();
    bodyX+=1;
    bodyY-=2;
    draw();
    bodyX+=1;
    bodyY-=1;
    draw();
    bodyX+=1;
    //bodyY-=2;
    draw();
    bodyX+=1;
    bodyY+=1;
    draw();
    bodyX+=1;
    bodyY+=2;
    draw();
    bodyX+=1;
    bodyY+=2;
    draw();
  }
  else if(!right && bodyX > 25)
  {
    bodyX-=1;
    bodyY-=2;
    draw();
    bodyX-=1;
    bodyY-=2;
    draw();
    bodyX-=1;
    bodyY-=1;
    draw();
    bodyX-=1;
    //bodyY-=2;
    draw();
    bodyX-=1;
    bodyY+=1;
    draw();
    bodyX-=1;
    bodyY+=2;
    draw();
    bodyX-=1;
    bodyY+=2;
    draw();
  }
  rFootY-=2;
  lFootY-=2;
}

void blinkEyes()
{
  for(int i=0; i<4; i++)
  {
    if(rightEyeOpen == true)
    {
      rightEyeOpen = false;
      leftEyeOpen = false;
    }
    else
    {
      rightEyeOpen = true;
      leftEyeOpen = true;
    }
    delay(100);
    draw();
  }
}

void noseWiggle()
{
  for(int i=0; i<4; i++)
  {
    if(noseY == 0)
    {
      noseY = 1;
    }
    else
    {
      noseY = 0;
    }
    delay(100);
    draw();
  }
}

void draw()
{
  display.clearDisplay();
  display.fillRect(0,62,128,2,WHITE);                          // ground
  display.fillCircle(bodyX,bodyY,11,WHITE);                    // body
  display.fillCircle(bodyX+rFootX,bodyY+rFootY,4,WHITE);       // right foot
  display.fillCircle(bodyX+lFootX,bodyY+lFootY,4,WHITE);       // left foot
  display.fillCircle(bodyX+headX+5,bodyY+headY-16,4,WHITE);    // right ear
  display.fillRect(bodyX+headX+1,bodyY+headY-16,9,16,WHITE);
  display.fillCircle(bodyX+headX+5,bodyY+headY-16,2,BLACK);
  display.fillRect(bodyX+headX+3,bodyY+headY-16,5,16,BLACK);
  display.fillCircle(bodyX+headX-5,bodyY+headY-16,4,WHITE);    // left ear
  display.fillRect(bodyX+headX-9,bodyY+headY-16,9,16,WHITE);
  display.fillCircle(bodyX+headX-5,bodyY+headY-16,2,BLACK);
  display.fillRect(bodyX+headX-7,bodyY+headY-16,5,16,BLACK);
  display.fillCircle(bodyX+headX,bodyY+headY,10,WHITE);         // head
  if(rightEyeOpen == true)
  {
    display.fillCircle(bodyX+headX+3,bodyY+headY-3,2,BLACK);      // right eye
    display.drawPixel(bodyX+headX+3,bodyY+headY-3,WHITE);
  }
  if(leftEyeOpen == true)
  {
    display.fillCircle(bodyX+headX-3,bodyY+headY-3,2,BLACK);      // left eye
    display.drawPixel(bodyX+headX-3,bodyY+headY-3,WHITE);
  }
  display.drawCircle(bodyX+headX+2,bodyY+headY+2,2,BLACK);      // mouth
  display.drawCircle(bodyX+headX-2,bodyY+headY+2,2,BLACK);      
  display.fillRect(bodyX+headX-4,bodyY+headY,10,2,WHITE);
  display.fillTriangle(bodyX+headX+2,bodyY+headY+noseY,bodyX+headX-2,bodyY+headY+noseY,bodyX+headX,bodyY+headY+noseY+2,BLACK); // nose
  display.drawCircle(bodyX+rArmX+4,bodyY,3,BLACK);                    // right arm
  display.fillRect(bodyX+rArmX+1,bodyY-3,7,3,WHITE);
  display.drawCircle(bodyX+lArmX-4,bodyY,3,BLACK);                    // left arm
  display.fillRect(bodyX+lArmX-7,bodyY-3,7,3,WHITE);
  display.fillRect(3,3,hunger,2,WHITE);                         // hunger bar
  display.drawRect(2,2,52,4,WHITE);
  display.display();
}

