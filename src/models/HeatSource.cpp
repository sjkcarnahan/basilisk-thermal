#include "thermal/models/HeatSource.h"

HeatSource::HeatSource() : heatRate(1){this->writeHeatRate = this->heatRateMsg.get_writer();}
void HeatSource::UpdateState(uint64_t CurrentSimNanos){this->writeHeatRate({this->heatRate});}
void HeatSource::initialize(){this->UpdateState(0);}