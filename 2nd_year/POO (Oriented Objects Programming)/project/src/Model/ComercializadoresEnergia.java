package Model;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ComercializadoresEnergia implements Serializable {

    private String nome;
    private double precoBaseKW;
    private double fatorImposto;
    private Map<SmartHouse,List<Fatura>> casas;
    private int numeroDeClientes;
    private boolean faturado=false;

    /**
     * Função que inicializa um comercializador
     * @param nome Nome do fornecedor
     */
    public ComercializadoresEnergia(String nome){
        this.nome=nome;
        this.precoBaseKW= 0.142;
        this.fatorImposto= 0.001;
        this.casas = new HashMap<>();
        this.numeroDeClientes=0;
    }

    /**
     * Função que inicializa um comercializador
     * @param nome Nome do fornecedor
     * @param casa SmartHouse a adicionar
     * @param fat Faturas da casa a adicionar
     */
    public ComercializadoresEnergia(String nome,SmartHouse casa,List<Fatura> fat){
        this.nome=nome;
        this.precoBaseKW= 0.142;
        this.fatorImposto= 0.001;
        this.casas = new HashMap<>();
        this.casas.putIfAbsent(casa,fat);
        this.numeroDeClientes=0;
    }

    /**
     * Função que inicializa um comercializador
     * @param nome Nome do fornecedor
     * @param precoBaseKW preço base por kW do fornecedor
     * @param fatorImposto fator de imposto
     * @param numeroDeClientes numero de clientes de um fornecedor
     */
    public ComercializadoresEnergia(String nome,double precoBaseKW, double fatorImposto, int numeroDeClientes){
        this.nome=nome;
        this.precoBaseKW=precoBaseKW;
        this.fatorImposto=fatorImposto;
        this.casas = new HashMap<>();
        this.numeroDeClientes=numeroDeClientes;
    }

    /**
     * Função que inicializa um comercializador
     * @param nome Nome do fornecedor
     * @param precoBaseKW preço base por kW do fornecedor
     * @param fatorImposto fator de imposto
     */
    public ComercializadoresEnergia(String nome,double precoBaseKW, double fatorImposto){
        this.nome=nome;
        this.precoBaseKW=precoBaseKW;
        this.fatorImposto=fatorImposto;
        this.casas = new HashMap<>();
        this.numeroDeClientes=0;
    }

    public boolean hasFaturado(){return this.faturado;}

    /**
     * Função que inicializa um comercializador
     * @param nome Nome do fornecedor
     * @param precoBaseKW preço base por kW do fornecedor
     * @param fatorImposto fator de imposto
     * @param casas Map de casas com as respetivas faturas
     */
    public ComercializadoresEnergia(String nome,double precoBaseKW, double fatorImposto,Map<SmartHouse,List<Fatura>> casas) throws CloneNotSupportedException {
        this.nome=nome;
        this.precoBaseKW=precoBaseKW;
        this.fatorImposto=fatorImposto;
        Map<SmartHouse,List<Fatura>> casinhasNovas=new HashMap<>();
        for(SmartHouse casa:casas.keySet()){
            List<Fatura> casinhas = new ArrayList<>(casas.get(casa));
            casinhasNovas.putIfAbsent(casa.clone(), casinhas);
            this.numeroDeClientes+=1;
        }
        this.casas=casinhasNovas;
    }


    /**
     * Função que inicializa um comercializador
     * @param ce Cópia de cápsula
     */
    public ComercializadoresEnergia(ComercializadoresEnergia ce) throws CloneNotSupportedException {
        this.nome=ce.getNome();
        this.precoBaseKW = ce.getPrecoBaseKW();
        this.fatorImposto= ce.getFatorImposto();
        this.casas = ce.getCasas();
        this.numeroDeClientes=ce.getNumeroDeCliente();
        this.faturado=false;
    }

    /**
     * Getter do número de clientes
     * @return número de clientes
     */
    public int getNumeroDeCliente(){return this.numeroDeClientes;}

    /**
     * Getter de casas
     * @return Map de casas com as respetivas faturas
     */
    public Map<SmartHouse,List<Fatura>> getCasas() throws CloneNotSupportedException {
        Map<SmartHouse,List<Fatura>> casinhasNovas=new HashMap<>();
        for(SmartHouse casa:casas.keySet()){
            List<Fatura> casinhas = new ArrayList<>(casas.get(casa));
            casinhasNovas.put(casa.clone(), casinhas);
        }
        return casinhasNovas;
    }

    /**
     * Setter de casas
     * @param casas Map de casas com as respetivas faturas
     */
    public void setCasas(Map<SmartHouse,List<Fatura>> casas) throws CloneNotSupportedException {
        Map<SmartHouse,List<Fatura>> casinhasNovas=new HashMap<>();
        for(SmartHouse casa:casas.keySet()){
            casinhasNovas.put(casa.clone(), clonaFaturas(casas.get(casa)));
            this.numeroDeClientes+=1;
        }
        this.casas=casinhasNovas;
    }

    /**
     * Adiciona uma casa a um fornecedor
     * @param casa Casa a adicionar
     */
    public void addCasa(SmartHouse casa){
        this.casas.put(casa, new ArrayList<>());
        this.numeroDeClientes++;
    }

    /**
     * Adiciona uma casa a um fornecedor com as faturas já existentes
     * @param casa Casa a adicionar
     * @param faturas Lista de fatura da casa
     */
    public void addCasa(SmartHouse casa, List<Fatura> faturas){
        this.casas.put(casa,clonaFaturas(faturas)); this.numeroDeClientes++;
    }

    /**
     * Dá clone às faturas
     * @param faturas Lista de fatura da casa
     */
    public List<Fatura> clonaFaturas(List<Fatura> faturas){
        return new ArrayList<>(faturas);
    }

    /**
     * Remove casa do comercializador
     * @param casa Casa a retirar
     */
    public void removeCasa(SmartHouse casa){
        this.casas.remove(casa);
        // casa fica sem luz
        this.numeroDeClientes--;
    }

    /**
     * Remove casa do comercializador
     * @param morada Morada da casa a retirar
     */
    public void removeCasa(String morada){
        for (SmartHouse casa:this.casas.keySet()){
            if(casa.getMorada().equals(morada)){
                this.casas.remove(casa);
                this.numeroDeClientes--;
            }
        }
    }


    /**
     * Getter preço base kW
     * @return preço base kW
     */
    public double getPrecoBaseKW(){return this.precoBaseKW;}

    /**
     * Getter nome do comercializador
     * @return nome do comercializador
     */
    public String getNome(){return this.nome;}

    /**
     * Setter nome do comercializador
     * @param nome nome do fornecedor
     */
    public void setNome(String nome){ this.nome=nome;}

    /**
     * Setter preço base do comercializador
     * @param preco preço base do fornecedor
     */
    public void setPrecoBaseKW(double preco){ this.precoBaseKW = preco; }

    /**
     * Setter fator de imposto do comercializador
     * @param fator fator de imposto do comercialzizador
     */
    public void setFatorImposto(double fator){ this.fatorImposto = fator; }

    /**
     * Getter fator de imposto do comercializador
     * @return fator imposto
     */
    public double getFatorImposto(){return this.fatorImposto;}


    /**
     * Função que gera fatura de uma casa
     * @param casa Casa a ser retirada a fatura
     * @param data_final Data final da fatura
     * @return Fatura gerada
     */
    public Fatura geraFatura(SmartHouse casa, LocalDate data_final){
        Fatura newFatura;
        if (this.casas.containsKey(casa)){
            List<Fatura> faturas = this.casas.get(casa);
            newFatura = new Fatura(casa.getDataCriacao(), data_final, casa.getConsumoDaCasa(), casa.getConsumoDaCasa()*this.fatorImposto*this.precoBaseKW);
            faturas.add(newFatura);
        }
        else{
            List<Fatura> faturas = new ArrayList<>();
            newFatura = new Fatura(casa.getDataCriacao(), data_final, casa.getConsumoDaCasa(), casa.getConsumoDaCasa()*this.fatorImposto*this.precoBaseKW);
            faturas.add(newFatura);
            this.casas.put(casa,faturas);
        }

        return newFatura;
    }

    /**
     * Função que adiciona fatura a uma casa
     * @param fat Fatura a adicionar
     * @param casa Casa a ser adicionada a fatura
     */
    public void addFatura(Fatura fat, SmartHouse casa){
        try{
            this.casas.get(casa).add(fat);
        } catch(Exception e){System.out.println("Não existe casa, erro "+e); }

    }

    /**
     * Getter das faturas de uma determinada casa
     * @param casa Casa em investigação
     * @return Lista de faturas de uma casa
     */
    public List<Fatura> getFaturas(SmartHouse casa) throws CloneNotSupportedException {
        List<Fatura> faturas = new ArrayList<>();
        if(this.casas.containsKey(casa)){
            for (Fatura fatura : this.casas.get(casa)) faturas.add(fatura.clone());
        }
        return faturas;
    }

    /**
     * Função que termina o contrato do forneecedor com uma casa
     * @param casa Casa a terminar o contrato
     */
    public void terminaContrato(SmartHouse casa){
        removeCasa(casa);
    }

    /**
     * FUnção que calcula o preço de consumo de um smartdevice
     * @param sd Smartdevice
     * @return preço do dispositivo
     */
    public double getPrecoPerDevice(SmartDevice sd){
        return (this.precoBaseKW*sd.getConsumo()*(1+this.fatorImposto))*0.9;
    }

    /**
     * Casa mais gastadora de sempre de um fornecedor
     * @return casa mais gastadora
     */
    public SmartHouse getCasaMaisGastadora(){
        SmartHouse casaMaisGastadora=null;
        double maxConsumo=0;
        for(SmartHouse casa:this.casas.keySet()) {
            double consumo = casa.getConsumoDaCasa();
            if ((consumo > maxConsumo) || (casaMaisGastadora == null)) {
                maxConsumo = consumo;
                casaMaisGastadora = casa;
            }
        }
        return casaMaisGastadora;
    }


    /**
     * Setter do número de clientes
     * @param numero Numero de clientes
     */
    public void setNumerodeClientes(int numero){ this.numeroDeClientes = numero; }

    /**
     * Getter do número de clientes de um fornecedor
     * @return numero de clientes
     */
    public int getNumeroDeClientes(){ return this.numeroDeClientes;}


    /**
     * FUnção que calcula casa mais gastadora de um fornecedor em determinado periodo de tempo
     * @param dataInit Data de inicio do periodo de tempo
     * @param dataFin Data de fim do periodo do tempo
     * @return casa mais gastadora
     */
    public SmartHouse getCasaMaisGastadora(LocalDate dataInit, LocalDate dataFin){
        SmartHouse casaMaisGastadora=null;
        double maxConsumo=0;
        if (!this.faturado){

        }
        for(SmartHouse casa:this.casas.keySet()){
            List<Fatura> faturas = this.casas.get(casa);
            for (Fatura faturaTemp : faturas) {
                if (faturaTemp.getDataInicial().isBefore(dataInit) && faturaTemp.getDataFinal().isAfter(dataFin)) {
                    if (faturaTemp.getKwsConsumidos() > maxConsumo || casaMaisGastadora == null) {
                        casaMaisGastadora = casa;
                        maxConsumo = faturaTemp.getKwsConsumidos();
                    }
                }
            }
        }
        return casaMaisGastadora;
    }


    /**
     * Função que calcula a faturação
     * @return faturação
     */
    public double getFaturacao(){
        double faturacao=0;
        for(List<Fatura> faturasDeCadaCasa:this.casas.values()){
            for (Fatura fatura : faturasDeCadaCasa) faturacao += fatura.getValorDaFatura();
        }
        return faturacao;
    }

    /**
     * Função que gera faturação de um fornecedor
     * @param data_final Data onde de retirar a faturação
     */
    public void faturacao(LocalDate data_final){
        for(SmartHouse casa:this.casas.keySet()) {
            if(this.casas.get(casa).size()==0)
                geraFatura(casa, data_final);
            //casa.setConsumo(0);
        }
        this.faturado=true;
    }


    /**
     * FUnção que retorna a lista de faturação de um fornecedor
     * @param time tempo de faturação
     */
    public void faturacao(String time){
        for(SmartHouse casa:this.casas.keySet()) {
            LocalDate data_final= casa.getDataCriacao().plusDays(Integer.parseInt(time));
            if(!hasFaturado())
                geraFatura(casa, data_final);
        }
        this.faturado=true;
    }

    public String getListaFaturacao(){
        StringBuilder sb = new StringBuilder();
        for (SmartHouse casa:this.casas.keySet()){
            sb.append(casa.getID());
            sb.append("\n");
            for (Fatura fatura:this.casas.get(casa)){
                sb.append(fatura.toString());
                sb.append("\n");
            }
        }
        return sb.toString();
    }


    /**
     * Funçaõ que lista os clientes de um fornecedor
     * @return String com a lista de clientes
     */
    public String listOfClientes(){
        StringBuilder sb = new StringBuilder();
        
        for(SmartHouse casa:this.casas.keySet()){
            sb.append(casa.getID());  
            sb.append(this.casas.get(casa).toString());
        }
        
        return sb.toString();
    }

    /**
     * Função que compara o comercializador com um objeto para ver se são iguais
     * @param obj objeto
     * @return bool de comparação
     */
    public boolean equals(Object obj){
        if (this==obj) return true;
        if (obj==null||this.getClass()!=obj.getClass()) return false;
        ComercializadoresEnergia ce = (ComercializadoresEnergia) obj;
        return (this.nome.equals(ce.getNome())  &&  this.precoBaseKW == (ce.getPrecoBaseKW()) && this.fatorImposto == (ce.getFatorImposto()));
    }

    /**
     * Função que clona um forncedor
     * @return Comercizalidor clonado
     */
    public ComercializadoresEnergia clone() throws CloneNotSupportedException {
        return new ComercializadoresEnergia(this);
    }

    /**
     * toString de um comercializador
     * @return String com os dados do comercializador
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nNOME: ");
        sb.append(this.nome);
        sb.append("\tPREÇO BASE: ");
        sb.append(this.precoBaseKW);
        sb.append("\tIMPOSTO ENERGÉTICO: ");
        sb.append(this.fatorImposto);
        sb.append("\tTOTAL CLIENTES: ");
        /*
        for(SmartHouse casa:this.casas.keySet()){
            sb.append(casa.getID());
            sb.append(this.casas.get(casa).toString());
        }*/
        sb.append(this.numeroDeClientes);
        return sb.toString();
    }

}
