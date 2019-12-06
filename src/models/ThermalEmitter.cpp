#include "thermal/models/ThermalEmitter.h"

#include <cmath>

#include "thermal/thermalConstants.h"

HeatRate_t greyBodyFlux(Emittance_t eps, Area_t area, Temperature_t temp){
    return thermal::constants::sigma_SB * eps * area * std::pow(temp, 4);
}

ThermalEmitter::ThermalEmitter() :
    area(1),
    epsilon(1),
    initialTemperature(0)
    {this->writeHeatRateMsg = this->outputHeatRateMsg.get_writer();}

void ThermalEmitter::initialize(){
    HeatRate_t heatRate = greyBodyFlux(this->epsilon, this->area, this->initialTemperature);
    this->writeHeatRateMsg({heatRate});
}
void ThermalEmitter::UpdateState(uint64_t CurrentSimNanos){
    HeatRate_t heatRate = greyBodyFlux(this->epsilon, this->area, this->readUpstreamTemperature().temperature);
    this->writeHeatRateMsg({heatRate});
}