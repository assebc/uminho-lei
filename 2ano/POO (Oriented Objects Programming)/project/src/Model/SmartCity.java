package Model;

import java.time.LocalDate;
import java.util.*;

import Controller.Controller;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.lang.StringBuilder;
import java.io.*;

import static java.time.temporal.ChronoUnit.DAYS;

public class SmartCity implements Serializable{

    @Serial
    private static final long serialVersionUID = 1732799934;
    private Map<Integer,SmartHouse> casas=new HashMap<>();
    private List<ComercializadoresEnergia> comercializadores=new ArrayList<>();
    private List<Marca> marcas = new ArrayList<>(); 
    private Map<String,SmartDevice> presets= new HashMap<>();
    private int houseID=0; //diz quantas casas tem na cidade e atribui o seu numero
    private int deviceID=0; //diz quantos devices tem na cidade e atribui o seu numero
    private LocalDate data_atual;

    /**
     * Inicializador de uma cidade
     */
    public SmartCity(){
        this.data_atual = LocalDate.now();
        this.deviceID = 0;
        this.houseID = 0;
        this.comercializadores=new ArrayList<>();
        this.marcas = new ArrayList<>();
        this.presets=new HashMap<>();
        this.casas = new HashMap<>();
    }

    /**
     * Duplicação de uma cidade através (proveniente do estado)
     * @param state cidade para ser duplicada
     */
    public SmartCity(SmartCity state){
        this.data_atual = state.getDataAtual();
        this.deviceID = state.getDeviceId();
        this.houseID = state.getHouseId();
        this.comercializadores= state.getComercializadores();
        this.marcas = state.getMarcas();
        this.presets= state.getPresets();
        this.casas = state.getCasas();
    }

    /**
     * Função responsável pela aprte da simulação
     * @param time Data definida na simulação
     * @return inteiros
     */
    public int simulation(String time){

        String [] data = time.split("\\.", 3);  //separa a data dada
        int no_days = 0;
        LocalDate data_sim;
        double consumo_tmp;

        switch (data.length) {
            case 1 -> { //apenas dado um dia
                no_days = Integer.parseInt(data[0]);
                data_sim = LocalDate.now().plus(no_days,DAYS);
            }
            case 3 -> { //dada uma data em formato DD.MM.YYYY
                Controller p = new Controller(this);
                data_sim = p.parseData(time);
                if(data_sim.isBefore(this.data_atual)) return 1; //data anterior portanto inválida
            }
            default -> {
                //Data inválida
                return 1;
            }
        }
        System.out.println("\nDATA: "+data_sim.toString());
        //calcula consumos no intervalo de datas da data atual à data da simulação
        for (SmartHouse casa : this.casas.values()){
            consumo_tmp = casa.getConsumoDaCasa(this.data_atual, data_sim);
            System.out.println("\nCONSUMO CASA No."+ casa.getID() +": " + consumo_tmp);
        }
        /*
         percorre comercializadores para tirarem faturas
         guarda as faturas no seu map e manda para as casas guardarem
         */
        for (ComercializadoresEnergia comercializadore : this.comercializadores) {
            comercializadore.faturacao(data_sim);
        }
        this.data_atual = data_sim;
        return 0;
    }


    /**
     * Merge de duas cidades
     * @param toMergeo cidade para dar merge
     */
    public void merge(Object toMergeo){
        SmartCity toMerge = (SmartCity) toMergeo;
        for(Integer id: toMerge.getCasas().keySet()){
            if(!casas.containsKey(id)){
                this.casas.put(id,toMerge.getCasa(id));
                //this.deviceID+=toMerge.getCasa(id).size();  incrementar o smartId;
            }
        }

        for (ComercializadoresEnergia temp : toMerge.getComercializadores()) {
            if (!this.comercializadores.contains(temp))
                this.comercializadores.add(temp);
        }

        for (Marca temp : toMerge.getMarcas()) {
            if (!this.marcas.contains(temp))
                this.marcas.add(temp);
        }

        for(String id: toMerge.getPresets().keySet()){
            if(!presets.containsKey(id)){
                this.presets.put(id,toMerge.getPreset(id));
            }
        }

        this.houseID=this.casas.size()+1; //passa para o id seguinte


    }

    /**
     * Getter de marca
     * @param nome nome da marca a procurar
     * @return marca em questão ou null
     */
    public Marca getMarca(String nome){
        for(Marca x : this.marcas){
            if(x.getNome().equals(nome)){return x;}
        }
        return null;
    }

    /**
     * Getter dos presets de dispositivos
     * @return Map dos presets de dispositivos
     */
    public Map<String, SmartDevice> getPresets(){return this.presets;}

