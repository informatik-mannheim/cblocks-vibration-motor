#ifndef CBLOCKS_VIBRATION_MOTOR_H
#define CBLOCKS_VIBRATION_MOTOR_H

#define PERCENTAGE_RESOURCE 0
#define UPDATE_INTERVAL_IN_MS 100

#include "Arduino.h"
#include "CBlocks.h"
#include "Command.h"
#include "UpdateTimer.h"
#include "Adafruit_DRV2605.h"

namespace CBlocks {
  class VibrationMotor {
  private:
    CBlocks* cblocks;
    Adafruit_DRV2605* drv;
    static unsigned int percentage;
    UpdateTimer* updateTimer;

    static CommandResponse percentageCommandCallback(JsonObject& json);
    void vibrate();
  public:
    VibrationMotor(CBlocks* cblocks);
    void begin();

    void publishStatus();
  };
}

#endif
