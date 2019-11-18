%module(package="basilisk.thermal") thermal
%{
#include "models/thermalConductor.h"
#include "thermalTypes.h"
#include "messages/TemperatureMsg.h"
#include "system_models/sys_model.h"
%}
%include "system_models/sys_model.h"
%include "models/thermalConductor.h"
%include "thermalTypes.h"
%include "messages/TemperatureMsg.h"


