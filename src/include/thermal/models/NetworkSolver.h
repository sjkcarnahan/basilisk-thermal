#pragma once

#include <vector>

#include <Eigen/Dense>

#include "framework/messaging/message.h"
#include "framework/messaging/readFunctor.h"
#include "framework/messaging/writeFunctor.h"
#include "framework/system_models/sys_model.h"

#include "thermal/models/HeatPath.h"
#include "thermal/models/NetworkMass2.h"
#include "thermal/messages/HeatRateMsg.h"
#include "thermal/thermalTypes.h"

/* A constant heat source */
class NetworkSolver: public SysModel {
public:
    NetworkSolver();
    void initialize() override;
    void UpdateState(uint64_t CurrentSimNanos) override;

public:
    void addMass(NetworkMass2* mass);
    void addPath(HeatPath* path){this->paths.push_back(path);}

private:
    std::vector<NetworkMass2*> masses;
    std::vector<HeatPath*> paths;
    Eigen::MatrixXd Amat;
    uint64_t numberOfMasses;
};
