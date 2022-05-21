package Controller;

import Model.Marca;
import Model.SmartBulb;
import Model.SmartCamera;
import Model.SmartCity;
import Model.SmartDevice;
import Model.SmartHouse;
import Model.SmartSpeaker;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.ObjectInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.AccessDeniedException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public class Controller {
    private SmartCity city;

    public Controller(){ this.city = new SmartCity(); }
    /**
     * Inicializador do Controller
     * @param city Cidade a ser inicializada
     */
    public Controller(SmartCity city){
        this.city = city;
    }


    /**
     * Getter da cidade
     * @return Cidade
     */
    public SmartCity getCity(){
        return this.city;
    }

    /**
     * Salvar estado da cidade
     * @param name_path path do ficheiro
     * @throws IOException Exception de não encontrar o caminho
     */
    public void saveState(String name_path) throws IOException {
        this.city.saveState(name_path);
    }

    /**
     * Ler ficheiro object
     * @param filepath String de caminho para ler ficheiro
     */
    public Object ReadObjectFromFile(String filepath) {

        try {

            FileInputStream fileIn = new FileInputStream(filepath);
            ObjectInputStream objectIn = new ObjectInputStream(fileIn);

            Object obj = objectIn.readObject();

            System.out.println("Estado carregado com sucesso!");
            objectIn.close();
            return obj;

        } catch (Exception ex) {
            ex.printStackTrace();
            return null;
        }
    }

    /**
     * Função que dá merge a cidades
     * @param path Cidade a dar merge
     */
    public void merge(String path) throws FileNotFoundException {
 
        SmartCity city = (SmartCity)ReadObjectFromFile(path);
        this.city.merge(city);
    }

    /**
     * Função que procura a data atual na cidade
     * @return Data atual
     */
    public LocalDate getDataAtual(){
        return this.city.getDataAtual();
    }


    public void alteraConsumoDiario(String marca, String novoConsumo){
        this.city.getMarca(marca).setConsumoDiario(Double.parseDouble(novoConsumo));
    }

    /**
     * Função que cria fornecedor de energia
     * @param nome nome do fornecedor
     * @param preco preço base
     * @param imposto imposto
     */
    public void createComercializadorEnergia(String nome, double preco, double imposto){
        this.city.createComercializadorEnergia(nome,preco,imposto);
    }

    /**
     * Verifica se um dado comercializador existe na cidade
     * @param nome do comercializador a procurar
     * @return Bool a indicar se existe ou não
     */
    public boolean existsComercializador(String nome){
        return this.city.getComercializador(nome) == null;
    }

    /**
     * Getter do comercializador
     * @param id id da casa
     * @return String do comercializador
     */
    public String getComercializadoratual(int id){
        return this.city.getCasa(id).getCompanhia_eletrica().toString();
    }

    /**
     * Getter do comercializador do preço base
     * @param nome nome do comercializador
     * @return preço base
     */
    public double getComercializadorPrecoBaseKW(String nome){
        return this.city.getComercializador(nome).getPrecoBaseKW();
    }
    
    /**
     * Setter do comercializador do preço base
     * @param nome nome do comercializador
     * @param precobase preço a modificar
     */
    public void setComercializadorPrecoBaseKW(String nome,double precobase){
        this.city.getComercializador(nome).setPrecoBaseKW(precobase);
    }

    /**
     * Setter do comercializador do fator imposto
     * @param nome nome do comercializador
     * @param fator fator imposto a modificar
     */
    public void setComercializadorFatorImposto(String nome,double fator){
        this.city.getComercializador(nome).setFatorImposto(fator);
    }
    
    /**
     * Getter do comercializador do fator imposto
     * @param nome nome do comercializador
     * @return fator imposto
     */
    public double getComercializadorFatorImposto(String nome){

        return this.city.getComercializador(nome).getFatorImposto();
    }

    /**
     * Muda o Fornecedor de uma casa
     * @param id id da casa
     * @param nome nome do fornecedor
     * @param data Data atual
     */
    public void mudaDeFornecedorString(int id, String nome, LocalDate data){
        this.city.mudaDeFornecedorString(id, nome, data);
    }

    /**
     * Função que verifica se existe fornecedor na cidade
     * @param comercializador nome do comercializador
     * @return boolean
     */
    public boolean hasComercializador(String comercializador){
        return this.city.hasComercializador(comercializador);
    }

    /**
     * Função que lista comercializadores
     * @return String da lista de comercializadores
     */
    public String listComercializadores(){
        return this.city.listComercializadores();
    }

    /**
     * Faturação
     * @param comercializador nome do comercializador
     * @param time data em string
     */
    public void ComercializadorFaturacao(String comercializador,String time){
        this.city.getComercializador(comercializador).faturacao(time);
    }

    /**
     * Getter de lista de faturação de um comercializador
     * @param comercializador noem do comercializador
     * @return Lista de faturação em string
     */
    public String getListaFaturacaoComercializador(String comercializador){
        return this.city.getComercializador(comercializador).getListaFaturacao();
    }

    /**
     * Getter do comercializador com maior faturação
     * @return comercializador
     */
    public String getComercializadorMaiorFaturacao(){
        return this.city.getComercializadorMaiorFaturacao().toString();
    }

    /**
     * Getter do nome do comercializador com maior faturação
     * @return nome do comercializador
     */
    public String getComercializadorMaiorFaturacaoNome(){
        return this.city.getComercializadorMaiorFaturacao().getNome();
    }


    /**
     * Função que cria marca
     * @param nome nome da marca
     * @param consumo consumo
     */
    public void createMarca(String nome, double consumo){
        this.city.createMarca(nome,consumo);
    }
    /**
     * Getter de marca pelo nome
     * @param nome Nome da marca
     * @return Marca
     */
    public Marca getMarca(String nome){
        return this.city.getMarca(nome);
    }

    /**
     * Função que transforma a lista de marca em string
     * @return String de marcas
     */
    public String marcasListToString(){
        return this.city.marcasListToString();
    }

    /**
     * Função que lista as marcas
     */
    public void listMarcas(){
        this.city.listMarcas();
    }

    /**
     * Função que cria casa na cidade
     * @param nome_prop Nome do proprietário
     * @param nif NIF do proprietário
     * @param morada Morada da casa
     * @param fornecedor Fornecedor da casa
     * @return id da casa
     */
    public int createHouse(String nome_prop, int nif, String morada, String fornecedor){
        return this.city.createHouse(nome_prop, nif, morada, fornecedor);
    }

    public SmartHouse getCasa(int id){
        return this.city.getCasa(id);
    }

    public SmartHouse getCasaMaisGastadora(String time){return this.city.getCasaMaisGastadora(time);}


/**
     * Getter id da casa atual
     * @return id da casa
     */
    public int getHouseId(){return this.city.getHouseId();}

    public int getCasaMaisGastadora(LocalDate a, LocalDate b){
        SmartHouse casa = this.city.getCasaMaisGastadora(a,b);
        return casa.getID();
    }

    public List<SmartHouse> getCasasMaisGastadoras(String time){
        return this.city.getCasasMaisGastadoras(time);
    }

    /**
     * Getter do id da casa mais gastadora
     * @return id da casa
     */
    public int getCasaMaisGastadoraID(){
        return this.city.getCasaMaisGastadora(null).getID();
    }

    /**
     * Getter do id da casa mais gastadora
     * @return id da casa
     */
    public double getCasaMaisGastadoraConsumo(){
        return this.city.getCasaMaisGastadora(null).getConsumoDaCasa();
    }

    /**
     * Getter de casa mais gastadora
     * @return Casa mais gastadora
     */
    public String getCasaMaisGastadora(){
        return this.city.getCasaMaisGastadora(null).toString();
    }

    /**
     * Lista de casas
     */
    public void listSmartHouses(){
        this.city.listSmartHouses();
    }

    /**
     * Função que cria divisões
     * @param nome_divisao Nome da divisão
     */
    public void criaDivisao(String nome_divisao){
        this.city.criaDivisao(nome_divisao);
    }

    /**
     * Função que cria divisão em uma casa
     * @param id id da casa
     * @param nome_divisao Nome da divisão
     */
    public void criaDivisaoCasa(int id, String nome_divisao){
        this.city.getCasa(id).addDivisao(nome_divisao);
    }

    /**
     * Função que remove divisão em uma casa
     * @param id id da casa
     * @param nome_divisao Nome da divisão
     */
    public void removeDivisaoCasa(int id, String nome_divisao){
        this.city.getCasa(id).removeDivisao(nome_divisao);
    }

    /**
     * Adiciona dispositivo a divisão
     * @param house_id id da casa
     * @param divisao divisão emq uestão
     * @param sd dispositivo a adicionar
     */
    public void addDeviceToDivisao(int house_id, String divisao, SmartDevice sd){
        this.city.addDeviceToDivisao(this.city.getHouseId(),divisao,sd);
    }

    /**
     * Adiciona lampada a divisao
     * @param house_id id da casa
     * @param divisao divisão em questão
     * @param modo modo da lampada
     * @param dimensions dimensões da lampada
     * @param consumo consumo da lampada
     * @param estado estado da lampada
     */
    public void addSmartBulbToDivisao(int house_id,String divisao, String modo,  int dimensions, double consumo, String estado){
        this.city.addDeviceToDivisaoL(house_id, divisao, this.city.getDeviceId(),modo , dimensions,consumo);
    }
    
    /** 
     * Adiciona camara a divisao
     * @param house_id id da casa
     * @param divisao nome divisão
     * @param width comprimeito da resolução
     * @param heigth largura da resolução
     * @param tamanho tamanho
     * @param consumo consumo
     * @param estado estado
     */
    public void addSmartCameraToDivisao(int house_id,String divisao, float width,  float heigth, int tamanho, double consumo, String estado){
        this.city.addDeviceToDivisaoC(house_id, divisao, this.city.getDeviceId(),width , heigth,tamanho, consumo);
    }
    
    /** 
     * Adiciona coluna a uma divisão
     * @param house_id id da casa
     * @param divisao nome divisão
     * @param nome_marca nome da marca
     * @param estacao estação
     * @param volume volume
     * @param consumo consumo
     * @param estado estado
     */
    public void addSmartSpeakerToDivisao(int house_id,String divisao, String nome_marca,  double consumo, String estacao, int volume, String estado){
        this.city.addDeviceToDivisaoS(house_id, divisao, this.city.getDeviceId(), volume, estacao, nome_marca, consumo, estado);
    }


    /**
     * Função que adiciona preset de dispositivo a uma divisão de uma casa
     * @param id id da casa
     * @param divisao nome da divisão
     * @param preset preset de dispositivo
     */
    public void addDeviceToDivisao(int id, String divisao, String preset){
        this.city.getCasa(id).addDevice(divisao,this.city.getPreset(preset));
    }

    /**
     * Função que obtem o nome das divisões de uma casa
     * @param id id da casa
     * @return Set do nome das divisões
     */
    public Set<String> getHouseDivisoes(int id){
        return this.city.getCasa(id).getNomeDivisoes();
    }
    public void addDevicePreset(String nome,SmartDevice id){
        this.city.addDevicePreset(nome,id);
    }

    /**
     * Lista preset de dispositivos
     */
    public void listSmartDevicesPresets(){
        this.city.listSmartDevicesPresets();
    }

    /**
     * Liga dispositvos de uma casa através do id
     * @param id id da casa
     */
    public void setHouseOn(int id){ this.city.setHouseOn(id);}


    /**
     * Liga dispositivos de uma divisão através do id
     * @param id id da casa
     * @param divisao divisao da casa
     */
    public void setCasaDivisaoOn(int id, String divisao){
        this.city.setCasaDivisaoOn(id,divisao);
    }


    /**
     * Desliga dispositvos de uma casa através do id
     * @param id id da casa
     */
    public void setHouseOFF(int id){ this.city.setHouseOFF(id); }

    /**
     * Desliga dispositvos de uma divisão através do id
     * @param id id da casa
     * @param divisao divisao da casa
     */
    public void setCasaDivisaoOFF(int id, String divisao){
        this.city.setCasaDivisaoOFF(id,divisao);
    }

    /**
     * Função que procura uma divisão numa casa atrásves do id
     * @param id id da casa
     * @param divisao divisão em questão
     * @return divisao
     */
    public String getCasaDivisao(int id, String divisao){
        return this.city.getCasaDivisao(id,divisao);
    }

    /**
     * Dá um id a um dispositivo
     */
    public int giveDeviceId(){
        return this.city.giveDeviceId();
    }
    
    /**
     * Função que lê todas as linhas de um fichero
     * @param nomeFich nome do fichero
     * @return retorna uma Lista de Strings com todas as linhas do ficheiro
     */
    public List<String> readFile(String nomeFich) {
        try {
            return Files.readAllLines(Paths.get(nomeFich), StandardCharsets.UTF_8);

        }
        catch(IOException exc) {
            return new ArrayList<>();
        }

    }

    public void addSmartSpeakerPreset(String nome_preset, String nome_marca, double consumo, String estacao, int volume, String estado){
        SmartDevice sp = new SmartSpeaker(this.city.giveDeviceId(),volume,estacao,estado,this.city.getMarca(nome_marca),consumo);  //O COntroller por criar devices?
        this.city.addDevicePreset(nome_preset, sp);
    }

    public void addSmartCameraPreset(String nome_preset, float width, float height, int tamanho, String estado){
        SmartDevice sc = new SmartCamera(this.city.giveDeviceId(), width,height,tamanho,estado);
        this.city.addDevicePreset(nome_preset, sc);
    }

    public void addSmartBulbPreset(String nome_preset,  String mode,int dimensions, double consumo){
        SmartDevice sc = new SmartBulb(this.city.giveDeviceId(), mode,dimensions,consumo);
        this.city.addDevicePreset(nome_preset, sc);
    }

    /**
     * Função que dá parse às logs dadas em ficheiro
     */
    public void parse(String nameOfFile) throws IOException{
        try{
            if (!nameOfFile.contains(".txt"))
                nameOfFile=nameOfFile+".txt";
            Path path = Path.of("./logs/"+nameOfFile);
            //Path path = FileSystems.getDefault().getPath("logs", "logs.txt");
            String content = Files.readString(path);
            String[] contentSplited = content.split("\n");
            String[] linhaPartida;
            String divisao = "";
    
            for (String linha : contentSplited) {
    
                linhaPartida = linha.split(":", 2);
    
                switch (linhaPartida[0]) {
                    case "Casa" -> parseCasa(linhaPartida[1]);
                    case "Divisao" -> {
                        divisao = linhaPartida[1];
                        this.city.criaDivisao(divisao);
                    }
                    case "SmartBulb" -> {
                        if (divisao == null) System.out.println("Linha inválida.");
                        parseSmartBulb(divisao, linhaPartida[1]);
                    }
                    case "SmartCamera" -> {
                         if (divisao == null) System.out.println("Linha inválida.");
                         parseSmartCamera(divisao, linhaPartida[1]);
                    }
                    case "SmartSpeaker" -> {
                        if (divisao == null) System.out.println("Linha inválida.");
                        parseSmartSpeaker(divisao, linhaPartida[1]);
                       
                    }
                    case "Fornecedor" -> parseComercializadoresEnergia(linhaPartida[1]);
                    case "Marca" -> parseMarca(linhaPartida[1]);
                }
            }
            System.out.println("Ficheiro carregado com sucesso.");
        }
        catch(Exception e){
            System.out.println("Ocorreu um erro a carregar o ficheiro.");
        }
      
    }

    /**
     * Função que dá parse às casas em uma SmartCity
     * @param input String atual a ser lida das logs
     */
    public void parseCasa(String input){
        String[] campos = input.split(",");
        String nome = campos[0];
        int nif = Integer.parseInt(campos[1]);
        String fornecedor = campos[2];
        this.city.createHouse(nome, nif, "", fornecedor);
    }

    /**
     * Função que dá parse às lampadas em uma SmartCity
     * @param divisao Divisao em que o dispositivo vai ser adicionado
     * @param input String atual a ser lida das logs
     */
    public void parseSmartBulb(String divisao,String input){
        String[] campos = input.split(",");
        String mode = campos[0];
        int dimensions = Integer.parseInt(campos[1]);
        double consumo = Double.parseDouble(campos[2]);
        this.city.addDeviceToDivisaoL(city.getHouseId()-1, divisao, this.city.giveDeviceId(), mode, dimensions,consumo);
    }

    /**
     * Função que dá parse às camaras desegurança em uma SmartCity
     * @param divisao Divisao em que o dispositivo vai ser adicionado
     * @param input String atual a ser lida das logs
     */
    public void parseSmartCamera(String divisao, String input){
        String[] campos = input.split(",");
        String resolucao = campos[0]; //resolução 0000x0000?
        resolucao = resolucao.replace("(","");
        resolucao = resolucao.replace(")","");
        String[] widthHeight = resolucao.split("x");
        int tamanho = Integer.parseInt(campos[1]);
        float width = Float.parseFloat(widthHeight[0]);
        float heigth = Float.parseFloat(widthHeight[1]);
        double consumo = Double.parseDouble(campos[2]);
		this.city.addDeviceToDivisaoC(city.getHouseId()-1, divisao, this.city.giveDeviceId(),width,heigth,tamanho,consumo);
    }

    /**
     * Função que dá parse às colunas em uma SmartCity
     * @param divisao Divisao em que o dispositivo vai ser adicionado
     * @param input String atual a ser lida das logs
     */
    public void parseSmartSpeaker(String divisao, String input){
        String[] campos = input.split(",");
        int vol = Integer.parseInt(campos[0]);
        String estacao = campos[1];
        double consumo = Double.parseDouble(campos[3]);
        String estado = "OFF";
        this.city.addDeviceToDivisaoS(city.getHouseId()-1,divisao, this.city.getDeviceId(), vol, estacao, campos[2], consumo, estado);
    }

    /**
     * Função que dá parse aos fornecedores em uma SmartCity
     * @param input String atual a ser lida das logs
     */
    public void parseComercializadoresEnergia(String input){
        String[] campos = input.split(",");
        String nome = campos[0];
        this.city.createComercializadorEnergia(nome);
    }

    /**
     * Função que dá parse às marcas em uma SmartCity
     * @param input String atual a ser lida das logs
     */
    public void parseMarca(String input){
        String[] campos = input.split(",");
        String nome = campos[0];
        double consumo = Double.parseDouble(campos[1]);
        this.city.createMarca(nome, consumo);
    }

    /**
     * Função que dá parse à data em uma SmartCity
     * @param data_string String atual a ser lida das logs
     */
    public LocalDate parseData(String data_string){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy");
        return LocalDate.parse(data_string, formatter);
    }
    
    /**
     * Função que trata da parte da simulação com o usuário
     * @param sc Scanner utilizado para ler do terminal
     */
    public void simulation(Scanner sc) throws IOException {
        System.out.println("Especifique o número de linhas que pretende adicionar na simulação: ");
        int loop= sc.nextInt();
        System.out.println("Insira os comandos: ");
        for(int i = 0;i<loop;i++){
            String line = sc.nextLine();
            String [] linha = line.split(",", 4);
        /*
         linha[0] data
         linha[1] id_casa/id_fornecedor
         linha[2] id_dispositivo/id_fornecedor/altera_atributo_fornecedor
         linha[3] ação/novo_valor_atributo/null
         */
            // fazer com que o tempo avance e só depois pode efetuar ação
            // FALTA TRATAR DOS FATORES QUE SÃO DEPENDENTES DA DATA
            //SmartCity city = new SmartCity();
            //city.loadState("path");
            if(this.city.hasSmartHouse(Integer.parseInt(linha[1]))) { // house related
                if (this.city.getCasa(Integer.parseInt(linha[1])).existsDevice(Integer.parseInt(linha[2]))) {
                    this.city.getCasa(Integer.parseInt(linha[1])).getDevice(Integer.parseInt(linha[2]));
                    switch (linha[3].toUpperCase()) {
                        case "SETON", "TURNON" -> this.city.getCasa(Integer.parseInt(linha[1])).getDevice(Integer.parseInt(linha[2])).turnOn();
                        case "SETOFF", "TURNOFF" -> this.city.getCasa(Integer.parseInt(linha[1])).getDevice(Integer.parseInt(linha[2])).turnOff();
                    }
                } else {
                    if (this.city.hasComercializador(linha[2])) {
                        this.city.getCasa(Integer.parseInt(linha[1])).mudaDeFornecedor(this.city.getComercializador(linha[2]), this.city.getDataAtual());
                        throw new IOException(linha[2]);
                    }
                }

            } else{
                if (city.hasComercializador(linha[1])) { // fornecedor related
                    switch (linha[2].toUpperCase()) {
                        case "ALTERAPRECOBASE" -> city.getComercializador(linha[1]).setPrecoBaseKW(Double.parseDouble(linha[3]));
                        case "ALTERAVALORDESCONTO", "ALTERAIMPOSTO", "ALTERAFATORIMPOSTO" -> city.getComercializador(linha[1]).setFatorImposto(Double.parseDouble(linha[3]));
                    }
                    throw new AccessDeniedException(linha[2]);
                }
            }
        }

    }


    
}
