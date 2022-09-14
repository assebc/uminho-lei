package Model;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/**
 * A SmartHouse faz a gestão dos SmartDevices que existem e dos
 * espaços (as salas) que existem na casa.
 *
 */
public class SmartHouse implements Serializable, Comparable<SmartHouse>{

    private int id;
    private String nome_prop;
    private int NIF_prop;
    private String morada;
    private ComercializadoresEnergia companhia_eletrica;
    private double consumo; //consumo em kWh
    private double totalCustoInstalacao;
    private Map<String,Map<Integer, SmartDevice>> devices = new HashMap<>();
    private LocalDate dataCriacao;

    /**
     * Inicializador de construtor da casa
     */
    public SmartHouse() {
        this.nome_prop = "";
        this.NIF_prop = 0;
        this.morada = "";
        this.devices = new HashMap<>();
        this.companhia_eletrica = new ComercializadoresEnergia("");
        this.dataCriacao=LocalDate.now();
        this.totalCustoInstalacao=0;
    }

    /**
     * Inicializador de construtor de uma casa sem direito a luz
     * @param id id a definir
     * @param nome nome a definir
     * @param NIF nif a definir
     * @param Morada morada a definir
     */
    public SmartHouse(int id, String nome, int NIF, String Morada){
        this.id = id;
        this.nome_prop = nome;
        this.NIF_prop = NIF;
        this.morada = Morada;
        this.companhia_eletrica = null;
        this.dataCriacao=LocalDate.now();
        this.totalCustoInstalacao=0;
    }

    /**
     * Inicializador de construtor de uma casa
     * @param id id a definir
     * @param nome nome a definir
     * @param NIF nif a definir
     * @param morada morada a definir
     * @param comp comercializador a definir
     */
    public SmartHouse(int id,String nome, int NIF, String morada, ComercializadoresEnergia comp) {
        // initialise instance variables
        this.id=id;
        this.nome_prop = nome;
        this.NIF_prop = NIF;
        this.morada = morada;
        this.devices = new HashMap<>();
        this.companhia_eletrica=comp;
        comp.addCasa(this);
        this.dataCriacao=LocalDate.now();
        this.totalCustoInstalacao=0;
    }

    public SmartHouse(int id,String nome, int NIF, String morada, ComercializadoresEnergia comp, LocalDate dataDaCriacao) {
        // initialise instance variables
        this.id=id;
        this.nome_prop = nome;
        this.NIF_prop = NIF;
        this.morada = morada;
        this.devices = new HashMap<>();
        this.companhia_eletrica=comp;
        comp.addCasa(this);
        this.dataCriacao=dataDaCriacao;
        this.totalCustoInstalacao=0;
    }

    /**
     * Inicializador do construtor de uma casa
     * @param id id a definir
     * @param sh casa já pré-definida
     */
    public SmartHouse(int id, SmartHouse sh){ //o id tem sempre de ser passado pela cidade para
        this.id = id;
        this.nome_prop=sh.getNome_prop();
        this.NIF_prop = sh.getNIF_prop();
        this.morada= sh.getMorada();
        this.companhia_eletrica=sh.getCompanhia_eletrica();
        this.companhia_eletrica.addCasa(this);
        this.totalCustoInstalacao=sh.getTotalCustoInstalacao();
    }

    /**
     * Inicializador de um construtor de uma casa
     * @param houseID id a definir
     * @param nome nome a definir
     * @param nif nif a definir
     * @param fornecedor fornecedor a definir
     */
    public SmartHouse(int houseID, String nome,int nif,ComercializadoresEnergia fornecedor){
        this.id = houseID;
        this.nome_prop = nome;
        this.NIF_prop = nif;
        this.morada = "";
        this.companhia_eletrica = fornecedor;
        fornecedor.addCasa(this);
        this.totalCustoInstalacao=0;
    }

    /**
     * Duplicar casa
     * @param sh casa pré-definida
     */
    public SmartHouse(SmartHouse sh){
        this.id = sh.getID();
        this.nome_prop = sh.getNome_prop();
        this.NIF_prop = sh.getNIF_prop();
        this.morada = sh.getMorada();
        this.companhia_eletrica = sh.getCompanhia_eletrica();
        this.companhia_eletrica.addCasa(this);
        this.totalCustoInstalacao=sh.getTotalCustoInstalacao();
        this.consumo=sh.getConsumo();
        this.devices=sh.getHouse();
        this.dataCriacao = sh.getDataCriacao();
    }

