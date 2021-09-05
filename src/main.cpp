#include <Arduino.h>
#include <M5Stack.h>
#include <Avatar.h>
#include <ESP8266SAM.h>
#include <AudioOutputI2S.h>
#define MAX_LENGTH 32

using namespace m5avatar;

Avatar avatar;
AudioOutputI2S *out = NULL;
char message[MAX_LENGTH];
char input;
int pos = 0;

void setup() {
  m5.begin();
  out = new AudioOutputI2S(0, 1);
  out->begin();
  avatar.init();
}

void speak(char msg[]){
  ESP8266SAM *sam = new ESP8266SAM;
  avatar.setMouthOpenRatio(0.4);
  sam->Say(out, msg);
  avatar.setMouthOpenRatio(0.4);
  avatar.setMouthOpenRatio(0);
  delete sam;
}

void loop() {
  
  while(Serial.available() > 0){
    input = Serial.read();
    if(input != '\n' && (pos < MAX_LENGTH -1)){
      message[pos] = input;
      pos++;
    }else {
      message[pos] = '\0';
      Serial.println(message);
      speak(message);
      pos = 0;
    }
  }
  avatar.setExpression(Expression::Neutral);
}