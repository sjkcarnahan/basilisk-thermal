#pragma once

#include <vector>

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/messages/TemperatureMsg.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/models/HeatPath.h"
#include "thermal/thermalTypes.h"

class NetworkMass: public SysModel {
public:
    NetworkMass();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Temperature_t temperature;
    Mass_t mass;
    SpecificHeat_t c_p;
    SimMessage<TemperatureMsg> outputTemperatureMsg;

public:
    void addUpstreamRate(ReadFunctor<HeatRateMsg> reader);
    void addDownstreamRate(ReadFunctor<HeatRateMsg> reader);
//    void addUpstreamPath(NetworkSolver* path){};
//    void addDownstreamPath(HeatPath* path);

private:
    std::vector<ReadFunctor<HeatRateMsg>> upstreamHeatRateReaders;
    std::vector<ReadFunctor<HeatRateMsg>> downstreamHeatRateReaders;
//    std::vector<HeatPath*> upstreamPaths;
//    std::vector<HeatPath*> downstreamPaths;
    WriteFunctor<TemperatureMsg> writeTemperatureMsg;
};
