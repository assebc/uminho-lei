package teste21;

public class SmartSpeaker extends SmartDevice{

    public static final int MAX = 20;
    private int volume;
    private String channel;


    public SmartSpeaker(String id, String channel, double consumoPorHora) {
        super(id, consumoPorHora);
        this.channel = channel;
        this.volume = 10;
    }


}