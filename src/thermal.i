
%module(package="basilisk.thermal") thermal

%include "std_vector.i"
%include "stdint.i"
%include "framework/messaging.i"
%{
#include "framework/system_models/sys_model.h"
#include "models/thermalConductor.h"
#include "models/thermalMass.h"
#include "thermalTypes.h"
%}
%include "framework/system_models/sys_model.h"
%include "models/thermalConductor.h"
%include "models/thermalMass.h"
%include "thermalTypes.h"
%{
%}
INSTANTIATE_MESSAGE_TEMPLATE(TemperatureMsg)
INSTANTIATE_MESSAGE_TEMPLATE(HeatRateMsg)


