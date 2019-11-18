%module(package="basilisk.thermal") thermal
%ignore SysModel;
%{
#include "framework/system_models/sys_model.h"
#include "models/thermalConductor.h"
#include "thermalTypes.h"
#include "messages/TemperatureMsg.h"
%}
%include "framework/system_models/sys_model.h"
%include "models/thermalConductor.h"
%include "thermalTypes.h"
%include "messages/TemperatureMsg.h"


