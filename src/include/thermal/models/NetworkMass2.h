#pragma once

#include <vector>

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/thermalTypes.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/messages/TemperatureMsg.h"

/* A mass whose temperature is solved by the NetworkSolver */
class NetworkMass2: public SysModel {
public:
    NetworkMass2();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;
    void addIndependentHeatRate(ReadFunctor<HeatRateMsg> rateReader);
    HeatRate_t independentHeatRate();
    Temperature_t initialTemperature;
    Mass_t mass;
    SpecificHeat_t c_p;
    Temperature_t temperature;
    uint64_t networkPosition;
    SimMessage<TemperatureMsg> temperatureMsg;

private:
    std::vector<ReadFunctor<HeatRateMsg>> independentRateReaders;
    WriteFunctor<TemperatureMsg> writeTemperature;
};
