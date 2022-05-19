import java.time.LocalDateTime;

public class SmartBulb extends SmartDevice{

    public static final int WARM = 2;
    public static final int NEUTRAL = 1;
    public static final int COLD = 0;
    private int tone;

    public SmartBulb(String id, double consumoPorHora) {
        super(id, consumoPorHora);

    }

    public void setTone(int t) {
        if (t>WARM) this.tone = WARM;
        else this.tone = Math.max(t, COLD);
    }
    public int getTone() {
        return this.tone;
    }
}
