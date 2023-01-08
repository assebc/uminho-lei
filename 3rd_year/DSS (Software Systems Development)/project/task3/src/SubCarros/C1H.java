package EntregaFinal.src.SubCarros;

public class C1H extends C1 implements Hibrido {
	private int _motor_eletrico;

	public C1H(){
		super();
		this._motor_eletrico = 0;
	}

	public C1H(String marca, String modelo, Integer potencia, Integer cilindara, Integer fiabilidade, int _motor_eletrico){
		super(marca,modelo,potencia,cilindara,fiabilidade);
		this._motor_eletrico = _motor_eletrico;
	}

	@Override
	public int getPotenciaMotorEletrico() {
		return _motor_eletrico;
	}

	@Override
	public void setPotenciaMotorEletrico(int potencia) {
		this._motor_eletrico = potencia;
	}

}