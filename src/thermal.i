%module(package="basilisk.thermal") thermal
%{
#include "framework/system_models/sys_model.h"
#include "models/thermalConductor.h"
#include "thermalTypes.h"
#include "messages/TemperatureMsg.h"
%}
%include "models/thermalConductor.h"
%include "thermalTypes.h"
%include "messages/TemperatureMsg.h"


