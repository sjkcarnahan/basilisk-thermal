#include "thermal/models/NetworkMass.h"

NetworkMass::NetworkMass() :
    mass(1),
    c_p(1000),
    temperature(273.15)
    {this->writeTemperatureMsg = this->outputTemperatureMsg.get_writer();}

void NetworkMass::initialize(){ this->writeTemperatureMsg({this->temperature}); }

void NetworkMass::addUpstreamRate(ReadFunctor <HeatRateMsg> reader){
    this->upstreamHeatRateReaders.push_back(reader);
}

void NetworkMass::addDownstreamRate(ReadFunctor <HeatRateMsg> reader){
    this->downstreamHeatRateReaders.push_back(reader);
}

//void NetworkMass::addUpstreamPath(HeatPath* path){
//    this->upstreamPaths.push_back(path);\
//}
//
//void NetworkMass::addDownstreamPath(HeatPath* path){
//    this->downstreamPaths.push_back(path);
//}

void NetworkMass::UpdateState(uint64_t CurrentSimNanos){
    this->writeTemperatureMsg({this->temperature});
}