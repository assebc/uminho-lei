package task3.src.SubCarros;

public class C2H extends C2 implements Hibrido {
	private int _motor_eletrico;

	public C2H(){
		super();
		this._motor_eletrico = 0;
	}

	public C2H(String marca, String modelo, Integer potencia, Integer cilindara, Integer fiabilidade, int _motor_eletrico){
		super(marca,modelo,potencia,cilindara,fiabilidade);
		this._motor_eletrico = _motor_eletrico;
	}

	@Override
	public int getPotenciaMotorEletrico() {
		return this._motor_eletrico;
	}

	@Override
	public void setPotenciaMotorEletrico(int potencia) {
		this._motor_eletrico = potencia;
	}

}