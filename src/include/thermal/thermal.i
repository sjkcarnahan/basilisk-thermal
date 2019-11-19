
%module(package="basilisk.thermal") thermal

%include "std_vector.i"
%include "stdint.i"
%include "framework/messaging.i"
%{
#include "framework/system_models/sys_model.h"
#include "thermal/models/thermalConductor.h"
#include "thermal/models/thermalMass.h"
#include "thermal/models/thermalEmitter.h"
#include "thermal/thermalTypes.h"
#include "thermal/thermalConstants.h"
%}
%include "framework/system_models/sys_model.h"
%include "thermal/models/thermalConductor.h"
%include "thermal/models/thermalMass.h"
%include "thermal/models/thermalEmitter.h"
%include "thermal/thermalTypes.h"
%include "thermal/thermalConstants.h"
%{
%}
INSTANTIATE_MESSAGE_TEMPLATE(thermal, TemperatureMsg)
INSTANTIATE_MESSAGE_TEMPLATE(thermal, HeatRateMsg)


