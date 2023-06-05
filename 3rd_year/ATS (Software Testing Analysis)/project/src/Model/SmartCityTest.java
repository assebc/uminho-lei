package Model;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.time.LocalDate;

import static org.junit.jupiter.api.Assertions.*;

class SmartCityTest {

    @Test
    void merge() {
        SmartCity city1 = new SmartCity();
        SmartCity city2 = new SmartCity();
        SmartCity city3 = new SmartCity();
        SmartHouse house1 = new SmartHouse(10,"Pai Natal",123456789, new ComercializadoresEnergia("EDP"));
        SmartHouse house2 = new SmartHouse(12,"Mãe Natal",123456780, new ComercializadoresEnergia("EDP"));
        city3.createHouse(house1);
        city3.createHouse(house2);
        assertTrue(city1.getCasas().size() == city2.getCasas().size());
        assertFalse(city1.equals(city3));
        city1.merge(city3);
        assertFalse(city1.getCasas().size() == city2.getCasas().size());
        assertEquals(city3.getCasas().values().size(), city1.getCasas().values().size(), "Smart city not well merged!");
    }

    @Test
    void states() throws IOException, ClassNotFoundException {
        SmartCity city = new SmartCity();
        city.createHouse(new SmartHouse(10, "Pai Natal", 123456789, "Rua do Pai Natal", new ComercializadoresEnergia("EDP")));
        city.saveState("teste");
        SmartCity city2 = new SmartCity();
        SmartCity city_tmp = city2.loadState("teste");
        assertEquals(city.getCasas().size(), city_tmp.getCasas().size(), "Cities are not identical!");
    }

    @Test
    void giveId() {
        SmartCity city = new SmartCity();
        int id_house = city.giveHouseId();
        int id_device = city.giveDeviceId();
        assertTrue(id_house == 1);
        assertTrue(id_device == 1);
    }

    @Test
    void hasComercializador() {
        SmartCity city = new SmartCity();
        city.createComercializadorEnergia("EDP");
        assertTrue(city.hasComercializador("EDP"));
    }
    @Test
    void getCasaMaisGastadora() {
        SmartCity city = new SmartCity();
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        ComercializadoresEnergia ce2 = new ComercializadoresEnergia("Iberdola");
        Fatura fat = new Fatura(LocalDate.ofYearDay(2000,15),  LocalDate.now(), 20.0, 100.0);
        SmartHouse house =  new SmartHouse(10, "Rui Pedro", 123456789, "Lousada", ce);
        SmartHouse house2 = new SmartHouse(15, "Maddie Faisa Macqueen", 12346678, "Rua do Algarve", ce);
        ce.addFatura(fat,house);
        city.createHouse(house);
        city.createHouse(house2);
        city.createComercializadorEnergia(ce);
        city.createComercializadorEnergia(ce2);
        assertTrue(city.getCasaMaisGastadora("5").equals(city.getCasa(0)));
    }

    @Test
    void getCasaMaisGastadora2(){
        SmartCity city = new SmartCity();
        ComercializadoresEnergia edp = new ComercializadoresEnergia("edp");
        SmartHouse house = new SmartHouse(10, "Rui Pedro", 123456789, "Lousada", edp);
        house.setConsumo(20.0);
        Fatura fat = new Fatura(LocalDate.ofYearDay(2000,30), LocalDate.now(), 50.0, 150.0);
        edp.addFatura(fat, house);
        city.createHouse(house);
        city.createComercializadorEnergia(edp);
        assertTrue(city.getCasaMaisGastadora("5").equals(city.getCasa(0)));
    }

    @Test
    void getCasaMaisGastadora3(){
        SmartCity city = new SmartCity();
        ComercializadoresEnergia edp = new ComercializadoresEnergia("edp");
        SmartHouse house = new SmartHouse(10, "Rui Pedro", 123456789, "Lousada", edp);
        house.setConsumo(20.0);
        SmartHouse house2 = new SmartHouse(15, "Rui Pedro", 123456789, "Lousada", edp);
        house.setConsumo(50.0);
        Fatura fat = new Fatura(LocalDate.ofYearDay(2000,30), LocalDate.now(), 50.0, 150.0);
        Fatura fat2 = new Fatura(LocalDate.ofYearDay(2000,10), LocalDate.now(), 50.0, 150.0);
        edp.addFatura(fat, house);
        edp.addFatura(fat2,house2);
        city.createHouse(house);
        city.createHouse(house2);
        city.createComercializadorEnergia(edp);
        assertTrue(city.getCasaMaisGastadora("20").equals(city.getCasa(1)));
    }

    @Test
    void getComercializadorMaiorFaturacao() {
        SmartCity city = new SmartCity();
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        ComercializadoresEnergia ce2 = new ComercializadoresEnergia("Iberdola");
        Fatura fat = new Fatura(LocalDate.ofYearDay(2000,15),  LocalDate.now(), 20.0, 100.0);
        SmartHouse house =  new SmartHouse(10, "Rui Pedro", 123456789, "Lousada", ce);
        ce.addFatura(fat,house);
        city.createHouse(house);
        city.createComercializadorEnergia(ce);
        city.createComercializadorEnergia(ce2);
        assertFalse(city.getComercializadorMaiorFaturacao().equals(city.getComercializador("EDP")));
    }

    @Test
    void createComercializadorEnergia() {
        SmartCity city = new SmartCity();
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        city.createComercializadorEnergia(ce);
        assertTrue(city.getComercializador("EDP").equals(ce));
    }

