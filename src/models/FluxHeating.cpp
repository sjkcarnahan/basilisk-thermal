#include "thermal/models/FluxHeating.h"

#include "thermal/thermalConstants.h"

double positiveDotProduct(Eigen::Vector3d v1, Eigen::Vector3d v2){
    double dot = v1.dot(v2);
    return dot > 0 ? dot : 0;
}

FluxHeating::FluxHeating() :
    area(1),
    alpha(1),
    nHat_B({1, 0, 0}),
    initialHeatRate(0)
    {this->name = "FluxHeating";}

void FluxHeating::setProcess(SysProcess* proc){
    this->process = proc;
    this->readFlux.process = proc;
    this->readSourceHeading.process = proc;
    this->outputHeatRateMsg.process = proc;
    this->writeHeatRateMsg.process = proc;
}

void FluxHeating::initialize(){
    this->readFlux.name = this->name + "::readFlux";
    this->readSourceHeading.name = this->name + "::readSourceHeading";
    this->outputHeatRateMsg.name = this->name + "::outputHeatRateMsg";
    this->writeHeatRateMsg.name = this->name + "::writeHeatRateMsg";
    this->writeHeatRateMsg = this->outputHeatRateMsg.get_writer();
    this->writeHeatRateMsg({this->initialHeatRate});
}

void FluxHeating::UpdateState(uint64_t CurrentSimNanos){
    Eigen::Vector3d sourceHeading = Eigen::Vector3d(this->readSourceHeading().rHat_XB_B);
    double dot = positiveDotProduct(this->nHat_B, sourceHeading);
    Flux_t flux = this->readFlux().flux;
    HeatRate_t heatRate = dot * flux * this->area * this->alpha;
    this->writeHeatRateMsg({heatRate});
}