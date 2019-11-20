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
#include <math.h>
#include "thermal/thermalConstants.h"
#include "thermal/models/solarHeating.h"

double positiveDotProduct(Eigen::Vector3d v1, Eigen::Vector3d v2){
    double dot = v1.dot(v2);
    return dot > 0 ? dot : 0;
}

SolarHeating::SolarHeating() :
    area(1),
    alpha(1),
    nHat_B({1, 0, 0})
    {
    this->writeHeatRateMsg = this->outputHeatRateMsg.get_writer();
    }

void SolarHeating::UpdateState(uint64_t CurrentSimNanos){
    Eigen::Vector3d sunHeading = Eigen::Vector3d(this->readSunHeading().rHat_XB_B);
    double dot = positiveDotProduct(this->nHat_B, sunHeading);
    Flux_t flux = this->readSolarFlux().flux;
    HeatRate_t heatRate = dot * flux * this->area;
    this->writeHeatRateMsg({heatRate});
}