    /**
     * Getter das marcas
     * @return lista de marcas de uma cidade
     */
    public List<Marca> getMarcas(){return this.marcas;}

    /**
     * Trocar o tipo de marcas de lista para string
     * @return String das marcas
     */
    public String marcasListToString(){
        StringBuffer sb = new StringBuffer();
        for(Marca x : this.marcas){
            sb.append(x.toString());
        }
        return sb.toString();
    }

    /**
     * Salvar estado de uma cidade
     * @param nameOfFile nome do ficheiro onde guardar o estado
     * @throws IOException Exception se ão for encontrado tal ficheiro
     */
    public void saveState(String nameOfFile) throws IOException {
        try{
            FileOutputStream fos = new FileOutputStream(nameOfFile);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(this);
            oos.flush();
            oos.close();
        }
        catch(FileNotFoundException e){
            System.out.println("File not found! "+e);
        }
    }

    /**
     * Carregar estado pré-gravado de uma cidade
     * @param nameOfFile nome do ficheiro com o estado de uma cidade
     * @return Cidade redefinida
     * @throws IOException Exception se não encontrar ficheiro
     * @throws ClassNotFoundException Exception se ocorrerem problemas a ler strings do ficheiro estado.object
     */
    public SmartCity loadState(String nameOfFile) throws IOException, ClassNotFoundException{
        FileInputStream fis = new FileInputStream(nameOfFile);
        ObjectInputStream oos = new ObjectInputStream(fis);
        SmartCity cit =(SmartCity) oos.readObject();
        oos.close();
        return cit;
    }

    /**
     * Inicializador de uma cidade
     * @param houseID id da casa
     * @param deviceID id de dispositivo
     */
    public SmartCity(int houseID, int deviceID){
        this.deviceID = deviceID;
        this.houseID = houseID;
    }

    /**
     * Getter de data atual
     * @return Data atural
     */
    public LocalDate getDataAtual(){return this.data_atual;}

    /**
     * Getter do id da casa
     * @return id da casa
     */
    public int getHouseId(){return this.houseID;}

    /**
     * Getter do id do dispositivo
     * @return id do dispositivo
     */
    public int getDeviceId(){return this.deviceID;}

    public SmartDevice getDevice(int id){
        for(SmartHouse casas:this.casas.values()){
            if(casas.existsDevice(id)) return casas.getDevice(id);
        }
        return null;
    }

    /**
     * Setter para o id de um dispositivo
     * @return id incrementado de um dispositivo
     */
    public int giveDeviceId(){return ++(this.deviceID);} //serve para dar o id e aumentar o numero de devices

    /**
     * Setter para o id de uma casa
     * @return id incrementado de uma casa
     */
    public int giveHouseId(){return ++(this.houseID);} //serve para dar o id e aumentar o numero de casas

    /**
     * Getter de preset's de dispositivos
     * @param preset String de presets de dispositvos
     * @return preset de dispositvo
     */
    public SmartDevice getPreset(String preset){
        return presets.get(preset);
    }

    /**
     * Getter de casas
     * @return map de casas em uma cidade
     */
    public Map<Integer,SmartHouse> getCasas(){return this.casas;}

    /**
     * Procura comercializador por id
     * @param id id em procura
     * @return boolean se existe ou não comercializador por id na cidade
     */
    public boolean hasComercializador(String id){
        return this.comercializadores.stream().anyMatch(c->c.getNome().equals(id));
    }

    /**
     * Lista em string fornecedores de uma cidade
     * @return String de fornecedores
     */
    public String listComercializadores(){
        List<ComercializadoresEnergia> comercializadoresDaCidade = this.comercializadores;
        StringBuilder sb = new StringBuilder();
        ListIterator<ComercializadoresEnergia> iter = comercializadoresDaCidade.listIterator();
        sb.append("[");
        int pos =0;
        while(iter.hasNext()){
            ComercializadoresEnergia temp = iter.next();
            sb.append(temp.getNome());
            sb.append("     Preço p/KWh: ");
            sb.append(temp.getPrecoBaseKW());
            if(pos<this.comercializadores.size()-1){
                sb.append(",  ");
            }
            pos+=1;
        }
        sb.append("]");
        return sb.toString();

    }


