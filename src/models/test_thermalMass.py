import thermal
import pytest

def test_thermalMassTemperature():
    """
    This test checks that the temperature in a mass is updated correctly

    It uses user-set messages to simulate connected heat rates. It sets non-default parameters
    """
    m = thermal.ThermalMass()
    m.mass = 2.0
    m.c_p = 800.
    mr = m.outputTemperatureMsg.get_reader()
    m.UpdateState(0)
    initTemp = mr().temperature

    r1 = thermal.HeatRateMsgClass()
    r1w = r1.get_writer()
    r1Data = thermal.HeatRateMsg()
    r1Data.heatRate = 5
    r1w(r1Data)
    m.addUpstreamHeatRate(r1.get_reader())

    r2 = thermal.HeatRateMsgClass()
    r2w = r2.get_writer()
    r2Data = thermal.HeatRateMsg()
    r2Data.heatRate = -7
    r2w(r2Data)
    m.addDownstreamHeatRate(r2.get_reader())

    r3 = thermal.HeatRateMsgClass()
    r3w = r3.get_writer()
    r3Data = thermal.HeatRateMsg()
    r3Data.heatRate = -2
    r3w(r3Data)
    m.addUpstreamHeatRate(r3.get_reader())

    dt_sec = 10
    m.UpdateState(int(dt_sec * 1e9))

    netQ = r1Data.heatRate - r2Data.heatRate + r3Data.heatRate
    thermalMass = m.mass * m.c_p
    expectedDT = netQ * dt_sec / thermalMass
    outputDT = mr().temperature - initTemp
    assert outputDT == pytest.approx(expectedDT, rel=1e8)


if __name__ == "__main__":
    test_thermalMassTemperature()
