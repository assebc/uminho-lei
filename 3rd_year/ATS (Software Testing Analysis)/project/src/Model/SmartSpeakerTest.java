package Model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SmartSpeakerTest {

    @Test
    void getMarca() {
        Marca m = new Marca("ATS");
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", m, 0.05);
        assertEquals(m,ss.getMarca(),"Invalid brand!");
    }

    @Test
    void setMarca() {
        Marca mt = new Marca("POO");
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", mt, 0.05);
        Marca m = new Marca("ATS");
        ss.setMarca(m);
        assertEquals(m,ss.getMarca(),"Invalid brand!");
    }

    @Test
    void getVolume() {
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", new Marca("ATS"), 0.05);
        assertEquals(5,ss.getVolume(),"Invalid volume!");
    }

    @Test
    void setVolume() {
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", new Marca("ATS"), 0.05);
        ss.setVolume(10);
        assertEquals(10,ss.getVolume(),"Invalid volume!");
    }

    @Test
    void getEstacao() {
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", new Marca("ATS"), 0.05);
        assertEquals("RFM",ss.getEstacao(),"Invalid station!");
    }

    @Test
    void setEstacao() {
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", new Marca("ATS"), 0.05);
        ss.setEstacao("RUM");
        assertEquals("RUM",ss.getEstacao(),"Invalid station!");
    }

    @Test
    void getConsumo() {
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", new Marca("ATS"), 0.05);
        assertEquals(0,ss.getConsumo(),"Invalid consume!");
    }

    @Test
    void volumeUp() {
        SmartSpeaker ss = new SmartSpeaker(1,5, "RFM", new Marca("ATS"), 0.05);
        ss.volumeUp();
        assertEquals(6,ss.getVolume(),"Invalid volume!");
    }

    @Test
    void volumeDown() {
        SmartSpeaker ss = new SmartSpeaker(1,1, "RFM", new Marca("ATS"), 0.05);
        ss.volumeDown();
        assertEquals(0,ss.getVolume(),"Invalid volume!");
    }
}