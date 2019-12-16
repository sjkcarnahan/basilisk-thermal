#pragma once

#include <vector>

#include <Eigen/Dense>

#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/messaging/message.h"
#include "framework/system_models/sys_model.h"
#include "dynamics/messages/ScPlusStatesSimMsg.h"
#include "environment/messages/FluxSimMsg.h"
#include "navigation/messages/BodyHeadingSimMsg.h"

#include "thermal/messages/HeatRateMsg.h"
#include "thermal/thermalTypes.h"

class FluxHeating: public SysModel {
public:
    FluxHeating();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Area_t area;
    /* Note: while absorptance often refers to the visible spectrum, here it is used to be the
     * absorptance in the same band as the flux provided.*/
    Absorptance_t alpha;
    ReadFunctor<FluxSimMsg> readFlux;
    ReadFunctor<BodyHeadingSimMsg> readSourceHeading;
    SimMessage<HeatRateMsg> outputHeatRateMsg;
    Eigen::Vector3d nHat_B;  //!< surface normal
    Flux_t initialHeatRate; //!< will be written in initialize()

private:
    WriteFunctor<HeatRateMsg> writeHeatRateMsg;
};
