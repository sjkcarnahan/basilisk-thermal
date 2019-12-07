#include "thermal/models/NetworkMass2.h"

NetworkMass2::NetworkMass2(){
    this->initialTemperature = 273.15;
    this->temperature = 273.15;
    this->c_p = 1000;
    this->mass = 1.;
    this->writeTemperature = this->temperatureMsg.get_writer();
}

void NetworkMass2::initialize(){
    this->temperature = this->initialTemperature;
    this->writeTemperature({this->temperature});
}

void NetworkMass2::UpdateState(uint64_t CurrentSimNanos){
    this->writeTemperature({this->temperature});
}

void NetworkMass2::addIndependentHeatRate(ReadFunctor<HeatRateMsg> rateReader){
    this->independentRateReaders.push_back(rateReader);
}

HeatRate_t NetworkMass2::independentHeatRate(){
    HeatRate_t q = 0;
    for (auto src : this->independentRateReaders){
        q += src().heatRate;
    }
    return q;
}

