#pragma once

#include <vector>

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/messages/TemperatureMsg.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/thermalTypes.h"

class ThermalEmitter: public SysModel {
public:
    ThermalEmitter();
    void setProcess(SysProcess* proc) override;
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Area_t area;
    Emittance_t epsilon;
    ReadFunctor<TemperatureMsg> readUpstreamTemperature;
    SimMessage<HeatRateMsg> outputHeatRateMsg;
    Temperature_t initialTemperature;

private:
    WriteFunctor<HeatRateMsg> writeHeatRateMsg;
};
