package teste21;

public class SmartBulbDimmable extends SmartDevice{
    private double intensidade = 0.5;
    private double totalConsumo = 0;
    private double consumoPorHora;

    public SmartBulbDimmable(String id, double consumoPorHora) {
        super(id, consumoPorHora);
    }

    public double consumoPorHora(){ return this.consumoPorHora * this.intensidade; }

    @Override
    public double getTotalConsumo(){ return this.totalConsumo; }

    private static class InvalidLightIntensity extends Exception {};
    public void changeLightIntensity (double newLightIntesity) {
        this.intensidade = newLightIntesity;
    }
}
