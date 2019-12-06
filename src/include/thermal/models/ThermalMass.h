#pragma once

#include <vector>

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/messages/TemperatureMsg.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/thermalTypes.h"

class ThermalMass: public SysModel {
public:
    ThermalMass();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Temperature_t temperature;
    Mass_t mass;
    SpecificHeat_t c_p;
    SimMessage<TemperatureMsg> outputTemperatureMsg;

public:
    void addUpstreamHeatRate(ReadFunctor<HeatRateMsg> reader);
    void addDownstreamHeatRate(ReadFunctor<HeatRateMsg> reader);

private:
    std::vector<ReadFunctor<HeatRateMsg>> upstreamHeatRateReaders;
    std::vector<ReadFunctor<HeatRateMsg>> downstreamHeatRateReaders;
    WriteFunctor<TemperatureMsg> writeTemperatureMsg;
    uint64_t previous_time;
};
