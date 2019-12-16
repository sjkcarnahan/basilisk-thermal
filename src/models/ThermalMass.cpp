#include "thermal/models/ThermalMass.h"
#include <iostream>
ThermalMass::ThermalMass() :
    previous_time(0),
    mass(1),
    c_p(1000),
    temperature(273.15)
    {this->writeTemperatureMsg = this->outputTemperatureMsg.get_writer();}

void ThermalMass::initialize(){ this->writeTemperatureMsg({this->temperature}); }

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
    this->previous_time = CurrentSimNanos;
    double thermal_mass = this->mass * this->c_p;
    Temperature_t DT = Qtot * dt / thermal_mass;
    this->temperature += DT;
    this->writeTemperatureMsg({this->temperature});
}