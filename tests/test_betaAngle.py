import pytest
import numpy as np

from basilisk import thermal
from basilisk import dynamics
from basilisk import framework
from basilisk import environment


def test_betaAngle():
    """
    set up a known beta angle and check if it is calculated correctly
    """
    earth = dynamics.GravBodyData()
    earth.mu = 0.3986004415E+15

    oe = framework.classicElements()
    oe.a = 1000000
    oe.e = 0
    expected_beta = np.radians(45)
    oe.i = expected_beta
    oe.Omega = 0
    oe.omega = 0
    oe.f = np.radians(120)
    orbit = dynamics.KeplerianOrbit(oe, earth)
    r_BN_N = orbit.r_BP_P()
    v_BN_N = orbit.v_BP_P()

    scMsg = dynamics.ScPlusStatesSimMsgClass()
    scMsgData = dynamics.ScPlusStatesSimMsg()
    scMsgData.r_BN_N = r_BN_N
    scMsgData.v_BN_N = v_BN_N
    scMsgWriter = scMsg.get_writer()
    scMsgWriter(scMsgData)

    sunMsg = environment.SpicePlanetStateSimMsgClass()
    sunMsgData = environment.SpicePlanetStateSimMsg()
    sunMsgData.PositionVector = [0, 1.496e11, 0]
    sunMsgWriter = sunMsg.get_writer()
    sunMsgWriter(sunMsgData)

    earthMsg = environment.SpicePlanetStateSimMsgClass()
    earthMsgData = environment.SpicePlanetStateSimMsg()
    earthMsgData.PositionVector = [0, 0, 0]
    earthMsgWriter = earthMsg.get_writer()
    earthMsgWriter(earthMsgData)

    BA = thermal.BetaAngle()
    BA.readPlanetState = earthMsg.get_reader()
    BA.readScStates = scMsg.get_reader()
    BA.readSunState = sunMsg.get_reader()
    BA.UpdateState(0)

    BAReader = BA.outputMsg.get_reader()
    assert BAReader().betaAngle == pytest.approx(expected_beta)


if __name__ == "__main__":
    test_betaAngle()
