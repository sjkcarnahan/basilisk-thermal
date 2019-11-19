import thermal

def test_thermalConductor():
    cond = thermal.ThermalConductor()
    UT = thermal.TemperatureMsgClass()
    UTData = thermal.TemperatureMsg()
    UTData.temperature = 100
    UTw = UT.add_author()
    UTw(UTData)
    UTr = UT.add_subscriber()
    DT = thermal.TemperatureMsgClass()
    DTw = DT.add_author()
    assert 1==1

if __name__ == "__main__":
    test_thermalConductor()

