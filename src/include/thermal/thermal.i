
%module(package="basilisk") thermal

%include "std_vector.i"
%include "stdint.i"
%include "framework/messaging.i"
%include "external/eigen.i"
%eigen_typemaps(Eigen::Vector3d)
%{
#include "framework/system_models/sys_model.h"
#include "thermal/models/ArithmeticSurface.h"
#include "thermal/models/BetaAngle.h"
#include "thermal/models/FluxHeating.h"
#include "thermal/models/HeatSource.h"
#include "thermal/models/HeatPath.h"
#include "thermal/models/NetworkConductor.h"
#include "thermal/models/NetworkEmitter.h"
#include "thermal/models/NetworkMass2.h"
#include "thermal/models/NetworkRadiationConductor.h"
#include "thermal/models/NetworkSolver.h"
#include "thermal/models/SolarAngle.h"
#include "thermal/models/ThermalConductor.h"
#include "thermal/models/ThermalEmitter.h"
#include "thermal/models/ThermalMass.h"
#include "thermal/thermalTypes.h"
#include "thermal/thermalConstants.h"
%}
%include "framework/system_models/sys_model.h"
%include "thermal/models/ArithmeticSurface.h"
%include "thermal/models/BetaAngle.h"
%include "thermal/models/FluxHeating.h"
%include "thermal/models/HeatSource.h"
%include "thermal/models/HeatPath.h"
%include "thermal/models/NetworkConductor.h"
%include "thermal/models/NetworkEmitter.h"
%include "thermal/models/NetworkMass2.h"
%include "thermal/models/NetworkRadiationConductor.h"
%include "thermal/models/NetworkSolver.h"
%include "thermal/models/SolarAngle.h"
%include "thermal/models/ThermalConductor.h"
%include "thermal/models/ThermalEmitter.h"
%include "thermal/models/ThermalMass.h"
%include "thermal/thermalTypes.h"
%include "thermal/thermalConstants.h"

INSTANTIATE_MESSAGE_TEMPLATE(thermal, BetaAngleMsg)
INSTANTIATE_MESSAGE_TEMPLATE(thermal, ConductanceMsg)
INSTANTIATE_MESSAGE_TEMPLATE(thermal, HeatRateMsg)
INSTANTIATE_MESSAGE_TEMPLATE(thermal, SolarAngleMsg)
INSTANTIATE_MESSAGE_TEMPLATE(thermal, TemperatureMsg)