    /**
     * Getter de comercializadores
     * @return lista de comercializadores
     */
    public SmartHouse getCasaMaisGastadora(String time){
        SmartHouse ret=null;
        try{
            for (ComercializadoresEnergia comer: this.comercializadores){
                if (!comer.hasFaturado())
                    comer.faturacao(time); 
                SmartHouse temp = comer.getCasaMaisGastadora();
                if (ret == null || temp.getConsumo()>ret.getConsumo()){
                    ret = temp;
                }
            }
            return ret;
        }
        catch(Exception e){
            System.out.println("Deu asneira a ir buscar a casa mais gastadora");
        }
        return ret;
    }

    public List<SmartHouse> getCasasMaisGastadoras(String time){
        ArrayList<SmartHouse> casas = new ArrayList<>();
        try{
            for (ComercializadoresEnergia comer: this.comercializadores){
                if (!comer.hasFaturado())
                    comer.faturacao(time); 
                SmartHouse temp = comer.getCasaMaisGastadora();
                casas.add(temp);
            }
            Collections.sort(casas, Collections.reverseOrder());

            return casas;
        }
        catch(Exception e){
            System.out.println("Deu asneira a ir buscar a casa mais gastadora");
        }
        Collections.sort(casas);
        return casas;
    }

    /**
     * Getter da casa mais gastadora entre determinadas datas
     * @param dataInit data de inicio
     * @param dataFin data final
     * @return casa
     */
    public SmartHouse getCasaMaisGastadora(LocalDate dataInit, LocalDate dataFin){
        SmartHouse ret=null;
        for (ComercializadoresEnergia comer: this.comercializadores){
            if(!comer.hasFaturado()){
                comer.faturacao(dataFin);
            }
            SmartHouse temp = comer.getCasaMaisGastadora(dataInit, dataFin);
            if (ret == null || temp.getConsumo()>ret.getConsumo()){
                ret = temp;
            }
        }
        return ret;
    }
    public ComercializadoresEnergia getComercializadorMaiorFaturacao(){
        ComercializadoresEnergia ret=null;
        for (ComercializadoresEnergia comer: this.comercializadores){
            if (ret == null || comer.getFaturacao()>ret.getFaturacao()){
                ret = comer;
            }
        }
        return ret;
    }

    public List<ComercializadoresEnergia> getComercializadores(){return this.comercializadores;}


    /**
     * Criar comercializador em uma cidade
     * @param nome Nome do comercializador a adicionar à cidade
     */
    public void createComercializadorEnergia(String nome){
        ComercializadoresEnergia com = new ComercializadoresEnergia(nome);
        createComercializadorEnergia(com);
    }

    /**
     * Criar comercializador em uma cidade
     * @param nome Nome do fornecedor a adicionar
     * @param preco Preço base do comercializador
     * @param imposto Imposto do comercializor
     */
    public void createComercializadorEnergia(String nome, double preco, double imposto){ 
        ComercializadoresEnergia com = new ComercializadoresEnergia(nome, preco, imposto);
        createComercializadorEnergia(com);
    }

    /**
     * Adicionar comercializador em uma cidade com base em um comercializador previamente existente
     * @param com Comercializador a adicionar
     */
    public void createComercializadorEnergia(ComercializadoresEnergia com){
        this.comercializadores.add(com);
    }

    /**
     * Muda de fornecedor
     * @param id id da casa
     * @param novo novo comercializador
     * @param data_mudanca data em que se muda de fornecedor
     */
    public void mudaDeFornecedorString(int id, String novo, LocalDate data_mudanca){
        SmartHouse casa = getCasa(id);
        casa.mudaDeFornecedor(getComercializador(novo),data_mudanca);
    }

    /**
     * Getter de uma casa
     * @param id id da casa
     * @return Casa com determinado id
     */
    public SmartHouse getCasa(int id){
        return this.casas.get(id);
    }

    /**
     * Criar casa em uma cidade
     * @param nome nome do proprietário da casa
     * @param nif nif do proprietário da casa
     * @param morada morada da casa
     * @param comercializadorDeEnergia fornecedor da casa
     * @return id da casa
     */
    public int createHouse(String nome, int nif, String morada, String comercializadorDeEnergia){
        int id = this.houseID;
        
        if (getComercializador(comercializadorDeEnergia)==null){
            createComercializadorEnergia(comercializadorDeEnergia);
            SmartHouse house = new SmartHouse(id,nome,nif,morada,getComercializador(comercializadorDeEnergia));
            createHouse(house);
            //getComercializador(comercializadorDeEnergia).addCasa(house);
        }else{
            ComercializadoresEnergia comer = getComercializador(comercializadorDeEnergia);
            //createComercializadorEnergia(comer);
            SmartHouse house = new SmartHouse(id,nome,nif,morada,comer);
            createHouse(house);
            comer.addCasa(house);
        }
        
        return id;
    }

