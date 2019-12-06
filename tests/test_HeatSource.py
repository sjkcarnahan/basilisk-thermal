import pytest

from basilisk import thermal

def test_HeatSource():
    """
    This test checks that the input heat rate to HeatSource is properly written out as its message
    """
    expected_rate = 17.
    hs = thermal.HeatSource()
    hs.heatRate = expected_rate
    hs.initialize()
    hsr = hs.heatRateMsg.get_reader()
    assert hsr().heatRate == pytest.approx(expected_rate)


if __name__ == "__main__":
    test_HeatSource()
