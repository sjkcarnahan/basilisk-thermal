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
    {
    this->writeHeatRateMsg = this->outputHeatRateMsg.get_writer();
    }

void FluxHeating::initialize(){this->writeHeatRateMsg({this->initialHeatRate});}

void FluxHeating::UpdateState(uint64_t CurrentSimNanos){
    Eigen::Vector3d sourceHeading = Eigen::Vector3d(this->readSourceHeading().rHat_XB_B);
    double dot = positiveDotProduct(this->nHat_B, sourceHeading);
    Flux_t flux = this->readFlux().flux;
    HeatRate_t heatRate = dot * flux * this->area * this->alpha;
    this->writeHeatRateMsg({heatRate});
}