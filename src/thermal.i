%module(package="basilisk.thermal") thermal
%{
#include "models/thermalConductor.h"
#include "thermalTypes.h"
#include "messages/TemperatureMsg.h"
%}
%include "models/thermalConductor.h"
%include "thermalTypes.h"
%include "messages/TemperatureMsg.h"


