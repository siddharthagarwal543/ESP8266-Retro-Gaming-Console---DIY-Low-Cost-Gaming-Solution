#include <Wire.h>  
#include "SSD1306Wire.h" 

#include "images.h"
#include "fonts.h"

SSD1306Wire  display(0x3c, 4, 5);

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

float obstacle_idx[4];
int gap_height[4];
int spacing=32;
int width=30;
void setup() {
   
  Serial.println();
  Serial.println();

pinMode(2,OUTPUT);
pinMode(12,OUTPUT);
pinMode(14,INPUT_PULLUP); 
  display.init();

  for(int i=0;i<4;i++)
  {
    obstacle_idx[i]=128+((i+1)*spacing);
    {gap_height[i]=random(8,32);}
    }

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}


int score=0;
int stis=0;
float fx=30.00;
float fy=22.00;
int player_moving=0;
unsigned long moving_time=0;

int game_mode=0;
int frame=0;
int buzzer=0;
unsigned long buzzer_time=0;
void loop() {
   Serial.begin(300);  
   int tst;
   display.clear();

   if(game_mode==0)
   {
    display.setFont(ArialMT_Plain_16);
    display.drawString(0,4,"Flappy ");
   display.drawXbm(0, 0, 128, 64, background);
   display.drawXbm(20, 32, 14, 9, bird);

   display.setFont(ArialMT_Plain_10);
   display.drawString(0,44,"press to start");
    if(digitalRead(14)==0)
    game_mode=1;
    }

   if(game_mode==1)
   {
   display.setFont(ArialMT_Plain_10);
   display.drawString(3,0,String(score));
   
   if(digitalRead(14)==0)
   {
    if(stis==0)
      {
        moving_time=millis();
        player_moving=1;
        buzzer=1;
        stis=1;
        buzzer_time=millis();
       
        }
    
    }else{stis=0;}

   
    for(int j=0;j<4;j++){
       display.setColor(WHITE);
    display.fillRect(obstacle_idx[j],0,6,64);
     display.setColor(BLACK);
      display.fillRect(obstacle_idx[j],gap_height[j],6,width);
   
    }

  display.setColor(WHITE);
 //  display.fillCircle(fx, fy, 4); // game_modec
  display.drawXbm(fx, fy, 14, 9, bird);
  
    for(int j=0;j<4;j++)
    {
    obstacle_idx[j]=obstacle_idx[j]-0.01;
    if(obstacle_idx[j]<-7){
      score=score+1;
      digitalWrite(12,1);
      gap_height[j]=random(8,32);
     
    obstacle_idx[j]=128;
    }
    
    }
  if((moving_time+185)<millis())
  player_moving=0;

    if((buzzer_time+40)<millis())
  buzzer=0;

if(player_moving==0)
 fy=fy+0.01;
else
 fy=fy-0.03;


 if(buzzer==1)
 digitalWrite(12,1);
 else
 digitalWrite(12,0);

if(fy>63 || fy<0){
game_mode=0;
fy=22;
score=0;
 digitalWrite(12,1);
  delay(500);
   digitalWrite(12,0); 
for(int i=0;i<4;i++)//generates rectangle
  {
    obstacle_idx[i]=128+((i+1)*spacing);
    {gap_height[i]=random(4,30);}
    }
}

for(int m=0;m<4;m++)
if(obstacle_idx[m]<=fx+7 && fx+7<=obstacle_idx[m]+6)
{
  if(fy<gap_height[m] || fy+8>gap_height[m]+width){
  game_mode=0;
  fy=22;
  score=0;
  digitalWrite(12,1);
  delay(500);
   digitalWrite(12,0);
  for(int i=0;i<4;i++)
  {
    obstacle_idx[i]=128+((i+1)*spacing);
    {gap_height[i]=random(8,32);}
    }
  }}
   display.drawRect(0,0,128,64);
   }
   
  
  
  display.display();
  
}
