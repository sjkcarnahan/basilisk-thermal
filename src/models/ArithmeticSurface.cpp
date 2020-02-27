#include <cmath>

#include "thermal/models/ArithmeticSurface.h"
#include "thermal/thermalConstants.h"

ArithmeticSurface::ArithmeticSurface() :
        temperature(273.15),
        epsilon(1.0),
        area(1.0)
    {this->name = "ArithmeticSurface";}

void ArithmeticSurface::setProcess(SysProcess* proc){
    this->process = proc;
    this->outputTemperatureMsg.process = proc;
    this->writeTemperatureMsg.process = proc;
}
void ArithmeticSurface::initialize(){ 
    this->writeTemperatureMsg.name = this->name + "::writeTemperatureMsg";
    this->writeTemperatureMsg = this->outputTemperatureMsg.get_writer();
    this->writeTemperatureMsg({this->temperature});
}

void ArithmeticSurface::addIrradianceHeatRate(ReadFunctor <HeatRateMsg> reader){
    this->irradianceHeatRateReaders.push_back(reader);
}

void ArithmeticSurface::UpdateState(uint64_t CurrentSimNanos){
    HeatRate_t Qin = 0;
    for (auto reader : this->irradianceHeatRateReaders){
        Qin += reader().heatRate;
    }
    this->temperature = std::pow(Qin / thermal::constants::sigma_SB / this->epsilon / this->area, 0.25);
    this->writeTemperatureMsg({this->temperature});
}