#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/thermalTypes.h"
#include "thermal/messages/ConductanceMsg.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/messages/TemperatureMsg.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/models/NetworkMass2.h"

class HeatPath: public SysModel {
public:
    HeatPath(){};
    void initialize() override {};
    void setUpstream(NetworkMass2* mass){this->upstream = mass;}
    void setDownstream(NetworkMass2* mass){this->downstream = mass;}
public:
    Conductance_t conductance;  // conductance of the pathway from up to down node
    ReadFunctor<TemperatureMsg> readUpstreamTemperature;
    ReadFunctor<TemperatureMsg> readDownstreamTemperature;
    SimMessage<HeatRateMsg> heatRateMsg;
    SimMessage<ConductanceMsg> conductanceMsg;
    HeatRate_t initialHeatRate;
    WriteFunctor<HeatRateMsg> writeHeatRate;
    WriteFunctor<ConductanceMsg> writeConductance;
    NetworkMass2* upstream = nullptr;
    NetworkMass2* downstream = nullptr;
};
