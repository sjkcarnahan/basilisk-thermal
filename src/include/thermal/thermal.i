
%module(package="basilisk.thermal") thermal

%include "std_vector.i"
%include "stdint.i"
%include "framework/messaging.i"
%include "external/eigen.i"
%eigen_typemaps(Eigen::Vector3d)
%{
#include "framework/system_models/sys_model.h"
#include "thermal/models/thermalConductor.h"
#include "thermal/models/thermalMass.h"
#include "thermal/models/thermalEmitter.h"
#include "thermal/models/fluxHeating.h"
#include "thermal/models/betaAngle.h"
#include "thermal/thermalTypes.h"
#include "thermal/thermalConstants.h"
%}
%include "framework/system_models/sys_model.h"
%include "thermal/models/thermalConductor.h"
%include "thermal/models/thermalMass.h"
%include "thermal/models/thermalEmitter.h"
%include "thermal/models/fluxHeating.h"
%include "thermal/models/betaAngle.h"
%include "thermal/thermalTypes.h"
%include "thermal/thermalConstants.h"

INSTANTIATE_MESSAGE_TEMPLATE(thermal, BetaAngleMsg)
INSTANTIATE_MESSAGE_TEMPLATE(thermal, HeatRateMsg)
INSTANTIATE_MESSAGE_TEMPLATE(thermal, TemperatureMsg)


