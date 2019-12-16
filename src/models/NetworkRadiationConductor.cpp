#include "thermal/models/NetworkRadiationConductor.h"

#include <cmath>

#include "thermal/thermalConstants.h"

NetworkRadiationConductor::NetworkRadiationConductor(){
    this->conductance = 1;
    this->initialHeatRate = 0;
    this->viewFactor = 1;
    this->area = 1;
    this->epsilon_1 = 1;
    this->epsilon_2 = 1;
    this->isEmitter = true;
    this->writeConductance = this->conductanceMsg.get_writer();
    this->writeHeatRate = this->heatRateMsg.get_writer();
}

void NetworkRadiationConductor::initialize(){
    this->writeHeatRate({this->initialHeatRate});
    this->writeConductance({this->conductance});
}

void NetworkRadiationConductor::setConductance(Temperature_t upstreamTemperature, Temperature_t downstreamTemperature){
    Temperature_t upT = upstreamTemperature;
    Temperature_t downT = downstreamTemperature;
    this->conductance = thermal::constants::sigma_SB * this->area * this->viewFactor *
            (pow(upT, 3) + upT * pow(downT, 2) + pow(upT, 2) * downT + pow(downT, 3)) /
            (1 / this->epsilon_1 + 1 / this->epsilon_2 - 1);
}

void NetworkRadiationConductor::UpdateState(uint64_t CurrentSimNanos){
    Temperature_t upstreamTemp = this->readUpstreamTemperature().temperature;
    Temperature_t downstreamTemp = this->readDownstreamTemperature().temperature;
    this->setConductance(upstreamTemp, downstreamTemp);
    HeatRateMsg heatRate = {this->conductance * (upstreamTemp - downstreamTemp)};
    this->writeHeatRate(heatRate);
    this->writeConductance({this->conductance});
}