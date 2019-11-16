%module(package="basilisk.thermal") thermal
%{
#include "thermalConductor.h"
#include "thermalTypes.h"
#include "messages/TemperatureMsg.h"
%}
%include "thermalConductor.h"
%include "thermalTypes.h"
%include "messages/TemperatureMsg.h"


