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

// grid size
short gs = 8;

// arena limits
int lim_rgt = 128/gs-1;
int lim_bot = 64/gs-1;

// snake location
short snakeX[40] = {8,7,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
short snakeY[40] = {6,6,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
short snakeLen = 3;

// snake direction
short dir = 2;

// apple location
short appleX = 4;
short appleY = 4;

// set framerate
int frame_delay = 5;
int frame_count = 0;

bool gameOver = false;

void setup()   
{                
  Serial.begin(9600);

  // use internal 3.3v, and set the i2c address of the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // set buzzer to output, and each of the buttons to input_pullup
  pinMode(buzz , INPUT);
  for(int i=5; i<=12; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() 
{
  // get player input
  if(digitalRead(rgt) == LOW && dir != 2)
  {
    dir = 0;
  }
  if(digitalRead(up) == LOW && dir != 3)
  {
    dir = 1;
  }
  if(digitalRead(lft) == LOW && dir != 0)
  {
    dir = 2;
  }
  if(digitalRead(dwn) == LOW && dir != 1)
  {
    dir = 3;
  }

  frame_count++;
  if(frame_count > frame_delay)
  {
    // eat apple
    if(snakeX[0] == appleX && snakeY[0] == appleY && snakeLen < 40)
    {
      snakeX[snakeLen] = snakeX[snakeLen-1];
      snakeY[snakeLen] = snakeY[snakeLen-1];
      snakeLen++;
      appleX = random(lim_rgt+1);
      appleY = random(lim_bot+1);
    }
    
    // update snake
    for(int i=39; i>0; i--)
    {
      if(snakeX[i] > 0)
      {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
      }
    }
    
    switch(dir)
    {
      case 0:
        if(snakeX[0] < lim_rgt)
        {
          snakeX[0]++;
        }
        else
        {
          gameOver = true;
        }
        break;
      case 1:
        if(snakeY[0] > 0)
        {
          snakeY[0]--;
        }
        else
        {
          gameOver = true;
        }
        break;
      case 2:
        if(snakeX[0] > 0)
        {
          snakeX[0]--;
        }
        else
        {
          gameOver = true;
        }
        break;
      case 3:
        if(snakeY[0] < lim_bot)
        {
          snakeY[0]++;
        }
        else
        {
          gameOver = true;
        }
        break;
    }
    
    frame_count = 0;
  }

  display.clearDisplay();
  
  // draw apple
  display.fillRect(appleX*gs,appleY*gs,gs,gs,WHITE);

  // draw snake
  bool ended = false;
  for(int i=0; i<40 && !ended; i++)
  {
    if(snakeX[i] < 0)
    {
      ended = true;
    }
    else
    {
      display.fillRect(snakeX[i]*gs,snakeY[i]*gs,gs,gs,WHITE);
    }
  }
  display.display();
}
