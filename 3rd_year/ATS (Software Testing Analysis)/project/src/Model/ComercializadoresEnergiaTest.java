package Model;

import org.junit.jupiter.api.Test;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class ComercializadoresEnergiaTest {

    @Test
    void hasFaturado() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        assertEquals(false, ce.hasFaturado(), "Invalid value!");
    }

    @Test
    void getNumeroDeCliente() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        assertEquals(0, ce.getNumeroDeCliente(), "Invalid number of clients!");
    }

    @Test
    void getCasas() throws CloneNotSupportedException {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        assertEquals(0, ce.getCasas().size(), "Invalid number of clients!");
    }

    @Test
    void setCasas() throws CloneNotSupportedException {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        SmartHouse sh = new SmartHouse();
        Fatura fat = new Fatura(LocalDate.ofYearDay(2001,15), LocalDate.now(), 2.0, 15.0);
        List<Fatura> fs = new ArrayList<>();
        fs.add(fat);
        HashMap<SmartHouse, List<Fatura>> casa = new HashMap<>();
        casa.put(sh,fs);
        ce.setCasas(casa);
        assertEquals(1, ce.getCasas().size(), "Invalid number of houses!");
    }

    @Test
    void addCasa()  {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        SmartHouse sh = new SmartHouse();
        SmartHouse house = new SmartHouse(10, "ATS", 123456789, "Rua da Universidade");
        Fatura fat = new Fatura(LocalDate.ofYearDay(2000,15), LocalDate.now(), 2.0, 15.0);
        ce.addCasa(house);
        ce.addCasa(sh);
        ce.addFatura(fat,sh);
        ce.addFatura(fat,house);
        assertEquals(2, ce.getNumeroDeClientes(), "Invalid number of houses!");
    }

    @Test
    void clonaFaturas() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        SmartHouse sh = new SmartHouse();
        Fatura fat = new Fatura(LocalDate.ofYearDay(2000,15), LocalDate.now(), 2.0, 15.0);
        List<Fatura> f = new ArrayList<>();
        ce.addCasa(sh);
        f.add(fat);
        ce.addFatura(fat,sh);
        assertEquals(f,ce.clonaFaturas(f), "Not cloned correctly!");
    }

    @Test
    void removeCasa() throws CloneNotSupportedException {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        SmartHouse sh = new SmartHouse();
        SmartHouse house = new SmartHouse(10, "Pai Natal", 123456789, "Rua da universidade");
        ce.addCasa(house);
        ce.addCasa(sh);
        ce.removeCasa(house);
        assertEquals(1, ce.getCasas().size(), "Invalid number of houses!");
    }

    @Test
    void getPrecoBaseKW() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        assertEquals(0.142, ce.getPrecoBaseKW(), "Invalid default price kw!");
    }

    @Test
    void setPrecoBaseKW() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        ce.setPrecoBaseKW(0.15);
        assertEquals(0.15, ce.getPrecoBaseKW(), "Invalid default price kw!");
    }

    @Test
    void getNome() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("EDP");
        assertEquals("EDP", ce.getNome(), "Invalid name!");
    }

    @Test
    void setNome() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        ce.setNome("EDP");
        assertEquals("EDP", ce.getNome(), "Invalid name!");
    }

    @Test
    void getFatorImposto() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        assertEquals(0.001, ce.getFatorImposto(), "Invalid tax value!");
    }

    @Test
    void setFatorImposto() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        ce.setFatorImposto(0.002);
        assertEquals(0.002, ce.getFatorImposto(), "Invalid tax value!");
    }

    @Test
    void geraFatura() throws CloneNotSupportedException {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartHouse sh = new SmartHouse();
        Fatura fat = new Fatura(sh.getDataCriacao(), LocalDate.now(), sh.getConsumoDaCasa(), sh.getConsumoDaCasa()*ce.getFatorImposto()*ce.getPrecoBaseKW());
        HashMap<SmartHouse, List<Fatura>> casa = new HashMap<>();
        ce.setCasas(casa);
        assertEquals(fat, ce.geraFatura(sh, LocalDate.now()), "Invalid generation!");
    }

    @Test
    void addFatura() throws CloneNotSupportedException {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartHouse sh = new SmartHouse();
        ce.addCasa(sh);
        Fatura fat = new Fatura(sh.getDataCriacao(), LocalDate.now(), sh.getConsumoDaCasa(), sh.getConsumoDaCasa()*ce.getFatorImposto()*ce.getPrecoBaseKW());
        ce.addFatura(fat,sh);
        assertEquals(1, ce.getFaturas(sh).size(), "Receipt not added!");
    }

    @Test
    void getFaturas() throws CloneNotSupportedException {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartHouse sh = new SmartHouse();
        Fatura fat = new Fatura(sh.getDataCriacao(), LocalDate.now(), sh.getConsumoDaCasa(), sh.getConsumoDaCasa()*ce.getFatorImposto()*ce.getPrecoBaseKW());
        ce.addCasa(sh);
        ce.addFatura(fat, sh);
        List<Fatura> f = new ArrayList<>();
        f.add(fat);
        assertEquals(f,ce.getFaturas(sh), "Couldn't get receipts!");
    }

    @Test
    void terminaContrato() throws CloneNotSupportedException {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartHouse sh = new SmartHouse();
        ce.addCasa(sh);
        ce.terminaContrato(sh);
        assertEquals(sh.getCompanhia_eletrica().getNome().equals(""), ce.getCasas().keySet().isEmpty(),"Operation failed");
    }

    @Test
    void getPrecoPerDevice() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartBulb sb = new SmartBulb(1, SmartDevice.state.OFF);
        SmartDevice sd = sb;
        double price =(ce.getPrecoBaseKW()*sd.getConsumo()*(1+ce.getFatorImposto()))*0.9;
        assertEquals(price,ce.getPrecoPerDevice(sd), "Invalid price per device!");
    }

    @Test
    void getCasaMaisGastadora() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartHouse sh = new SmartHouse();
        ce.addCasa(sh);
        assertEquals(sh,ce.getCasaMaisGastadora(), "Invalid more spender house!");
    }

    @Test
    void setNumerodeClientes() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartHouse sh = new SmartHouse();
        ce.addCasa(sh);
        ce.setNumerodeClientes(10);
        assertEquals(10,ce.getNumeroDeCliente(), "Invalid number of clients!");
    }

    @Test
    void getNumeroDeClientes() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        SmartHouse sh = new SmartHouse();
        ce.addCasa(sh);
        assertEquals(1,ce.getNumeroDeCliente(), "Invalid number of clients!");
    }

    @Test
    void getFaturacao() {
        ComercializadoresEnergia ce = new ComercializadoresEnergia("Iberdrola");
        assertEquals(0.0,ce.getFaturacao(), "Invalid receipt!");
    }

}