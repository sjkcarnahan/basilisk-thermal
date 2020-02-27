#include "thermal/models/ThermalConductor.h"

ThermalConductor::ThermalConductor() :
    conductance(1),
    initialHeatRate(0)
    {this->name = "ThermalConductor";}

void ThermalConductor::setProcess(SysProcess* proc){
    this->process = proc;
    this->readDownstreamTemperature.process = proc;
    this->readUpstreamTemperature.process = proc;
    this->heatRateMsg.process = proc;
    this->writeHeatRate.process = proc;
}

void ThermalConductor::initialize(){
    this->readUpstreamTemperature.name = this->name + "::readUpstreamTemperature";
    this->readDownstreamTemperature.name = this->name + "::readDownstreamTemperature";
    this->writeHeatRate.name = this->name + "::writeHeatRate";
    this->heatRateMsg.name = this->name + "::heatRateMsg";
    this->writeHeatRate = this->heatRateMsg.get_writer();
    this->writeHeatRate({this->initialHeatRate});
}

void ThermalConductor::UpdateState(uint64_t CurrentSimNanos){
    Temperature_t upstreamTemp = this->readUpstreamTemperature().temperature;
    Temperature_t downstreamTemp = this->readDownstreamTemperature().temperature;
    HeatRateMsg heatRate = {this->conductance * (upstreamTemp - downstreamTemp)};
    this->writeHeatRate(heatRate);
}