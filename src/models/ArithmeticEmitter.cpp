#include <cmath>

#include "thermal/models/ArithmeticEmitter.h"
#include "thermal/thermalConstants.h"

ArithmeticEmitter::ArithmeticEmitter() :
        temperature(273.15),
        epsilon(1.0),
        area(1.0)
    {
    this->writeTemperatureMsg = this->outputTemperatureMsg.get_writer();
    this->writeTemperatureMsg.name = "ArithmeticEmitter.writeTemperatureMsg";
    this->readNearestTemperature.name = "ArithmeticEmitter.readNearestTemperature";
    }

void ArithmeticEmitter::initialize(){ this->writeTemperatureMsg({this->temperature}); }

void ArithmeticEmitter::addUpstreamHeatRate(ReadFunctor <HeatRateMsg> reader){
    this->upstreamHeatRateReaders.push_back(reader);
}

void ArithmeticEmitter::addDownstreamHeatRate(ReadFunctor <HeatRateMsg> reader){
    this->downstreamHeatRateReaders.push_back(reader);
}

void ArithmeticEmitter::UpdateState(uint64_t CurrentSimNanos){
    HeatRate_t Qtot = 0;
    for (auto reader : this->upstreamHeatRateReaders){
        Qtot += reader().heatRate;
    }
    for (auto reader: this->downstreamHeatRateReaders) {
        Qtot -= reader().heatRate;
    }
    this->temperature = Qtot > 0 ?
            std::pow(Qtot / thermal::constants::sigma_SB / this->epsilon / this->area, 0.25) :
            this->readNearestTemperature().temperature;
    this->writeTemperatureMsg({this->temperature});
}