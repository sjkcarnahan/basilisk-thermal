import pytest

from basilisk import thermal

def test_thermalEmitter():
    """
    This test checks that the heat emitted from a surface is calculated correctly

    It uses user-set messages to simulate connected temperature. It sets non-default parameters
    """

    UT = thermal.TemperatureMsgClass()
    UTData = thermal.TemperatureMsg()
    UTData.temperature = 100
    UTw = UT.get_writer()
    UTw(UTData)
    UTr = UT.get_reader()

    e = thermal.ThermalEmitter()
    e.readUpstreamTemperature = UT.get_reader()
    e.area = 2
    e.epsilon = 0.8
    e.UpdateState(0)
    er = e.outputHeatRateMsg.get_reader()

    expectedResult = thermal.sigma_SB * e.epsilon * e.area * UTr().temperature**4
    assert er().heatRate == pytest.approx(expectedResult)


if __name__ == "__main__":
    test_thermalEmitter()