    @Test
    void mudaDeFornecedorString() {
        SmartCity city = new SmartCity();
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        city.createComercializadorEnergia(ce);
        SmartHouse house = new SmartHouse(10, "Pai Natal", 123456789, "Rua da universidade", new ComercializadoresEnergia("Iberdola"));
        city.createHouse(house);
        assertEquals("Iberdola", city.getCasa(0).getCompanhia_eletrica().getNome(), "Invalid eletric company!");
        city.mudaDeFornecedorString(0, "EDP", LocalDate.now());
        assertEquals("EDP", city.getCasa(0).getCompanhia_eletrica().getNome(), "Value of eletric company didnt change!");
    }
    @Test
    void criaDivisao() {
        SmartCity city = new SmartCity();
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        city.createComercializadorEnergia(ce);
        SmartHouse house = new SmartHouse(10, "Pai Natal", 123456789, "Rua da universidade", new ComercializadoresEnergia("Iberdola"));
        city.createHouse(house);
        city.criaDivisao(0, "quarto");
        city.criaDivisao(0, "cozinha");
        assertTrue(city.getCasa(0).getDivisaoList().size()==2);
    }

    @Test
    void getCasaDivisao() {
        SmartCity city = new SmartCity();
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        city.createComercializadorEnergia(ce);
        SmartHouse house = new SmartHouse(10, "Pai Natal", 123456789, "Rua da universidade", new ComercializadoresEnergia("Iberdola"));
        city.createHouse(house);
        city.criaDivisao(0, "quarto");
        city.criaDivisao(0, "cozinha");
        assertFalse(city.getCasaDivisao(0,"quarto").isEmpty());
    }

    @Test
    void addDeviceToDivisao() {
        SmartCity city = new SmartCity();
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        city.createComercializadorEnergia(ce);
        SmartHouse house = new SmartHouse(10, "Pai Natal", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        city.createHouse(house);
        SmartBulb sb = new SmartBulb(1,"COLD", 10, 0.05);
        SmartDevice sd1 = sb;
        SmartHouse sh = new SmartHouse(20, "Mãe Natal", 123456788, "Rua do Natal", new ComercializadoresEnergia("EDP"));
        sh.addDivisao("quarto");
        sh.addDevice("quarto", sd1);
        city.addDevicePreset("lamp", sd1);
        city.addDeviceToDivisao("quarto", "lamp");
        city.criaDivisao(0,"quarto");
        assertEquals(sh.getDivisao("quarto"), city.getCasa(0).getDivisao("quarto"), "Invalid number of devices!");
    }

    @Test
    void createMarca() {
        SmartCity city = new SmartCity();
        Marca m = new Marca("JBL");
        city.createMarca(m);
        assertTrue(city.getMarca("JBL").equals(m));
    }


    @Test
    void hasSmartHouse() {
        SmartCity city = new SmartCity();
        SmartHouse house = new SmartHouse(10, "Pai Natal", 123456789, "Rua do Pai Natal", new ComercializadoresEnergia("EDP"));
        city.createHouse(house);
        assertTrue(city.hasSmartHouse(0));
    }

    @Test
    void setHouseOFF() {
        SmartCity city = new SmartCity();
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
        city.createHouse(house);
        city.getCasa(0).setHouseOFF();
        assertEquals(sd1.getEstado(),city.getCasa(0).getDevice(15).getEstado(),"Device 1 still on");
        assertEquals(sd2.getEstado(),city.getCasa(0).getDevice(16).getEstado(),"Device 2 still on");
        assertEquals(sd3.getEstado(),city.getCasa(0).getDevice(17).getEstado(),"Device 3 still on");
        assertEquals(sd4.getEstado(),city.getCasa(0).getDevice(18).getEstado(),"Device 4 still on");
        assertTrue(city.getCasa(0).getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.OFF)));
        assertTrue(city.getCasa(0).getDivisao("sala").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.OFF)));
    }

    @Test
    void setCasaDivisaoOFF() {
        SmartCity city = new SmartCity();
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        SmartCamera sc = new SmartCamera(20, "1920x1080", 10000, 10.0f);
        SmartBulb sb = new SmartBulb(15, SmartDevice.state.OFF);
        SmartDevice sd1 = sc;
        SmartDevice sd2 = sb;
        house.addDevice("suite",sd1);
        house.addDevice("suite",sd2);
        city.createHouse(house);
        city.getCasa(0).setDivisaoOFF("suite");
        assertEquals(sd1.getEstado(),city.getCasa(0).getDevice(20).getEstado(),"Device 1 still on");
        assertEquals(sd2.getEstado(),city.getCasa(0).getDevice(15).getEstado(),"Device 2 still on");
        assertTrue(city.getCasa(0).getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.OFF)));
    }

    @Test
    void setHouseOn() {
        SmartCity city = new SmartCity();
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
        city.createHouse(house);
        city.getCasa(0).setHouseOn();
        assertTrue(city.getCasa(0).getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.ON)));
        assertTrue(city.getCasa(0).getDivisao("sala").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.ON)));
    }

    @Test
    void setCasaDivisaoOn() {
        SmartCity city = new SmartCity();
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da universidade", new ComercializadoresEnergia("EDP"));
        house.addDivisao("suite");
        SmartCamera sc = new SmartCamera(20, "1920x1080", 10000, 10.0f);
        SmartBulb sb = new SmartBulb(15, SmartDevice.state.OFF);
        SmartDevice sd1 = sc;
        SmartDevice sd2 = sb;
        house.addDevice("suite",sd1);
        house.addDevice("suite",sd2);
        city.createHouse(house);
        city.getCasa(0).setDivisaoOn("suite");
        assertTrue(city.getCasa(0).getDivisao("suite").values().stream().allMatch(sd -> sd.getEstado().equals(SmartDevice.state.ON)));
    }
}