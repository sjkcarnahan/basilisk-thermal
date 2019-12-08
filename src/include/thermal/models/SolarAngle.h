#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"
#include "dynamics/messages/ScPlusStatesSimMsg.h"
#include "environment/messages/SpicePlanetStateSimMsg.h"

#include "thermal/messages/BetaAngleMsg.h"
#include "thermal/thermalTypes.h"

/* Produce Beta Angle of orbit. i.e. angle between planet-sun line and orbit plane
 * It is assumed that the spacecraft is in orbit about the planet, otherwise it may be nonsense*/
class BetaAngle : public SysModel {
public:
    BetaAngle();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    SimMessage<BetaAngleMsg> outputMsg;
    ReadFunctor<ScPlusStatesSimMsg> readScStates;
    ReadFunctor<SpicePlanetStateSimMsg> readSunState;
    ReadFunctor<SpicePlanetStateSimMsg> readPlanetState;
    AngleRadian_t initialBeta;
private:
    WriteFunctor<BetaAngleMsg> writeOutputMsg;
};
