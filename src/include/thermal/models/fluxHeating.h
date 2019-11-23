/*
 ISC License

 Copyright (c) 2016, Autonomous Vehicle Systems Lab, University of Colorado at Boulder

 Permission to use, copy, modify, and/or distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

 */

#pragma once

#include <vector>
#include <Eigen/Dense>
#include "framework/system_models/sys_model.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/messaging/message.h"
#include "dynamics/messages/ScPlusStatesSimMsg.h"
#include "environment/messages/FluxSimMsg.h"
#include "navigation/messages/BodyHeadingSimMsg.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/thermalTypes.h"

class FluxHeating: public SysModel {
public:
    FluxHeating();
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    Area_t area;
    Absorptance_t alpha;
    ReadFunctor<ScPlusStatesSimMsg> readScStates;  //!< Mostly to get attitude info
    ReadFunctor<FluxSimMsg> readSolarFlux;
    ReadFunctor<BodyHeadingSimMsg> readSunHeading;
    SimMessage<HeatRateMsg> outputHeatRateMsg;
    Eigen::Vector3d nHat_B;  //!< surface normal in sc body frame

private:
    WriteFunctor<HeatRateMsg> writeHeatRateMsg;
};
