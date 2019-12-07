#pragma once

#include <vector>

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"

#include "thermal/models/HeatPath.h"
#include "thermal/thermalTypes.h"

class NetworkEmitter: public HeatPath {
public:
    NetworkEmitter();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Area_t area;
    Emittance_t epsilon;
    Temperature_t initialTemperature;
};
