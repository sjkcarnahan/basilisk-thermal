#include "thermal/models/BetaAngle.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <Eigen/Dense>

BetaAngle::BetaAngle() :
    initialBeta(0)
    {this->name = "BetaAngle";}

void BetaAngle::setProcess(SysProcess* proc){
    this->process = proc;
    this->readPlanetState.process = proc;
    this->readScStates.process = proc;
    this->readSunState.process = proc;
    this->writeOutputMsg.process = proc;
    this->outputMsg.process = proc;
}
void BetaAngle::initialize(){
    this->readPlanetState.name = this->name + "::readPlanetState";
    this->readScStates.name = this->name + "::readScStates";
    this->readSunState.name = this->name + "::readSunState";
    this->writeOutputMsg.name = this->name + "::writeOutputMsg";
    this->outputMsg.name = this->name + "::outputMsg";
    this->writeOutputMsg = this->outputMsg.get_writer();
    this->writeOutputMsg({this->initialBeta});}

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