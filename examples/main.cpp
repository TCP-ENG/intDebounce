#include <Arduino.h>
#include "intdebounce.h"


void button_up()
{
  Serial.println("up button");
  if(digitalRead(4) == HIGH)
  {
    Serial.println("relaesed");
  }
  else{
    Serial.println("pressed");
  }
}

void button_down()
{
  Serial.println("down button");
  if(digitalRead(5) == HIGH)
  {
    Serial.println("relaesed");
  }
  else{
    Serial.println("pressed");
  }
}

void button_mode()
{
  Serial.println("mode button");
  if(digitalRead(6) == HIGH)
  {
    Serial.println("relaesed");
  }
  else{
    Serial.println("pressed");
  }
}

intdebounce iDB;
void setup() {
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial.available())
  {
    /* code */
  }
  
  iDB.setupPin(4,button_up,50);
  iDB.setupPin(5,button_down,50);
  iDB.setupPin(6,button_mode,50);

}
void loop() {
  // put your main code here, to run repeatedly:
  iDB.handleTimers();
  
}