    /**
     * Definir casa em uma cidade
     * @param house casa a definir
     */
    public void createHouse(SmartHouse house){
        this.casas.put(this.houseID,house);
        this.houseID++;
    }

    /**
     * Cria uma divisão
     * @param divisao divisão a criar
     */
    public void criaDivisao(String divisao){
        SmartHouse temp = getCasa(this.houseID-1);
        //System.out.println(temp==null);
        if(temp!=null){
            temp.addDivisao(divisao);
        }
    }

    /**
     * Cria uma divisão numa determinada casa
     * @param houseID id da casa
     * @param divisao divisão a adicionar na casa
     */
    public void criaDivisao(int houseID, String divisao){
        SmartHouse temp = getCasa(houseID);
        if(temp!=null){
            temp.addDivisao(divisao);
        }
    }

    /**
     * Função que procura uma divisão numa casa atrásves do id
     * @param id id da casa
     * @param divisao divisão em questão
     * @return divisao
     */
    public String getCasaDivisao(int id, String divisao){
        if(getCasa(id).hasDivisao(divisao)) return divisao ;
        else return null;
    }

    /**
     * Adicionar dispositivo em uma divisão
     * @param house_id id da casa
     * @param divisao divisão a receber o dispositivo
     * @param sd dispositivo a adicionar
     */
    public void addDeviceToDivisao(int house_id, String divisao, SmartDevice sd){
        if(getCasa(houseID)!=null){
            getCasa(houseID).addDevice(divisao, sd);
        }
    }

    /**
     * Adicionar dispositivo em uma divisão
     * @param house_id id da casa
     * @param divisao divisão a receber o dispositivo
     * @param sd dispositivo a adicionar por id
     */
    public void addDeviceToDivisao(int house_id, String divisao, int sd){
        if(getCasa(house_id)!=null){
            getCasa(house_id).addDevice(divisao, sd);
        }
    }

    /**
     * Adicionar lampada a uma divisão~
     * @param house_id id da casa
     * @param divisao divisão a receber a lampada
     * @param id id da lampada
     * @param mode modo da lampada
     * @param dimensions dimensão da lampada
     * @param consumo consumo da lampada
     */
    public void addDeviceToDivisaoL(int house_id, String divisao, int id, String mode , int dimensions, double consumo, String estado){
        SmartDevice sd = new SmartBulb(id,mode,dimensions,consumo, estado);
        getCasa(house_id-1).addDevice(divisao, sd);
    }

    /**
     * Adicionar camara a divisão
     * @param house_id id da casa
     * @param divisao divisão a receber a camara
     * @param id id a definir
     * @param width comprimento da resolução a definir
     * @param height largura da resolução a definir
     * @param consumo consumo a definir
     */
    public void addDeviceToDivisaoC(int house_id, String divisao, int id, float width , float height, int tamanho, double consumo, String estado){
        SmartDevice sc = new SmartCamera(id,width,height,tamanho,consumo, estado);
        getCasa(house_id-1).addDevice(divisao, sc);
    }

    /**
     * Adicionar coluna a divisão
     * @param house_id id da casa
     * @param divisao divisão a adicionar
     * @param id id a definir
     * @param vol volume a definir
     * @param estacao estação a definir
     * @param marca marca da coluna
     * @param consumo consumo a definir
     */
    public void addDeviceToDivisaoS(int house_id, String divisao, int id, int vol, String estacao , String marca, double consumo, String estado){
        SmartSpeaker sb;
        if(getMarca(marca)==null) { createMarca(marca); sb = new SmartSpeaker(id,vol,estacao,getMarca(marca),consumo);}
        else sb = new SmartSpeaker(id,vol,estacao,estado, getMarca(marca),consumo);
        SmartDevice sd = (SmartDevice) sb;
        getCasa(house_id-1).addDevice(divisao, sd); //FIX:fixed
    }

    /**
     * Adicionar dispositivo em divisão
     * @param divisao divisão a definir
     * @param preset preset do dispositivo a adicionar
     */
    public void addDeviceToDivisao(String divisao, String preset){
        int houseID = this.houseID-1;
        SmartHouse temp = getCasa(houseID);
        if(temp!=null){
            if(!temp.hasDivisao(divisao)){
                temp.addDevice(divisao, getPreset(preset));
            }
        }
    }


    /**
     * Criar marca em uma cidade
     * @param nome nome a definir
     * @param consumo consumo a definir
     */
    public Marca createMarca(String nome, double consumo){
        if(getMarca(nome) == null){
            createMarca(new Marca(nome, consumo));
        }
        return getMarca(nome);
    }


