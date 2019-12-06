import pytest
import numpy as np

from basilisk import thermal


def test_ArithmeticSurface():
    """
    This test checks that the arithmetic surface is properly balancing emission via its temperature
    """
    flux_heat_rate = thermal.HeatRateMsgClass()
    flux_heat_rate_data = thermal.HeatRateMsg()
    input_heat_rate = 10.
    flux_heat_rate_data.heatRate = input_heat_rate
    flux_heat_rate_writer = flux_heat_rate.get_writer()
    flux_heat_rate_writer(flux_heat_rate_data)

    tas = thermal.ArithmeticSurface()
    tas.addIrradianceHeatRate(flux_heat_rate.get_reader())
    tas.area = 3
    tas.epsilon = 0.3
    tas.UpdateState(0)
    tas_temperature_reader = tas.outputTemperatureMsg.get_reader()

    expected_temperature = (input_heat_rate / thermal.sigma_SB / tas.area / tas.epsilon)**0.25
    assert tas_temperature_reader().temperature == pytest.approx(expected_temperature)


if __name__ == "__main__":
    test_ArithmeticSurface()
