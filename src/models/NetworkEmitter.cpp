#include "thermal/models/NetworkEmitter.h"

#include <cmath>

#include "thermal/thermalConstants.h"
#include <iostream>
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
    Temperature_t temperature = this->readUpstreamTemperature().temperature;
    HeatRate_t heatRate = networkEmitterGreyBodyFlux(this->epsilon, this->area, temperature);
    this->writeHeatRate({heatRate});
    this->conductance = (heatRate / temperature + 4 * this->conductance) / 5;
    std::cout << "temp: " << temperature << " | cond: " << this->conductance << std::endl;
    this->writeConductance({this->conductance});
}