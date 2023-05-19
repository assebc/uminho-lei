package Model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SmartDeviceTest {

    @Test
    void toState() {
        SmartDevice sd = new SmartBulb(1,"COLD", 10, 0.05);
        assertTrue(sd.toState("ON").equals(SmartDevice.state.ON));
        assertTrue(sd.toState("OFF").equals(SmartDevice.state.OFF));
        assertTrue(sd.toState("Obatata").equals(SmartDevice.state.OFF));
    }

    @Test
    void getCustoInstalacao() {
        SmartDevice sd = new SmartBulb(1,"COLD", 10, 0.05);
        assertEquals(2.5, sd.getCustoInstalacao(), "Invalid installation' cost!");
    }

    @Test
    void turnOn() {
        SmartDevice sd = new SmartBulb(1,"COLD", 10, 0.05);
        assertTrue(sd.getEstado().equals(SmartDevice.state.OFF));
        sd.turnOn();
        assertTrue(sd.getEstado().equals(SmartDevice.state.ON));
    }

    @Test
    void turnOff() {
        SmartDevice sd = new SmartBulb(1,"COLD", 10, 0.05);
        assertTrue(sd.getEstado().equals(SmartDevice.state.OFF));
        sd.turnOn();
        assertTrue(sd.getEstado().equals(SmartDevice.state.ON));
        sd.turnOff();
        assertTrue(sd.getEstado().equals(SmartDevice.state.OFF));
    }
}