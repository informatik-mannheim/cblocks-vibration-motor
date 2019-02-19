#include "CBlocks.h"
#include "CBlocksMaker.h"
#include "VibrationMotor.h"

#define BAUD_RATE 115200
#define OBJECT_ID 3307
#define INSTANCE_ID 0

CBlocks::CBlocks* cblocks;
CBlocks::VibrationMotor* motor;

uint8_t effect = 1;

void initSerial(){
  Serial.begin(BAUD_RATE);
}

void initCBlocks(){
  cblocks = CBlocks::CBlocksMaker::make(OBJECT_ID, INSTANCE_ID);
  cblocks->begin();
}

void initSensor(){
  motor = new CBlocks::VibrationMotor(cblocks);
  motor->begin();
}

void setup(){
  initSerial();
  initCBlocks();
  initSensor();

  pinMode(21, OUTPUT);
}

void loop(){
  motor->publishStatus();
}
