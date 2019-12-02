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
#define _USE_MATH_DEFINES
#include <cmath>
#include <Eigen/Dense>
#include "thermal/models/betaAngle.h"

BetaAngle::BetaAngle() :
    initialBeta(0)
    {this->writeOutputMsg = this->outputMsg.get_writer();}

void BetaAngle::initialize(){this->writeOutputMsg({this->initialBeta});}

void BetaAngle::UpdateState(uint64_t CurrentSimNanos) {
    Eigen::Vector3d scPos(this->readScStates().r_BN_N);
    Eigen::Vector3d scVel(this->readScStates().v_BN_N);
    Eigen::Vector3d sunPos(this->readSunState().PositionVector);
    Eigen::Vector3d planetPos(this->readPlanetState().PositionVector);

    Eigen::Vector3d nHat = (scPos.cross(scVel)).normalized();  // orbit normal
    Eigen::Vector3d sHat = (planetPos - sunPos).normalized();
    AngleRadian_t beta = M_PI / 2 - std::acos(nHat.dot(sHat));
    this->writeOutputMsg({beta});
}