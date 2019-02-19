#include "Arduino.h"
#include "CBlocks.h"
#include "VibrationMotor.h"
#include "Command.h"
#include "UpdateTimer.h"

namespace CBlocks{
  unsigned int VibrationMotor::percentage = 0;

  VibrationMotor::VibrationMotor(CBlocks* cblocks) :
    cblocks(cblocks) {
      drv = new Adafruit_DRV2605();
      updateTimer = new UpdateTimer(UPDATE_INTERVAL_IN_MS);
    };

  void VibrationMotor::begin(){
    drv->begin();
    drv->setMode(DRV2605_MODE_REALTIME);

    cblocks->registerCommand(PERCENTAGE_RESOURCE, percentageCommandCallback);
  }

  void VibrationMotor::publishStatus(){
    cblocks->heartBeat();
    vibrate();

    if(updateTimer->updateIntervalExceeded()){
      cblocks->updateResource(PERCENTAGE_RESOURCE, VibrationMotor::percentage);
    }
  }

  void VibrationMotor::vibrate(){
    drv->setRealtimeValue(percentage);
  }

  CommandResponse VibrationMotor::percentageCommandCallback(JsonObject &json){
    percentage = json["data"];

    return CommandResponse::getSuccessCommandResponseFor(json["requestID"]);
  }
}
