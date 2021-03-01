#include <FastLED.h>

#define NUM_LEDS    56

CRGB first[NUM_LEDS];
CRGB second[NUM_LEDS];

unsigned long previousMillis = 0;        // will store last time turn signal was updated
unsigned long previousled = 0;
unsigned long currentMillis = 0;
const long interval = 500;           // interval at which to blink (milliseconds)
boolean turnstate = false;
boolean signalmove = false;
int ledinterval = 5;

boolean nextled = false;
boolean knightriderstate = false;
boolean drlstate = false;
boolean blinkerstate = false;
boolean started = false;
boolean tetris = false;
boolean sens1 = false;
boolean sens2 = false;
boolean firsttime = true;

boolean fastturn1 = false;
boolean fastturn2 = false;



void setup() {
Serial.begin(9600);
FastLED.addLeds<NEOPIXEL, 10>(first, NUM_LEDS);
FastLED.addLeds<NEOPIXEL, 9>(second, NUM_LEDS);

pinMode(13, INPUT_PULLUP);    // indicator switch
pinMode(12, INPUT_PULLUP);    // indicator switch
pinMode(2, OUTPUT);           //normal indicators 1
pinMode(5, OUTPUT);           //normal indicators 2

  
}

void knightrider(){
  if(knightriderstate == false){
  for(int i = 0; i<56; i++){
    first[i] = CRGB(50,0,0);
    second[i] = CRGB (50,0,0);
    FastLED.show();
    delay(44);
    knightriderstate = true;
  }
  delay(500);
  }else if(knightriderstate == true){
    for(int i = 56; i>0; i--){
    first[i] = CRGB(0,0,0);
    second[i] = CRGB (0,0,0);
    FastLED.show();
    delay(50);
    knightriderstate = false;
    }
  }
}

void drl(){
  if(drlstate == false){
  for(int i = 0; i<56; i++){
    first[i] = CRGB (80,80,80);
    second[i] = CRGB (80,80,80);
  }
    
  }
  FastLED.show();
  drlstate = true;
  firsttime = true;
}

void blinkerone(){
  if(fastturn1 == false){
    currentMillis = currentMillis+1 - previousMillis;
    fastturn1 = true;
  }

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
 
    // if the LED is off turn it on and vice-versa:
    if (blinkerstate == false){
      blinkerstate = true;
    }else{
      blinkerstate = false;
    }

      if(blinkerstate == true){
        digitalWrite(5, LOW);
      for(int j = 0; j<NUM_LEDS; j++){
      first[j] = CRGB(10,10,10);
      }FastLED.show();
      for(int i = 0; i<NUM_LEDS; i++){
      first[i] = CRGB(140,50,0);
      FastLED.show();
      delay(5);
      }delay(100);
      for(int i = 0; i<NUM_LEDS; i++){
        first[i] = CRGB(10,10,10);
      }FastLED.show();
      digitalWrite(5, HIGH);
      
  }
        
      
}
  
}




void blinkersecond(){
  if(fastturn2 == false){
    currentMillis = currentMillis+1 - previousMillis;
    fastturn2 = true;
  }

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
 
    // if the LED is off turn it on and vice-versa:
    if (blinkerstate == false){
      blinkerstate = true;
    }else{
      blinkerstate = false;
    }

      if(blinkerstate == true){
      digitalWrite(2, LOW);
      for(int j = 0; j<NUM_LEDS; j++){
      second[j] = CRGB(10,10,10);
      }FastLED.show();
      for(int i = 0; i<NUM_LEDS; i++){
      second[i] = CRGB(140,50,0);
      FastLED.show();
      delay(5);
      }delay(100);
      for(int i = 0; i<NUM_LEDS; i++){
        second[i] = CRGB(10,10,10);
      }FastLED.show();
      digitalWrite(2, HIGH);
      
  }
        
      
}
  
}


void legal(){

  int sensor1 = digitalRead(13);
  int sensor2 = digitalRead(12);
  if(sensor1 == 0){
    sens1 = true;
      if(sens2 == true){
      sens2 = false;
      digitalWrite(2, LOW);
      drl();
      }
    blinkerone();
    fastturn2 = false;
    drlstate = false;
  }else if(sensor2 == 0){
    sens2 = true;
    digitalWrite(5, LOW);
      if(sens1 == true){
        sens1 = false;
        drl();
      }
    blinkersecond();
    fastturn1 = false;
    drlstate = false;
  }else{
    fastturn1 = false;
    fastturn2 = false;
    drl();
    digitalWrite(2, LOW);
    digitalWrite(5, LOW);
}

}

void startup(){
  if(tetris == false){
        for(int i = 0; i<NUM_LEDS; i++){
        first[i] = CRGB (0,80,0);
        second[i] = CRGB(0,80,0);
        FastLED.show();
        delay(10);
        }
        tetris = true;
  }else if(tetris == true){
          delay(200);
          for(int j = 0; j<NUM_LEDS; j++){
          first[j] = CRGB(80,80,80);
          second[j] = CRGB(80,80,80);
          }
          FastLED.show();
          started = true;
        
  }
      
    
}



void loop() {

currentMillis = millis();
Serial.print(blinkerstate);
  if(started == false){
startup();
  }else{ 
legal();

  }
}
