public class SmartDevice {
    private String id;
    private boolean on;
    private double consumoPorHora;

    private double totalConsumo;
    public SmartDevice(String id, double consumoPorHora) {
        super();
        this.id = id;
        this.on = false;
        this.consumoPorHora = consumoPorHora;
    }
    public SmartDevice(SmartDevice smartDevice) {
        super();
        this.id = smartDevice.getId();
        this.on = smartDevice.getOn();
        this.consumoPorHora = smartDevice.getConsumoPorHora();
    }
    public boolean getOn() {return this.on;}

    public void turnOn(){this.on = true;}

    public void turnOff(){this.on = false;}

    public String getId() {return this.id;}
    public void setConsumoPorHora(double consumoPorHora) {
        this.consumoPorHora = consumoPorHora;
    }
    public double getConsumoPorHora() {
        return this.consumoPorHora;
    }

    public double getTotalConsumo(){ return this.totalConsumo; }

    public SmartDevice clone(){return new SmartDevice(this);}

}