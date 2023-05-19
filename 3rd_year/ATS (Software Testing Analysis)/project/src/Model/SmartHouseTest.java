package Model;

import org.junit.jupiter.api.Test;

import java.time.LocalDate;
import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

class SmartHouseTest {

    @Test
    void getDataCriacao() {
        SmartHouse sh = new SmartHouse();
        assertEquals(LocalDate.now(),sh.getDataCriacao(),"Invalid date of creation");
    }

    @Test
    void setNome_prop() {
        SmartHouse sh = new SmartHouse();
        sh.setNome_prop("ATS");
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade");
        assertEquals(house.getNome_prop(),sh.getNome_prop(),"Invalid name!");
    }

    @Test
    void setNIF_prop() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade");
        assertEquals(123456789,house.getNIF_prop(),"Invalid NIF!");
    }

    @Test
    void getTotalCustoInstalacao() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade");
        assertEquals(0, house.getTotalCustoInstalacao(), "Invalid installation cost!");
    }

    @Test
    void setMorada() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade");
        assertEquals("Rua da universidade",house.getMorada(),"Invalid address!");
    }

    @Test
    void setConsumo() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade");
        house.setConsumo(10.0);
        assertEquals(10.0,house.getConsumo(),"Invalid consumption!");
    }

    @Test
    void setCompanhia_eletrica() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        assertEquals("EDP", house.getCompanhia_eletrica().getNome(), "Invalid company");
    }

    @Test
    void getHouse() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("sala");
        house.addDivisao("quarto");
        SmartCamera sc = new SmartCamera(20, "1920x1080", 10000, 10.0f);
        SmartBulb sb = new SmartBulb(15, SmartDevice.state.OFF);
        SmartDevice sd1 = sc;
        SmartDevice sd2 = sb;
        house.addDevice("sala",sd1);
        house.addDevice("quarto",sd2);
        HashMap<String, Map<Integer, SmartDevice>> casa = new HashMap<>();
        Map<Integer, SmartDevice> div1 = new HashMap<>();
        Map<Integer, SmartDevice> div2 = new HashMap<>();
        div1.put(sd2.getID(),sd2);
        div2.put(sd1.getID(),sd1);
        casa.put("quarto", div1);
        casa.put("sala", div2);
        assertEquals(casa,house.getHouse(),"Invalid house devices");
    }

    @Test
    void getDivisao() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("sala");
        assertEquals(new HashMap<Integer, SmartDevice>(),house.getDivisao("sala"), "Invalid division!");
    }

    @Test
    void setDeviceOn() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        SmartCamera sc = new SmartCamera(20, "1920x1080", 10000, 10.0f);
        SmartDevice sd = sc;
        house.addDevice("suite",sd);
        house.setDeviceOn(20);
        assertTrue(house.getDivisao("suite").values().stream().allMatch(sds -> sds.getEstado().equals(SmartDevice.state.ON)));
    }

    @Test
    void setDivisaoOn() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        SmartCamera sc = new SmartCamera(20, "1920x1080", 10000, 10.0f);
        SmartBulb sb = new SmartBulb(15, SmartDevice.state.OFF);
        SmartDevice sd1 = sc;
        SmartDevice sd2 = sb;
        house.addDevice("suite",sd1);
        house.addDevice("suite",sd2);
        house.setDivisaoOn("suite");
        assertTrue(house.getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.ON)));
    }

    @Test
    void setHouseOn() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        house.addDivisao("sala");
        SmartCamera sc = new SmartCamera(15, "1920x1080", 10000, 10.0f);
        SmartBulb sb = new SmartBulb(16, SmartDevice.state.OFF);
        SmartCamera sc1 = new SmartCamera(17, "1920x1080", 10000, 10.0f);
        SmartBulb sb1 = new SmartBulb(18, SmartDevice.state.OFF);
        SmartDevice sd1 = sc;
        SmartDevice sd2 = sb;
        SmartDevice sd3 = sc1;
        SmartDevice sd4 = sb1;
        house.addDevice("suite",sd1);
        house.addDevice("sala",sd2);
        house.addDevice("suite",sd3);
        house.addDevice("sala",sd4);
        house.setHouseOn();
        assertTrue(house.getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.ON)));
        assertTrue(house.getDivisao("sala").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.ON)));
    }

    @Test
    void setDeviceOFF() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        SmartCamera sc = new SmartCamera(20, "1920x1080", 10000, 10.0f);
        SmartDevice sd = sc;
        house.addDevice("suite",sd);
        house.setDeviceOFF(20);
        assertTrue(house.getDivisao("suite").values().stream().allMatch(sds -> sds.getEstado().equals(SmartDevice.state.OFF)));
    }

    @Test
    void setDivisaoOFF() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        SmartCamera sc = new SmartCamera(20, "1920x1080", 10000, 10.0f);
        SmartBulb sb = new SmartBulb(15, SmartDevice.state.OFF);
        SmartDevice sd1 = sc;
        SmartDevice sd2 = sb;
        house.addDevice("suite",sd1);
        house.addDevice("suite",sd2);
        house.setDivisaoOFF("suite");
        assertEquals(sd1.getEstado(),house.getDevice(20).getEstado(),"Device 1 still on");
        assertEquals(sd2.getEstado(),house.getDevice(15).getEstado(),"Device 2 still on");
        assertTrue(house.getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.OFF)));
    }

    @Test
    void setHouseOFF() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        house.addDivisao("sala");
        SmartCamera sc = new SmartCamera(15, "1920x1080", 10000, 10.0f);
        SmartBulb sb = new SmartBulb(16, SmartDevice.state.OFF);
        SmartCamera sc1 = new SmartCamera(17, "1920x1080", 10000, 10.0f);
        SmartBulb sb1 = new SmartBulb(18, SmartDevice.state.OFF);
        SmartDevice sd1 = sc;
        SmartDevice sd2 = sb;
        SmartDevice sd3 = sc1;
        SmartDevice sd4 = sb1;
        house.addDevice("suite",sd1);
        house.addDevice("sala",sd2);
        house.addDevice("suite",sd3);
        house.addDevice("sala",sd4);
        house.setHouseOFF();
        assertEquals(sd1.getEstado(),house.getDevice(15).getEstado(),"Device 1 still on");
        assertEquals(sd2.getEstado(),house.getDevice(16).getEstado(),"Device 2 still on");
        assertEquals(sd3.getEstado(),house.getDevice(17).getEstado(),"Device 3 still on");
        assertEquals(sd4.getEstado(),house.getDevice(18).getEstado(),"Device 4 still on");
        assertTrue(house.getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.OFF)));
        assertTrue(house.getDivisao("sala").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.OFF)));
    }

    @Test
    void existsDevice() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        SmartCamera sc = new SmartCamera(15, "1920x1080", 10000, 10.0f);
        SmartDevice sd = sc;
        house.addDevice("suite",sd);
        assertTrue(house.existsDevice(15));
    }

    @Test
    void getConsumoDivisao() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("quarto");
        house.setConsumo(10000.00);
        assertEquals(0.0,house.getConsumoDivisao(house.getDivisao("quarto")), "Invalid consume value!");
    }

    @Test
    void removeDivisao() {
        SmartHouse sh = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        sh.addDivisao("quarto");
        sh.addDivisao("sala");
        sh.addDivisao("cozinha");
        assertTrue(sh.hasDivisao("quarto"));
        assertTrue(sh.hasDivisao("sala"));
        assertTrue(sh.hasDivisao("cozinha"));
        sh.removeDivisao("quarto");
        assertFalse(sh.hasDivisao("quarto"));
    }

    @Test
    void hasDivisao() {
        SmartHouse sh = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        sh.addDivisao("quarto");
        sh.addDivisao("sala");
        sh.addDivisao("cozinha");
        assertTrue(sh.hasDivisao("quarto"));
        assertTrue(sh.hasDivisao("sala"));
        assertTrue(sh.hasDivisao("cozinha"));
        assertFalse(sh.hasDivisao("quarto de hóspedes"));
    }

    @Test
    void getConsumoDaCasa() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.setConsumo(10000.00);
        assertEquals(0.0,house.getConsumoDaCasa(), "Invalid consume value!");
    }

    @Test
    void mudaDeFornecedor() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdola");
        assertTrue("EDP".equals(house.getCompanhia_eletrica().getNome()));
        house.mudaDeFornecedor(ce, LocalDate.now());
        assertTrue(ce.getNome().equals(house.getCompanhia_eletrica().getNome()));
        assertFalse(house.getCompanhia_eletrica().getNome().equals("EDP"));
    }

    @Test
    void terminaContrato() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        assertTrue("EDP".equals(house.getCompanhia_eletrica().getNome()));
        house.terminaContrato();
        assertEquals(null, house.getCompanhia_eletrica(), "Still has a electric company!");
    }

    @Test
    void getNomeDivisoes() {
        SmartHouse sh = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        sh.addDivisao("quarto");
        sh.addDivisao("casa de banho");
        Set<String> s = new HashSet<>();
        s.add("quarto");
        s.add("casa de banho");
        assertTrue(sh.getNomeDivisoes().equals(s));
    }

    @Test
    void getTotalDivisions() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("quarto");
        house.addDivisao("casa de banho");
        assertTrue(house.getTotalDivisions() == 2);
    }

    @Test
    void getDivisaoList() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("quarto");
        house.addDivisao("casa de banho");
        List<String> list = new ArrayList<>();
        list.add("quarto");
        list.add("casa de banho");
        assertTrue(house.getDivisaoList().equals(list));
    }

    @Test
    void getDevicesDivisao() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("quarto");
        SmartCamera sc1 = new SmartCamera(15, "1920x1080", 10000, 10.0f);
        SmartCamera sc2 = new SmartCamera(16, "1280x720", 11000, 10.0f);
        Map<Integer, SmartDevice> division = new HashMap<>();
        division.put(sc1.getID(),sc1);
        division.put(sc2.getID(), sc2);
        house.addDevice("quarto", sc1);
        house.addDevice("quarto", sc2);
        assertEquals(division, house.getDevicesDivisao("quarto"));
    }

    @Test
    void getDivisaoByIndex() {
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("quarto");
        house.addDivisao("casa de banho");
        assertTrue("quarto".equals(house.getDivisaoByIndex(0)));
        assertTrue("casa de banho".equals(house.getDivisaoByIndex(1)));
    }
}