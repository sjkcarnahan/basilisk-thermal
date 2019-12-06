#include <cmath>

#include "thermal/models/ArithmeticSurface.h"
#include "thermal/thermalConstants.h"

ArithmeticSurface::ArithmeticSurface() :
        temperature(273.15),
        epsilon(1.0),
        area(1.0)
    {
    this->writeTemperatureMsg = this->outputTemperatureMsg.get_writer();
    this->writeTemperatureMsg.name = "ArithmeticSurface.writeTemperatureMsg";
    }

void ArithmeticSurface::initialize(){ this->writeTemperatureMsg({this->temperature}); }

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