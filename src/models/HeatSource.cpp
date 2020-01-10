#include "thermal/models/HeatSource.h"

HeatSource::HeatSource() : heatRate(1){}

void HeatSource::UpdateState(uint64_t CurrentSimNanos){this->writeHeatRate({this->heatRate});}

void HeatSource::setProcess(SysProcess* proc){
    this->process = proc;
    this->writeHeatRate.process = proc;
    this->heatRateMsg.process = proc;
}

void HeatSource::initialize(){
    this->writeHeatRate = this->heatRateMsg.get_writer();
    this->UpdateState(0);}