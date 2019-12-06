#include "thermal/models/ThermalConductor.h"

ThermalConductor::ThermalConductor() :
    conductance(1),
    initialHeatRate(0)
    {this->writeHeatRate = this->heatRateMsg.get_writer();}

void ThermalConductor::initialize(){
    this->writeHeatRate({this->initialHeatRate});
}

void ThermalConductor::UpdateState(uint64_t CurrentSimNanos){
    Temperature_t upstreamTemp = this->readUpstreamTemperature().temperature;
    Temperature_t downstreamTemp = this->readDownstreamTemperature().temperature;
    HeatRateMsg heatRate = {this->conductance * (upstreamTemp - downstreamTemp)};
    this->writeHeatRate(heatRate);
}