    /**
     * Getter do id da casa
     * @return id da casa
     */
    public int getID(){
        return this.id;
    }

    /**
     * Setter do id da casa
     * @param id id a definir
     */
    public void setID(int id){
        this.id = id;
    }


    /**
     * Getter de data de criação
     * @return data de ciração de dispositivo
     */
    public LocalDate getDataCriacao(){
        return this.dataCriacao;
    }

    /**
     * Setter do nome do proprietário
     * @param nome nome a definir
     */
    public void setNome_prop(String nome) { this.nome_prop = nome; }

    /**
     * Getter do nome do proprietário
     * @return nome do proprietário
     */
    public String getNome_prop() { return this.nome_prop; }

    /**
     * Setter do nif do proprietário
     * @param NIF nif a definir
     */
    public void setNIF_prop(int NIF) { this.NIF_prop = NIF;}

    /**
     * Getter nif do proprietário
     * @return nif do proprietário
     */
    public int getNIF_prop(){ return this.NIF_prop; }

    /**
     * Getter custo de instalação acumulado
     * @return custo total de instalação dos dispositivos
     */
    public double getTotalCustoInstalacao(){ return this.totalCustoInstalacao; }

    /**
     * Setter de morada
     * @param morada morada a definir
     */
    public void setMorada(String morada){ this.morada = morada; }

    /**
     * Getter da morada da casa
     * @return morada
     */
    public String getMorada(){ return this.morada; }

    /**
     * Setter de consumo
     * @param consumo consumo a definir
     */
    public void setConsumo(double consumo){this.consumo = consumo;}

    /**
     * Getter consumo da casa
     * @return consumo
     */
    public double getConsumo(){return this.consumo;
    }

    /**
     * Setter de fornecedor de eletricidade
     * @param s comercializador de energia
     */
    public void setCompanhia_eletrica(ComercializadoresEnergia s){this.companhia_eletrica=s; s.addCasa(this);}

    /**
     * Getter de fornecedor de eltricidade
     * @return comercializador de energia
     */
    public ComercializadoresEnergia getCompanhia_eletrica(){return this.companhia_eletrica;}

    /**
     * Coloca todos os dispositivos e divisões em um mapo
     * @return todos os componentes da casa emo um map
     */
    public Map<String,Map<Integer, SmartDevice>> getHouse(){
        Map<String,Map<Integer, SmartDevice>> newHouse = new HashMap<>();
        for (String div:this.devices.keySet()){
            Map<Integer, SmartDevice> devi = new HashMap<>();
            for(SmartDevice sd:this.devices.get(div).values()){
                devi.put(sd.getID(), sd.clone());
            }
            newHouse.put(div, devi);
        }
        return newHouse;
    }


    /**
     * Getter de dispositivos de divisão
     * @param divisao em questão
     * @return map de todos os dispositivos da divisão
     */
    public Map<Integer, SmartDevice> getDivisao(String divisao){
        Map<Integer, SmartDevice> nova = new HashMap<>(this.devices.get(divisao));
        return nova;
    }

    /**
     * Liga determinado dispositivo
     * @param devCode id do dispositivo
     */
    public void setDeviceOn(int devCode) {
        if(this.companhia_eletrica != null) {
            for (Map<Integer, SmartDevice> dispositivos : this.devices.values()) {
                if (dispositivos.containsKey(devCode)) {
                    dispositivos.get(devCode).turnOn();
                }
            }
        }
    }

    /**
     * Liga todos os dispositivos de uma divisão
     * @param div divisão em questão
     */
    public void setDivisaoOn(String div){
        if(this.companhia_eletrica != null) {
            if (this.devices.containsKey(div)) {
                Map<Integer, SmartDevice> divisao = this.devices.get(div);
                for (SmartDevice sd : divisao.values()) {
                    sd.turnOn();
                }
            }
        }
    }

    /**
     * Ligar todos os dispositivos da casa
     */
    public void setHouseOn(){
        System.out.println(this.companhia_eletrica);
        if(this.companhia_eletrica != null) {
            for (String divisao : this.devices.keySet()) {
                setDivisaoOn(divisao);
            }
        }
    }

    /**
     * Desliga dispositivo por id
     * @param devCode id de dispositivo
     */
    public void setDeviceOFF(int devCode) {
        for (Map<Integer, SmartDevice> dispositivos: this.devices.values()){
            if (dispositivos.containsKey(devCode)){
                dispositivos.get(devCode).turnOff();
            }
        }
    }

