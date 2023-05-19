package Model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SmartBulbTest {

    @Test
    void getMode() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        assertEquals(SmartBulb.modo.COLD, sb.getMode(), "Invalid mode!");
    }

    @Test
    void setMode() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        sb.setMode(SmartBulb.modo.WARM);
        assertEquals(SmartBulb.modo.WARM, sb.getMode(), "Invalid mode!");
    }

    @Test
    void getDimensions() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        assertEquals(10, sb.getDimensions(),"Invalid dimensions!");
    }

    @Test
    void setDimensions() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        sb.setDimensions(11);
        assertEquals(11,sb.getDimensions(), "Invalid dimensions!");
    }

    @Test
    void getConsumo() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        assertEquals(0.0f,sb.getConsumo(), "Invalid consume!");
    }

    @Test
    void setConsumo() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        sb.setConsumo(11.0f);
        assertEquals(0.0f,sb.getConsumo(), "Invalid consume!");
    }

    @Test
    void turnOn() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        sb.turnOn();
        assertEquals(SmartDevice.state.ON,sb.getEstado(),"Not turned on!");
    }

    @Test
    void turnOff() {
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        sb.turnOff();
        assertEquals(SmartDevice.state.OFF,sb.getEstado(),"Not turned off!");
    }
}