package EntregaFinal.src.SubPilotos;

public class Piloto {
	private String _nome;
	private Float _cts;
	private Float _sva;

	public Piloto(){
		this._nome = "";
		this._cts = (float) 0.0;
		this._sva = (float) 0.0;
	}

	public Piloto(String nome, Float cts, Float sva){
		this._nome = nome;
		this._cts = cts;
		this._sva = sva;
	}

	public void set_nome(String _nome) {
		this._nome = _nome;
	}

	public void set_cts(Float _cts) {
		this._cts = _cts;
	}

	public void set_sva(Float _sva) {
		this._sva = _sva;
	}

	public String get_nome() {
		return _nome;
	}

	public Float get_cts() {
		return _cts;
	}

	public Float get_sva() {
		return _sva;
	}

	public int hashCode() {
		int lHashCode = 0;
		if ( this._nome != null ) {
			lHashCode += this._nome.hashCode();
		}
		if ( this._cts != null ) {
			lHashCode += this._cts.hashCode();
		}
		if ( this._sva != null ) {
			lHashCode += this._sva.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof Piloto) {
			Piloto lPilotoObject = (Piloto) aObject;
			boolean lEquals = true;
			lEquals &= ((this._nome == lPilotoObject._nome)
				|| (this._nome != null && this._nome.equals(lPilotoObject._nome)));
			lEquals &= ((this._cts == lPilotoObject._cts)
				|| (this._cts != null && this._cts.equals(lPilotoObject._cts)));
			lEquals &= ((this._sva == lPilotoObject._sva)
				|| (this._sva != null && this._sva.equals(lPilotoObject._sva)));
			return lEquals;
		}
		return false;
	}
}