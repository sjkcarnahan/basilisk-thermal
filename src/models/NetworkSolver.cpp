#include "thermal/models/NetworkSolver.h"

NetworkSolver::NetworkSolver() : numberOfMasses(0){
}
void NetworkSolver::initialize(){
    auto num_mass = this->masses.size();
    this->Amat.resize(num_mass, num_mass);
    this->Amat.fill(0.0);
}

void NetworkSolver::populateMatrix(){
    uint64_t up = -1;
    uint64_t down = -1;
    this->Amat.fill(0.0);
    for (auto path : this->paths){
        if (path->upstream) {
            up = path->upstream->networkPosition;
        }
        if (path->downstream) {
            down = path->downstream->networkPosition;
        }
        Conductance_t c = path->conductance;
        if (path->upstream) {
            this->Amat(up, up) -= c;
        }
        if (path->downstream){
            this->Amat(down, down) -= c;
        }
        if (path->upstream && path->downstream){
            this->Amat(up, down) += c;
            this->Amat(down, up) += c;
        }
    }
}

Eigen::VectorXd NetworkSolver::getIndependentQs(){
    Eigen::VectorXd independentQ;
    independentQ.resize(this->masses.size());
    uint64_t mi = 0;
    for (auto m : this->masses){
        independentQ(mi++) = m->independentHeatRate();
    }
    return independentQ;
}

void NetworkSolver::UpdateState(uint64_t CurrentSimNanos){
    Eigen::VectorXd solvedTemperatures;
    for (int i = 0; i != 10; i++) {
        this->populateMatrix();
        Eigen::VectorXd independentQ = this->getIndependentQs();
        solvedTemperatures = -this->Amat.inverse() * independentQ;
        for (auto path : this->paths) {
            if (path->isEmitter) {
                path->setConductance(solvedTemperatures(path->upstream->networkPosition));
            }
        }
    }
    uint64_t mi = 0;
    for (auto m : this->masses){
        m->temperature = solvedTemperatures(mi++);
    }
}

void NetworkSolver::addMass(NetworkMass2* mass){
    this->masses.push_back(mass);
    mass->networkPosition = this->numberOfMasses++;
}