    /**
     * Desliga todos os dispositivos de determinada divisão
     * @param div divisão em questão
     */
    public void setDivisaoOFF(String div){
        if (this.devices.containsKey(div)){
            Map <Integer, SmartDevice> divisao = this.devices.get(div);
            for (SmartDevice sd:divisao.values()){
                sd.turnOff();
            }
        }
    }

    /**
     * Desliga todos os dispositivos da casa
     */
    public void setHouseOFF(){
        for (String divisao:this.devices.keySet()){
            setDivisaoOFF(divisao);
        }
    }

    /**
     * Verifica se existe dispositivo na casa
     * @param id id do dispositivo
     * @return boolean se existe dispositivo na casa
     */
    public boolean existsDevice(Integer id) {
        for(Map<Integer, SmartDevice> dispositivos:this.devices.values()){
            if (dispositivos.containsKey(id))
                return true;
        }
        return false;
    }

    /**
     * Verifica se dispositivo existe em determinada divisão
     * @param id id a definir
     * @param divisao divisão em questão
     * @return boolean se existe dispositvo em determinada divisão por id
     */
    public boolean existsDevice(Integer id, String divisao) {
        return this.devices.get(divisao).containsKey(id);
    }

    /**
     * Adiciona dispostivo a uma divisão
     * @param divisao divisão a adiconar
     * @param s dispositivo a adicionar
     */
    public void addDevice(String divisao,SmartDevice s) {
        if (this.devices.containsKey(divisao)){
            this.devices.get(divisao).put(s.getID(),s.clone());
        }
        else{//criar a divisao 
            Map<Integer, SmartDevice> disp = new HashMap<>();
            disp.put(s.getID(),s.clone());
            this.devices.put(divisao, disp);
        }
    }

    /**
     * Adiciona dispositivo a divisão pelo id
     * @param divisao divisão a receber o dispositivo
     * @param id do dispositivo a adicionar
     */
    public void addDevice(String divisao,int id) {
        if (this.devices.containsKey(divisao)){
            this.devices.get(divisao).put(id,getDevice(id).clone());
        }
        else{//criar a divisao
            Map<Integer, SmartDevice> disp = new HashMap<>();
            disp.put(id,getDevice(id).clone());
            this.devices.put(divisao, disp);
        }
    }

    /**
     * Gette de dispositivo por id
     * @param s id de dispositvo
     * @return dispositivo
     */
    public SmartDevice getDevice(Integer s) {
        for(Map<Integer, SmartDevice> devices: this.devices.values()){
            if(devices.containsKey(s))
                return devices.get(s).clone();
        }
        return null;
    }

    /**
     * Getter de consumo em uma divisão
     * @param div map de dispositivos de determinada divisão
     * @return consumo
     */
    public double getConsumoDivisao(Map<Integer,SmartDevice> div){
        double consumoDivisao=0;
        for(SmartDevice disp:div.values()){
            consumoDivisao+=disp.getConsumo();
        }
        return consumoDivisao;
    }

    /**
     * Getter de consumo por em uma divisão durante determinado tempo
     * @param div dispositivos de divisão em questão
     * @param data_atual data final de determinado tempo
     * @param data_sim data inicial de determinado tempo
     * @return consumo da divisão
     */
    public double getConsumoDivisao(Map<Integer,SmartDevice> div,LocalDate data_atual, LocalDate data_sim){
        double consumoDivisao=0;
        for(SmartDevice disp:div.values()){
            consumoDivisao+=disp.getConsumo(data_atual, data_sim);
        }
        return consumoDivisao;
    }

    /**
     * Adiciona divisão na casa
     * @param div divisão em questão
     */
    public void addDivisao(String div){
        if (this.devices ==null){
            Map<Integer,SmartDevice> disp = new HashMap<>();
            assert false;
            this.devices.put(div,disp);
        }
        if(!this.devices.containsKey(div)){
            Map<Integer,SmartDevice> disp = new HashMap<>();
            this.devices.put(div,disp);
        }
    }

    /**
     * Remove divisão de uma casa
     * @param div divisão em questão
     */
    public void removeDivisao(String div){
        if( this.devices!=null && this.devices.containsKey(div)){
            this.devices.remove(div);
        }
    }

    /**
     * Procura divisão em uma casa
     * @param div divisão em questão
     * @return boolean se existe ou não divisão
     */
    public boolean hasDivisao(String div){
        return this.devices.containsKey(div);
    }


    /**
     * Getter do consumo em kWs da casa
     * @return consumo em kWs
     */
    public double getConsumoDaCasa(){
        this.consumo = 0;
        for(Map<Integer, SmartDevice> div: this.devices.values())
            this.consumo+=getConsumoDivisao(div);
        return this.consumo;
    }

