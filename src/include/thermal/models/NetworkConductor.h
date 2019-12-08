#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"

#include "thermal/thermalTypes.h"
#include "thermal/models/HeatPath.h"

class NetworkConductor: public HeatPath {
public:
    NetworkConductor();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;
};
