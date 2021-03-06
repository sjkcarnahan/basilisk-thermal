import pytest
import numpy as np

from basilisk import thermal

def test_NetworkSolver():
    """
    that the network mass works correctly
    """
    ns = thermal.NetworkSolver()
    m1 = thermal.NetworkMass2()
    m2 = thermal.NetworkMass2()
    m3 = thermal.NetworkMass2()
    c1 = thermal.NetworkConductor()
    c1.conductance = .0024 * 24
    c2 = thermal.NetworkConductor()
    c2.conductance = .0004 * 24
    c1.upstream = m1
    c1.downstream = m2
    c2.upstream = m2
    c2.downstream = m3

    inputMsg = thermal.HeatRateMsgClass()
    inputMsgData = thermal.HeatRateMsg()
    inputMsgData.heatRate = 10
    inputMsgWriter = inputMsg.get_writer()
    inputMsgWriter(inputMsgData)
    m1.addIndependentHeatRate(inputMsg.get_reader())

    em = thermal.NetworkEmitter()
    em.upstream = m3
    em.area = 3 * np.sqrt(3) / 2 * (.0254 ** 2) * 24
    em.readUpstreamTemperature = m3.temperatureMsg.get_reader()

    ns.addPath(em)
    ns.addPath(c1)
    ns.addPath(c2)
    ns.addMass(m1)
    ns.addMass(m2)
    ns.addMass(m3)

    m1.initialize()
    m2.initialize()
    m3.initialize()
    c1.initialize()
    c2.initialize()
    em.initialize()
    ns.initialize()
    m1.UpdateState(0)
    m2.UpdateState(0)
    m3.UpdateState(0)
    m3.UpdateState(0)
    em.UpdateState(0)
    ns.UpdateState(0)
    print(m1.temperature, m2.temperature, m3.temperature)

    assert m2.temperature == pytest.approx(197.6446866167)

if __name__ == "__main__":
    test_NetworkSolver()
