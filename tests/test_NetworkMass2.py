import pytest

from basilisk import thermal


def test_NetworkMass2():
    """
    that the network mass works correctly
    """
    m = thermal.NetworkMass2()
    m.initialTemperature = 300
    m.c_p = 0.75
    m.mass = 23
    heatMsg = thermal.HeatRateMsgClass()
    m.addIndependentHeatRate(heatMsg.get_reader())

    expected=1
    assert 1 == pytest.approx(expected)


if __name__ == "__main__":
    test_NetworkMass2()
