#include "thermal/models/RadiationConductor.h"
#include "thermal/thermalConstants.h"

RadiationConductor::RadiationConductor() :
    conductance(1),
    initialHeatRate(0),
    epsilonUp(1),
    epsilonDown(1),
    viewFactor(1),
    area(1)
    {this->name = "RadiationConductor";}

void RadiationConductor::setProcess(SysProcess* proc){
    this->process = proc;
    this->readDownstreamTemperature.process = proc;
    this->readUpstreamTemperature.process = proc;
    this->heatRateMsg.process = proc;
    this->writeHeatRate.process = proc;
    this->conductanceMsg.process = proc;
    this->writeConductance.process = proc;
}

void RadiationConductor::initialize(){
    this->writeHeatRate.name = this->name + "::writeHeatRate";
    this->writeConductance.name = this->name + "::writeConductance";
    this->heatRateMsg.name = this->name + "::heatRateMsg";
    this->conductanceMsg.name = this->name + "::conductanceMsg";
    this->readDownstreamTemperature.name = this->name + "::readDownstreamTemperature";
    this->readUpstreamTemperature.name = this->name + "::readUpstreamTemperature";
    this->writeHeatRate = this->heatRateMsg.get_writer();
    this->writeHeatRate({this->initialHeatRate});
    this->writeConductance = this->conductanceMsg.get_writer();
    this->writeConductance({this->conductance});
}

void RadiationConductor::UpdateState(uint64_t CurrentSimNanos){
    Temperature_t upstreamTemp = this->readUpstreamTemperature().temperature;
    Temperature_t downstreamTemp = this->readDownstreamTemperature().temperature;
    this->conductance = thermal::constants::sigma_SB * this->area * this->viewFactor *
        (pow(upstreamTemp, 3) + upstreamTemp * pow(downstreamTemp, 2) + pow(upstreamTemp, 2) * downstreamTemp + pow(downstreamTemp, 3)) /
        (1 / this->epsilonUp + 1 / this->epsilonDown - 1);
    HeatRateMsg heatRate = {this->conductance * (upstreamTemp - downstreamTemp)};
    this->writeHeatRate(heatRate);
    this->writeConductance({this->conductance});
}