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

#include "framework/system_models/sys_model.h"
#include "framework/messaging/message.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/messaging/readFunctor.h"
#include "dynamics/messages/ScPlusStatesSimMsg.h"
#include "environment/messages/SpicePlanetStateSimMsg.h"
#include "thermal/messages/BetaAngleMsg.h"
#include "thermal/thermalTypes.h"

/* Produce Beta Angle of orbit. i.e. angle between planet-sun line and orbit plane
 * It is assumed that the spacecraft is in orbit about the planet, otherwise it may be nonsense*/
class BetaAngle : public SysModel {
public:
    BetaAngle();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    SimMessage<BetaAngleMsg> outputMsg;
    ReadFunctor<ScPlusStatesSimMsg> readScStates;
    ReadFunctor<SpicePlanetStateSimMsg> readSunState;
    ReadFunctor<SpicePlanetStateSimMsg> readPlanetState;
    AngleRadian_t initialBeta;
private:
    WriteFunctor<BetaAngleMsg> writeOutputMsg;
};
