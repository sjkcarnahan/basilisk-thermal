#pragma once

#include <vector>

#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/messaging/message.h"
#include "framework/system_models/sys_model.h"

#include "thermal/messages/HeatRateMsg.h"
#include "thermal/messages/TemperatureMsg.h"
#include "thermal/thermalTypes.h"

/* Balances irradiance with thermal radiance to get a temperature, regardless of other conductances attached.
 * The idea is that the surface radiation vastly outweighs the attached conductances */
class ArithmeticSurface: public SysModel {
public:
    ArithmeticSurface();
    void setProcess(SysProcess* proc) override;
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Temperature_t temperature;
    Emittance_t epsilon;
    Area_t area;
    SimMessage<TemperatureMsg> outputTemperatureMsg;

public:
    void addIrradianceHeatRate(ReadFunctor<HeatRateMsg> reader);

private:
    std::vector<ReadFunctor<HeatRateMsg>> irradianceHeatRateReaders;
    WriteFunctor<TemperatureMsg> writeTemperatureMsg;
};
