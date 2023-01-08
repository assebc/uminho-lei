package task3.src.SubCarros;

public class Carro {
	private String _marca;
	private String _modelo;
	private int _cilindrada;
	private int _potencia;
	private int _fiabilidade;
	private String _iD; // suponho que isto seja a categoria, depois dá fix nisto

	public Carro(){
		this._marca = "";
		this._modelo = "";
		this._potencia = 0;
		this._iD = "";
		this._cilindrada = 0;
		this._fiabilidade = 0;
	}

	public Carro(String marca, String modelo, Integer potencia, Integer cilindara, Integer fiabilidade){
		this._marca = marca;
		this._modelo = modelo;
		this._potencia = potencia;
		this._cilindrada = cilindara;
		this._fiabilidade = fiabilidade;
	}

	public void set_marca(String _marca) {
		this._marca = _marca;
	}

	public void set_modelo(String _modelo) {
		this._modelo = _modelo;
	}

	public void set_cilindrada(int _cilindrada) {
		this._cilindrada = _cilindrada;
	}

	public void set_potencia(int _potencia) {
		this._potencia = _potencia;
	}

	public void set_fiabilidade(int _fiabilidade) {
		this._fiabilidade = _fiabilidade;
	}

	public void set_iD(String _iD) {
		this._iD = _iD;
	}

	public String get_marca() {
		return _marca;
	}

	public String get_modelo() {
		return _modelo;
	}

	public int get_cilindrada() {
		return _cilindrada;
	}

	public int get_potencia() {
		return _potencia;
	}

	public int get_fiabilidade() {
		return _fiabilidade;
	}

	public String get_iD() {
		return _iD;
	}

	public int hashCode() {
		int lHashCode = 0;
		if ( this._marca != null ) {
			lHashCode += this._marca.hashCode();
		}
		if ( this._modelo != null ) {
			lHashCode += this._modelo.hashCode();
		}
		if ( this._iD != null ) {
			lHashCode += this._iD.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof Carro) {
			Carro lCarroObject = (Carro) aObject;
			boolean lEquals = true;
			lEquals &= ((this._marca == lCarroObject._marca)
				|| (this._marca != null && this._marca.equals(lCarroObject._marca)));
			lEquals &= ((this._modelo == lCarroObject._modelo)
				|| (this._modelo != null && this._modelo.equals(lCarroObject._modelo)));
			lEquals &= this._cilindrada == lCarroObject._cilindrada;
			lEquals &= this._potencia == lCarroObject._potencia;
			lEquals &= this._fiabilidade == lCarroObject._fiabilidade;
			lEquals &= ((this._iD == lCarroObject._iD)
				|| (this._iD != null && this._iD.equals(lCarroObject._iD)));
			return lEquals;
		}
		return false;
	}
}