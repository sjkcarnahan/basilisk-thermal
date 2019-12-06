#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/thermalTypes.h"
#include "thermal/messages/TemperatureMsg.h"
#include "thermal/messages/HeatRateMsg.h"

class ThermalConductor: public SysModel {
public:
    ThermalConductor();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Conductance_t conductance;  // conductance of the pathway from up to down node
    ReadFunctor<TemperatureMsg> readUpstreamTemperature;
    ReadFunctor<TemperatureMsg> readDownstreamTemperature;
    SimMessage<HeatRateMsg> heatRateMsg;
    HeatRate_t initialHeatRate;

private:
    WriteFunctor<HeatRateMsg> writeHeatRate;
};
