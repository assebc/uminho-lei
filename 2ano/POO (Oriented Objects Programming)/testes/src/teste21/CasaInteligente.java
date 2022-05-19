package teste21;

import java.io.*;
import java.util.*;
import java.util.function.Consumer;

public class CasaInteligente {
    private Map<String,Collection<SmartDevice>> div_devices;
    private Collection<SmartDevice> devices;

    public CasaInteligente(Collection<SmartDevice> dispositivos) {
        this.div_devices = new HashMap<>();
        this.devices = dispositivos.stream().map(SmartDevice::clone).toList();
    }

    public void remove(String id) throws NaoExisteDispositivoException {
        SmartDevice sd = null;
        for(SmartDevice d: this.devices){
            if(d.getId().equals(id)) {sd = d; break;}
        }
        if(sd==null) throw new NaoExisteDispositivoException(id);
        this.devices.remove(sd);
        for(Collection<SmartDevice> sc :this.div_devices.values()){
            sc.remove(sd);
        }
    }

    public Iterator<SmartDevice> devicesPorConsumoCreste(){
        return this.devices.stream().map(SmartDevice::clone)
                                    .sorted(Comparator.comparingDouble(SmartDevice::getConsumoPorHora))
                                    .iterator();
    }

    public double getotalConsumo(String divisao){
        return this.div_devices.get(divisao).stream().mapToDouble(SmartDevice::getTotalConsumo).count();
    }

    public String divisaoMaisEconomica(){
        Map <String,Double> div_econom = new HashMap<>();
        String div = this.div_devices.keySet().stream().toList().get(0);
        double min = getotalConsumo(div);
        for(String x:this.div_devices.keySet()){
            if(getotalConsumo(x)<min){
                div = x;
                min = getotalConsumo(div);
            } else if(getotalConsumo(x)==min && x.compareTo(div)<0){
                div = x;
                min = getotalConsumo(div);
            }
        }
        return div;
    }

    public void alteraInfo(Consumer<SmartBulbDimmable> bd){
        this.devices.stream().filter(v->v instanceof SmartBulbDimmable)
                .map(v->(SmartBulbDimmable) v)
                .forEach(bd);
        bd = s->s.changeLightIntensity(0.25);
    }

    public boolean apenasNumaDivisao(){
        return this.devices.stream().distinct().count()==this.div_devices.values().stream().map(Collection::size).reduce(0,Integer::sum);
    }

    public boolean gravaEmFichObjetos(String fich) throws IOException{
        ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(fich));
        this.devices.stream().filter(s-> s instanceof SmartSpeaker).forEach(o-> {
            try {
                os.writeObject(o);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
        os.flush();
        os.close();
        return true;
    }
}
