import pytest

from basilisk import thermal

def test_thermalConductorHeatRate():
    """
    This test checks that the heat rate across a conductor is calculated appropriately

    It uses user-set messages to simulate up and downstream temperature messages
    The conductance is set to a non-default value
    The output is calculated independently and compared
    """
    UT = thermal.TemperatureMsgClass()
    UTData = thermal.TemperatureMsg()
    UTData.temperature = 100
    UTw = UT.get_writer()
    UTw(UTData)
    UTr = UT.get_reader()

    DT = thermal.TemperatureMsgClass()
    DTw = DT.get_writer()
    DTData = thermal.TemperatureMsg()
    DTData.temperature = 50
    DTw(DTData)
    DTr = DT.get_reader()

    cond = thermal.ThermalConductor()
    cond.conductance = 2.0
    cond.readUpstreamTemperature = UT.get_reader()
    cond.readDownstreamTemperature = DT.get_reader()
    cr = cond.heatRateMsg.get_reader()
    cond.UpdateState(0)

    expected_rate = (UTr().temperature - DTr().temperature) * cond.conductance
    assert cr().heatRate == pytest.approx(expected_rate, rel=1e-8)


if __name__ == "__main__":
    test_thermalConductorHeatRate()