    /**
     * Criar marca
     * @param nome nome a definir
     */
    public Marca createMarca(String nome){
        if(getMarca(nome) == null){
            createMarca(new Marca(nome));
        }
        return getMarca(nome);
    }

    /**
     * Criar marca
     * @param marca marca a adicionar numa cidade com base a uma marca pré-criada
     */
    public void createMarca(Marca marca){
        if(getMarca(marca.getNome()) == null){
            this.marcas.add(marca);
        }
    }

    /**
     * Adicionar preset de dispositivo
     * @param nome nome do presety
     * @param device smartdevice a definir o preset
     */
    public void addDevicePreset(String nome, SmartDevice device){
        if(getPreset(nome) == null){
            this.presets.put(nome,device);
        }
    }

    /**
     * Adicionar preset de dispositivo
     * @param nome nome do presety
     * @param device id do smartdevice a definir o preset
     */
    public void addDevicePreset(String nome, int device){
        if(getPreset(nome) == null){
            this.presets.put(nome,getDevice(device));
        }
    }

    /**
     * Listar faturas numa string
     * @return string das faturas
     */
    public String listFaturas(){
        List<String> listaDeFaturas = new ArrayList<>();
        for (ComercializadoresEnergia temp : this.comercializadores) {
            listaDeFaturas.add(temp.getNome());
            listaDeFaturas.add(temp.getListaFaturacao());
        }
        return listaDeFaturas.toString();
    }

    /**
     * Listar faturas de determinado fornecedor numa string
     * @param nomeComercializador nome do comercializador pretendido
     * @return string com a lista de faturas de um fornecedor
     */
    public String listFaturas(String nomeComercializador){
        return getComercializador(nomeComercializador).getListaFaturacao().toString();
    }

    /**
     * Getter de determinado comercializor
     * @param nomeComercializador nome do comercializador
     * @return Comercializador pretendido ou null
     */
    public ComercializadoresEnergia getComercializador(String nomeComercializador){
        for (ComercializadoresEnergia comer:this.comercializadores){
            if (comer.getNome().equals(nomeComercializador)){
                return comer;
            }
        }
        return null;
    }

    /**
     * Lista de presets de dispositivos
     */
    public void listSmartDevicesPresets(){
        StringBuilder sb = new StringBuilder();
        for(String name : this.presets.keySet()){
            sb.append("\nNome do preset: ");
            sb.append(name);
            sb.append("\n");
            sb.append(this.presets.get(name).toString());
        }
        System.out.println(sb);
    }

    /**
     * Lista de marcas existentes
     */
    public void listMarcas(){
        System.out.println(this.marcasListToString());
    }

    /**
     * Lista de casas na cidade
     */
    public void listSmartHouses(){
        StringBuilder sb = new StringBuilder();
        for(SmartHouse casa: this.casas.values()){
            sb.append(casa.toString());
        }
        System.out.println(sb);
    }

    /**
     * Procura casa em uma cidade através do seu id
     * @param id id da casa
     * @return boolean se existe casa em cidade
     */
    public boolean hasSmartHouse(int id){
        return this.casas.containsKey(id);
    }


    /**
     * Desliga dispositvos de uma casa através do id
     * @param id id da casa
     */
    public void setHouseOFF(int id){
        getCasa(id).setHouseOFF();
    }

    /**
     * Desliga dispositivos de uma divisão através do id
     * @param id id da casa
     * @param divisao divisao da casa
     */
    public void setCasaDivisaoOFF(int id, String divisao){
        getCasa(id).setDivisaoOFF(divisao);
    }

    /**
     * Liga dispositvos de uma casa através do id
     * @param id id da casa
     */
    public void setHouseOn(int id){
        getCasa(id).setHouseOn();
    }


    /**
     * Liga dispositivos de uma divisão através do id
     * @param id id da casa
     * @param divisao divisao da casa
     */
    public void setCasaDivisaoOn(int id, String divisao){
        getCasa(id).setDivisaoOn(divisao);
    }

    /**
     * toString da cidade
     * @return String com todos os componentes de uma cidade
     */
    public String toString(){
        StringBuilder bd = new StringBuilder();
        bd.append("\nCASAS:\n");
        bd.append(this.casas.toString());
        bd.append("\nCOMERCIALIZADORES:\n");
        bd.append(this.comercializadores.toString());
        bd.append("\nMARCAS:\n");
        bd.append(this.marcas.toString());
        bd.append("\nPRESETS:\n");
        bd.append(this.presets.toString());
        bd.append("\n");
        return bd.toString();
    }


}
