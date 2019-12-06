#pragma once

#include <vector>
#include "framework/system_models/sys_model.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/messaging/message.h"
#include "thermal/messages/TemperatureMsg.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/thermalTypes.h"

class ArithmeticEmitter: public SysModel {
public:
    ArithmeticEmitter();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Temperature_t temperature;
    Emittance_t epsilon;
    Area_t area;
    SimMessage<TemperatureMsg> outputTemperatureMsg;

public:
    void addUpstreamHeatRate(ReadFunctor<HeatRateMsg> reader);
    void addDownstreamHeatRate(ReadFunctor<HeatRateMsg> reader);
    ReadFunctor<TemperatureMsg> readNearestTemperature;

private:
    std::vector<ReadFunctor<HeatRateMsg>> upstreamHeatRateReaders;
    std::vector<ReadFunctor<HeatRateMsg>> downstreamHeatRateReaders;
    WriteFunctor<TemperatureMsg> writeTemperatureMsg;
};
