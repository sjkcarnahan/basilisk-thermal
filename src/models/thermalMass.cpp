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

#include "thermalMass.h"

ThermalMass::ThermalMass() :
    previous_time(0),
    mass(1),
    c_p(1000),
    temperature(273.15)
    {this->writeTemperatureMsg = this->outputTemperatureMsg.get_writer();}

void ThermalMass::addUpstreamHeatRate(ReadFunctor <HeatRateMsg> reader){
    this->upstreamHeatRateReaders.push_back(reader);
}

void ThermalMass::addDownstreamHeatRate(ReadFunctor <HeatRateMsg> reader){
    this->downstreamHeatRateReaders.push_back(reader);
}

void ThermalMass::UpdateState(uint64_t CurrentSimNanos){
    HeatRate_t Qtot = 0;
    for (auto reader : this->upstreamHeatRateReaders){
        Qtot += reader().heatRate;
    }
    for (auto reader: this->downstreamHeatRateReaders) {
        Qtot -= reader().heatRate;
    }
    double dt = (CurrentSimNanos - this->previous_time) / 1e9;
    double thermal_mass = this->mass * this->c_p;
    Temperature_t DT = Qtot * dt / thermal_mass;
    this->temperature += DT;
    this->writeTemperatureMsg({this->temperature});
}