    /**
     * Getter do consumo da casa em determinado intervalo de tempo
     * @param data_atual data do inicio do intervalo
     * @param data_sim data final
     * @return consumo
     */
    public double getConsumoDaCasa(LocalDate data_atual, LocalDate data_sim){
        this.consumo = 0;
        for(Map<Integer, SmartDevice> div: this.devices.values())
            this.consumo+=getConsumoDivisao(div, data_atual, data_sim);
        return this.consumo;
    }

    /**
     * Clone da casa
     * @return casa clonada
     */
    public SmartHouse clone() throws CloneNotSupportedException {
        return new SmartHouse(this);
    }

    /**
     * toString da casa
     * @return String com todas as informações da casa
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nPROPRIETÁRIO: ");
        sb.append(this.nome_prop);
        sb.append("\tNIF: ");
        sb.append(this.NIF_prop);
        sb.append("\tMORADA: ");
        sb.append(this.morada);
        sb.append("\nCOMERCIALIZADOR DE ENERGIA:\n");
        sb.append(this.companhia_eletrica.toString());
        sb.append("\n");
        sb.append("TOTAL DIVISÕES: ");
        sb.append(this.devices.size());
        sb.append("\nDISPOSITIVOS POR DIVISÃO:\n");
        for(String divisao:this.devices.keySet()){
            sb.append("\n");
            sb.append(divisao);
            sb.append("\n");
            for(SmartDevice sd:this.devices.get(divisao).values()){
                //sb.append("Id do dispositivo: ");
                //sb.append(sd.getID());
                //sb.append("\n");
                sb.append("Consumo do dispositivo: ").append(sd.getConsumo());
                sb.append("\n");
                sb.append(sd);
                sb.append("\n");
            }
        }
        sb.append("\n");
        return sb.toString();
    }

    /**
     * Muda de fornecedor
     * @param novoComercializadoresEnergia novo comercializador
     * @param data_mudanca data em que se muda de fornecedor
     */
    public void mudaDeFornecedor(ComercializadoresEnergia novoComercializadoresEnergia, LocalDate data_mudanca){
        this.companhia_eletrica.terminaContrato(this);//terminar contrato
        this.companhia_eletrica=novoComercializadoresEnergia;
        this.companhia_eletrica.addCasa(this);
    }

    /**
     * Termina contrato com fornecedor
     */
    public void terminaContrato(){
        this.companhia_eletrica.removeCasa(this);
        this.companhia_eletrica=null;
    }

    /**
     * Getter do nome de divisões
     * @return set com o nome de divisões
     */
    public Set<String> getNomeDivisoes(){
        return this.devices.keySet();
    }

    /**
     * Getter do número total de divisões
     * @return número de divisões
     */
    public int getTotalDivisions(){return this.devices.size();}


    /**
     * Getter de lista de dvisiões
     * @return lista de divisões na casa
     */
    public List<String> getDivisaoList(){
        
        List<String> divs_list = new ArrayList<>();
        int index = 0;

        for (Map.Entry<String,Map<Integer, SmartDevice>> devices : devices.entrySet()) {
            divs_list.add(index, devices.getKey());
            index++;
        }

        return divs_list;
    }

    /**
     * Getter de dispositivos por divisão
     * @param divisao divisão onde procurar dispositivos
     * @return Map de dispositvivos
     */
    public Map<Integer,SmartDevice> getDevicesDivisao(String divisao){
        return this.devices.get(divisao);

    }

    /**
     * Getter da divisão por id
     * @param index id da divisão
     * @return divisão
     */
    public String getDivisaoByIndex(int index){return this.getDivisaoList().get(index);}

    public String basicToString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nPROPRIETÁRIO: ");
        sb.append(this.nome_prop);
        sb.append("\tNIF: ");
        sb.append(this.NIF_prop);
        sb.append("\tMORADA: ");
        sb.append(this.morada);
        sb.append("\tCOMERCIALIZADOR DE ENERGIA:");
        sb.append(this.companhia_eletrica.toString());
        sb.append("\tCONSUMO DA CASA:");
        sb.append(getConsumo());
        sb.append("\n");
        return sb.toString();
    }


    @Override
    public int compareTo(SmartHouse casa){
        if (this.consumo<casa.getConsumo())
            return -1;

        else if (this.consumo>casa.getConsumo())
            return 1;
        return 0;
    }


}
