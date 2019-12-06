#include "thermal/models/BetaAngle.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <Eigen/Dense>

BetaAngle::BetaAngle() :
    initialBeta(0)
    {this->writeOutputMsg = this->outputMsg.get_writer();}

void BetaAngle::initialize(){this->writeOutputMsg({this->initialBeta});}

void BetaAngle::UpdateState(uint64_t CurrentSimNanos) {
    Eigen::Vector3d scPos(this->readScStates().r_BN_N);
    Eigen::Vector3d scVel(this->readScStates().v_BN_N);
    Eigen::Vector3d sunPos(this->readSunState().PositionVector);
    Eigen::Vector3d planetPos(this->readPlanetState().PositionVector);

    Eigen::Vector3d nHat = (scPos.cross(scVel)).normalized();  // orbit normal
    Eigen::Vector3d sHat = (planetPos - sunPos).normalized();
    AngleRadian_t beta = M_PI / 2 - std::acos(nHat.dot(sHat));
    this->writeOutputMsg({beta});
}