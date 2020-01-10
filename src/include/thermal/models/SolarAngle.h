#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "dynamics/messages/ScPlusStatesSimMsg.h"

#include "environment/messages/SpicePlanetStateSimMsg.h"

#include "thermal/messages/SolarAngleMsg.h"
#include "thermal/thermalTypes.h"

/* Produce Solar Angle (Theta). i.e. angle between planet-sun line and planet-sc line IN THE ORBIT PLANE
 * It is assumed that the spacecraft is in orbit about the planet, otherwise it may be nonsense*/
class SolarAngle : public SysModel {
public:
    SolarAngle();
    void setProcess(SysProcess* proc) override;
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    SimMessage<SolarAngleMsg> outputMsg;
    ReadFunctor<ScPlusStatesSimMsg> readScStates;
    ReadFunctor<SpicePlanetStateSimMsg> readSunState;
    ReadFunctor<SpicePlanetStateSimMsg> readPlanetState;
    AngleRadian_t initialTheta;

private:
    WriteFunctor<SolarAngleMsg> writeOutputMsg;
};
