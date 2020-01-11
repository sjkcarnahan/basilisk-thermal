#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/thermalTypes.h"
#include "thermal/messages/ConductanceMsg.h"
#include "thermal/messages/TemperatureMsg.h"
#include "thermal/messages/HeatRateMsg.h"

class RadiationConductor: public SysModel {
public:
    RadiationConductor();
    void setProcess(SysProcess* proc) override;
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Conductance_t conductance;  // conductance of the pathway from up to down node
    ReadFunctor<TemperatureMsg> readUpstreamTemperature;
    ReadFunctor<TemperatureMsg> readDownstreamTemperature;
    SimMessage<HeatRateMsg> heatRateMsg;
    SimMessage<ConductanceMsg> conductanceMsg;
    HeatRate_t initialHeatRate;
    Emittance_t epsilonUp;
    Emittance_t epsilonDown;
    double viewFactor;
    Area_t area;

private:
    WriteFunctor<HeatRateMsg> writeHeatRate;
    WriteFunctor<ConductanceMsg> writeConductance;
};
