#pragma once

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"

#include "thermal/thermalTypes.h"
#include "thermal/models/HeatPath.h"

class NetworkRadiationConductor: public HeatPath {
public:
    NetworkRadiationConductor();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;
    void setConductance(Temperature_t upstreamTemperature, Temperature_t downstreamTemperature) override;

public:
    double viewFactor;
    Area_t area;
    Emittance_t epsilon_1;
    Emittance_t epsilon_2;
};
