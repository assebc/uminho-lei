package Model;

import java.lang.StringBuilder;
import java.time.LocalDate;


/**
 * Uma SmartCamera é um SmartDevice que além de ligar e desligar permite também
 * gravar videos de segurança.
 *
 * Obtém a resolução dos ficheiros
 * Tamanho do ficheiro de videos
 * Consumo Energético
 *
 */
public class SmartCamera extends SmartDevice {

    private float resolucao; 
    private int tamanho_ficheiros;

    /**
     * Inicialização da camara
     * @param id id a definir
     * @param resolucao resolução a definir
     * @param tamanhoFicheiros tamanho dos ficheiros a definir
     * @param estado estado a definir
     * @param consumo consumo a definir
     * @param ligadoI data de ativar a camara a definir
     */
    public SmartCamera(int id,float resolucao, int tamanhoFicheiros, state estado, float consumo, LocalDate ligadoI){
        super(id, estado, consumo, ligadoI, LocalDate.now());
        this.resolucao=resolucao;
        this.tamanho_ficheiros= tamanhoFicheiros;
    }

    /**
     * Inicializador da camara
     * @param id id a definir
     * @param resolucao resolução a definir
     * @param tamanhoFicheiros tamanho de ficheiro a definir
     * @param consumo consumo a definir
     */
    public SmartCamera(int id, String resolucao, int tamanhoFicheiros, double consumo){
        super(id, state.OFF, consumo, LocalDate.now(), LocalDate.now());
        String[] wxh = resolucao.split("x");
        float width = Float.parseFloat(wxh[0]);
        float height = Float.parseFloat(wxh[1]);
        this.resolucao=width*height/1000000;
        this.tamanho_ficheiros= tamanhoFicheiros;
    }

    /**
     * Inicializador da camera
     * @param id id a definir
     * @param width comprimento a definir
     * @param height largura a definir
     * @param tamanhoFicheiros tamanho de ficheiros a definir
     * @param estado estado a definir
     */
    public SmartCamera(int id, float width,float height, int tamanhoFicheiros, String estado){
        super(id, estado, 0, LocalDate.now(), LocalDate.now());
        this.resolucao=width*height/1000000;
        this.tamanho_ficheiros= tamanhoFicheiros;
        this.setConsumo(resolucao*tamanhoFicheiros);
    }

    /**
     * Inicializador de camara
     * @param id id a definir
     * @param width compprimento a definir
     * @param height altura a definir
     * @param tamanhoFicheiros tamanho de ficheiros a definir
     * @param consumo consumo a definir
     */
    public SmartCamera(int id, float width,float height, int tamanhoFicheiros, double consumo){
        super(id, state.OFF, consumo, LocalDate.now(), LocalDate.now());
        this.resolucao=width*height/1000000;
        this.tamanho_ficheiros= tamanhoFicheiros;
    }

    /**
     * Inicializador de camara
     * @param id id a definir
     * @param width compprimento a definir
     * @param height altura a definir
     * @param tamanhoFicheiros tamanho de ficheiros a definir
     * @param estado estado a definir
     * @param consumo consumo a definir
     */
    public SmartCamera(int id, float width,float height, int tamanhoFicheiros, state estado, float consumo){
        super(id, estado, consumo, LocalDate.now(), LocalDate.now());
        this.resolucao=width*height/1000000;
        this.tamanho_ficheiros= tamanhoFicheiros;
    }

    /**
     * Camara a duplicar
     * @param sc camara a ser duplicado
     */
    public SmartCamera(SmartCamera sc){
        super(sc.getID(), sc.getEstado(), sc.getConsumo(), sc.getLigadoInit(), sc.getDataFin());
        this.resolucao=sc.getResolucao();
        this.tamanho_ficheiros=sc.getFileSize();
    }

    /**
     * Getter de consumo da lampada
     * @param data_atual data atual da camara
     * @param dataSimulacao data de inicialização da camara
     * @return consumo
     */
    public double getConsumo(LocalDate data_atual, LocalDate dataSimulacao){
        return switch (this.getEstado().toString()) {
            case ("ON") -> this.tamanho_ficheiros * this.resolucao;
            default -> 0;
        };
    }

    /**
     * Getter da resolução
     * @return resolução
     */
    public float getResolucao(){
        return this.resolucao;
    }

    /**
     * Getter do tamanho do ficheiros
     * @return tamanho dos ficheros
     */
    public int getFileSize(){
        return this.tamanho_ficheiros;
    }

    /**
     * Getter do consumo da camara
     * @return consumo
     */
    public double getConsumo(){
        if (this.getEstado()==state.OFF)
            return 0;
        else{
            return this.tamanho_ficheiros*resolucao;
        }       
   } //tempo de gravacao, resolucao, bitrate

    /**
     * Setter de resolução
     * @param width comprimento da resolução a definir
     * @param height largura da resolução a definir
     */
    public void setResolucao(float width, float height){
        this.resolucao=(width*height)/10000000;
    }

    /**
     * Setter da resolução
     * @param res resolução a definir
     */
    public void setResolucao(float res){
        this.resolucao=res;
    }

    /**
     * Setter do tamanho de ficheiros
     * @param file tamanho de ficheiros a definir'«
     */
    public void setFileSize(int file){
        this.tamanho_ficheiros=file;
    }

    /**
     * Comparar camara a um objeto
     * @param obj Objeto a comparar
     * @return boolean de comparação
     */
    public boolean equals(Object obj){
        if(this==obj)
            return true;
        
        if (obj==null||obj.getClass()!=this.getClass())
            return false;
        
        SmartCamera newC = (SmartCamera) obj;
        return (this.getID() == newC.getID() && this.resolucao == (newC.getResolucao()) && this.tamanho_ficheiros==newC.getFileSize()  && this.getEstado().toString().equals(newC.getEstado().toString())  &&  this.getConsumo() == (newC.getConsumo()));
    }

    /**
     * toString de uma camara
     * @return String com as especificações de uma camara
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n[SmartCamera]");
        sb.append("\nID: ");
        sb.append(this.getID());
        sb.append("\nResolução: ");
        sb.append(this.resolucao);
        sb.append("\nTamanho dos ficheiros:");
        sb.append(this.tamanho_ficheiros);
        sb.append("\nEstado: ");
        sb.append(this.getEstado());
        sb.append("\n");
        return sb.toString();
    }

    /**
     * Clone de camara
     * @return camara clonada
     */
    public SmartCamera clone(){
        return new SmartCamera(this);
    }
}   
