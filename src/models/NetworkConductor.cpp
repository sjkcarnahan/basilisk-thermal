#include "thermal/models/NetworkConductor.h"

NetworkConductor::NetworkConductor(){
    this->conductance = 1;
    this->initialHeatRate = 0;
    this->writeConductance = this->conductanceMsg.get_writer();
    this->writeHeatRate = this->heatRateMsg.get_writer();
}

void NetworkConductor::initialize(){
    this->writeHeatRate({this->initialHeatRate});
    this->writeConductance({this->conductance});
}

void NetworkConductor::UpdateState(uint64_t CurrentSimNanos){
    Temperature_t upstreamTemp = this->readUpstreamTemperature().temperature;
    Temperature_t downstreamTemp = this->readDownstreamTemperature().temperature;
    HeatRateMsg heatRate = {this->conductance * (upstreamTemp - downstreamTemp)};
    this->writeHeatRate(heatRate);
}