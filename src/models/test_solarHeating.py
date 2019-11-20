import pytest
import numpy as np
import thermal
import navigation
import environment
import dynamics


def postiveDotProduct(v1, v2):
    """
    :param v1: a 3 vector
    :param v2: a 3 vector
    :return: dot product (if positive), 0 otherwise
    """
    dot_prod = np.dot(v1, v2)
    if dot_prod > 0:
        return dot_prod
    else:
        return 0


def test_solarHeating():
    sunHeadingMsg = navigation.BodyHeadingSimMsgClass()
    sunHeadingData = navigation.BodyHeadingSimMsg()
    sunHeadingData.rHat_XB_B = [1, 0, 0]
    sunHeadingWriter = sunHeadingMsg.get_writer()
    sunHeadingWriter(sunHeadingData)

    solarFluxMsg = environment.SolarFluxSimMsgClass()
    solarFluxMsgData = environment.SolarFluxSimMsg()
    solarFluxMsgData.flux = 1300.
    solarFluxMsgWriter = solarFluxMsg.get_writer()
    solarFluxMsgWriter(solarFluxMsgData)

    scMsg = dynamics.ScPlusStatesSimMsgClass()
    scMsgData = dynamics.ScPlusStatesSimMsg()
    scMsgData.sigma_BN = [1, 0, 0]
    scMsgWriter = scMsg.get_writer()
    scMsgWriter(scMsgData)

    s = thermal.SolarHeating()
    s.readScStates = scMsg.get_reader()
    s.readSolarFlux = solarFluxMsg.get_reader()
    s.readSunHeading = sunHeadingMsg.get_reader()
    s.nHat_B = np.array([1.5, 253.6, 345.0]) / np.linalg.norm([1.5, 253.6, 345.0])
    s.UpdateState(0)

    sr = s.outputHeatRateMsg.get_reader()
    dot = postiveDotProduct(scMsgData.sigma_BN, s.nHat_B)
    dotFlux = dot * solarFluxMsgData.flux
    expectedHeatRate = dotFlux * s.area * s.alpha

    assert sr().heatRate == pytest.approx(expectedHeatRate)


if __name__ == "__main__":
    test_solarHeating()
