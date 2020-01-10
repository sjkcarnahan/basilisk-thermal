#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/thermalTypes.h"
#include "thermal/messages/HeatRateMsg.h"

/* A constant heat source */
class HeatSource: public SysModel {
public:
    HeatSource();
    void setProcess(SysProcess* proc) override;
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    HeatRate_t heatRate;  // conductance of the pathway from up to down node
    SimMessage<HeatRateMsg> heatRateMsg;

private:
    WriteFunctor<HeatRateMsg> writeHeatRate;
};
