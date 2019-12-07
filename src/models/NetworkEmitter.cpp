#include "thermal/models/NetworkEmitter.h"

#include <cmath>

#include "thermal/thermalConstants.h"

HeatRate_t networkEmitterGreyBodyFlux(Emittance_t eps, Area_t area, Temperature_t temp){
    return thermal::constants::sigma_SB * eps * area * std::pow(temp, 4);
}

NetworkEmitter::NetworkEmitter(){
    this->area = 1;
    this->epsilon = 1;
    this->initialTemperature = 273.15;
    this->writeHeatRate = this->heatRateMsg.get_writer();
    this->writeConductance = this->conductanceMsg.get_writer();
}

void NetworkEmitter::initialize(){
    HeatRate_t heatRate = networkEmitterGreyBodyFlux(this->epsilon, this->area, this->initialTemperature);
    this->writeHeatRate({heatRate});
    Conductance_t initialConductance = heatRate / this->initialTemperature;
    this->conductance = initialConductance;
    this->writeConductance({initialConductance});
}
void NetworkEmitter::UpdateState(uint64_t CurrentSimNanos){
    HeatRate_t heatRate = networkEmitterGreyBodyFlux(this->epsilon, this->area, this->readUpstreamTemperature().temperature);
    this->writeHeatRate({heatRate});
    Conductance_t currentConductance = heatRate / this->readUpstreamTemperature().temperature;
    this->writeConductance({currentConductance});
}