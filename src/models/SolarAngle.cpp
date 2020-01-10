#include "thermal/models/SolarAngle.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <Eigen/Dense>

#include "framework/utilities/avsEigenMRP.h"

SolarAngle::SolarAngle() :
    initialTheta(0)
    {}

void SolarAngle::setProcess(SysProcess* proc){
    this->process = proc;
    this->readSunState.process = proc;
    this->readScStates.process = proc;
    this->readPlanetState.process = proc;
    this->writeOutputMsg.process=  proc;
    this->outputMsg.process = proc;
}

void SolarAngle::initialize(){
    this->writeOutputMsg = this->outputMsg.get_writer();
    this->writeOutputMsg({this->initialTheta});}

void SolarAngle::UpdateState(uint64_t CurrentSimNanos) {
    Eigen::Vector3d r_BN_N(this->readScStates().r_BN_N);
    Eigen::Vector3d v_BN_N(this->readScStates().v_BN_N);
    Eigen::Vector3d r_SN_N(this->readSunState().PositionVector);
    Eigen::Vector3d r_PN_N(this->readPlanetState().PositionVector);

    Eigen::Vector3d nHat_N = (r_BN_N.cross(v_BN_N)).normalized();  // orbit normal
    Eigen::Vector3d rHat_SP_N = (r_SN_N - r_PN_N).normalized();
    Eigen::Vector3d rHat_SP_N_in_plane = rHat_SP_N - rHat_SP_N.dot(nHat_N) * nHat_N;
    Eigen::Vector3d rHat_BP_N = (r_BN_N - r_PN_N).normalized();
    AngleRadian_t theta = std::acos(rHat_BP_N.dot(rHat_SP_N_in_plane));
    this->writeOutputMsg({theta});
}