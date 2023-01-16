package EntregaFinal.src.SubSimulacao;

public class  EstadoJogadorPremium extends EstadoJogador {
	private int _tempoTotal;

	public EstadoJogadorPremium(){
		super();
		this._segmento = 1;
		this._volta = 0;
		this._estadoCarro = EstadoCarro.OK;
		this._tempoTotal = 0;
	}

	@Override
	public EstadoCarro get_estadoCarro() {
		return super.get_estadoCarro();
	}

	@Override
	public int get_segmento() {
		return super.get_segmento();
	}

	@Override
	public int get_volta() {
		return super.get_volta();
	}

	public int get_tempoTotal() {
		return _tempoTotal;
	}

	@Override
	public void set_estadoCarro(EstadoCarro _estadoCarro) {
		super.set_estadoCarro(_estadoCarro);
	}

	@Override
	public void set_segmento(int _segmento) {
		super.set_segmento(_segmento);
	}

	@Override
	public void set_volta(int _volta) {
		super.set_volta(_volta);
	}

	public void set_tempoTotal(int _tempoTotal) {
		this._tempoTotal = _tempoTotal;
	}
	
	public int hashCode() {
		int lHashCode = 0;
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof EstadoJogadorPremium) {
			EstadoJogadorPremium lEstadoJogadorPremiumObject = (EstadoJogadorPremium) aObject;
			boolean lEquals = true;
			lEquals &= this._tempoTotal == lEstadoJogadorPremiumObject._tempoTotal;
			return lEquals;
		}
		return false;
	}
}