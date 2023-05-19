package Model;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SmartCameraTest {

    @Test
    void getConsumo() {
        SmartCamera sc = new SmartCamera(1,"1920x1080", 1024, 0.05);
        assertEquals(0,sc.getConsumo(),"Invalid consume!");
    }

    @Test
    void getResolucao() {
        SmartCamera sc = new SmartCamera(1, 1920, 1080, 10000, SmartDevice.state.OFF, 0.05f);
        assertEquals(1920*1080/1000000f,sc.getResolucao(), "Invalid resolution!");
    }

    @Test
    void setResolucao() {
        SmartCamera sc = new SmartCamera(1, 1920, 1080, 10000, SmartDevice.state.OFF, 0.05f);
        sc.setResolucao(1280,720);
        assertEquals(1280*720/10000000f,sc.getResolucao(), "Invalid resolution!");
    }

    @Test
    void getFileSize() {
        SmartCamera sc = new SmartCamera(1, 1920, 1080, 10000, SmartDevice.state.OFF, 0.05f);
        assertEquals(10000,sc.getFileSize(), "Invalid file size!");
    }

    @Test
    void setFileSize() {
        SmartCamera sc = new SmartCamera(1, 1920, 1080, 10000, SmartDevice.state.OFF, 0.05f);
        sc.setFileSize(11000);
        assertEquals(11000,sc.getFileSize(), "Invalid file size!");
    }
}


