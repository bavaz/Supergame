#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>
#include "structure.h"

//#define RLED RED_LED
//#define GLED GREEN_LED
//#define Potentiometer PE_3
//#define btn PE_0



void GameUIInit();

void GameUITick();

//extern const uint32_t Potentiometer;

void setup() {
 
  GameUIInit();
  //pinMode(btn,INPUT);
  //pinMode(RLED,OUTPUT);
  //pinMode(GLED,OUTPUT);
  Serial.begin(9600);

  // Read some analog signal and scale it arbitarily
  // for random seed.
  srand((7+analogRead(Potentiometer)) * 347);
}

void loop() {
  GameUITick();
  
  
}
