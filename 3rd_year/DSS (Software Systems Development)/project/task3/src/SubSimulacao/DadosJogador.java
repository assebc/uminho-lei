package task3.src.SubSimulacao;

import task3.src.SubCarros.Carro;
import task3.src.SubPilotos.Piloto;

public class DadosJogador {
	private static int idCount=0;
	private int id;
	private String _jogadorID;
	private Carro _carros;
	private Piloto _pilotos;

	public DadosJogador(String id, Carro c, Piloto p){
		this._jogadorID = id;
		this._carros = c;
		this._pilotos = p;
		this.id = idCount++;
	}

	public DadosJogador(String jId, Piloto p, int id){
		this._jogadorID = jId;
		this._carros = null;
		this._pilotos = p;
		this.id = id;
	}

	public DadosJogador(String jId, Carro c, Piloto p, int id){
		this._jogadorID = jId;
		this._carros = c;
		this._pilotos = p;
		this.id = id;
	}

	public int getId(){
		return this.id;
	}

	public void set_jogadorID(String _jogadorID) {
		this._jogadorID = _jogadorID;
	}

	public String get_jogadorID() {
		return _jogadorID;
	}

	public void set_carro(Carro _carro) {
		this._carros = _carro;
	}

	public void set_piloto(Piloto _piloto) {
		this._pilotos = _piloto;
	}

	public Carro get_carro() {
		return _carros;
	}

	public Piloto get_piloto() {
		return _pilotos;
	}
	
	public int hashCode() {
		int lHashCode = 0;
		if ( this._jogadorID != null ) {
			lHashCode += this._jogadorID.hashCode();
		}
		if ( this._carros != null ) {
			lHashCode += this._carros.hashCode();
		}
		if ( this._pilotos != null ) {
			lHashCode += this._pilotos.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof DadosJogador) {
			DadosJogador lDadosJogadorObject = (DadosJogador) aObject;
			boolean lEquals = true;
			lEquals &= ((this._jogadorID == lDadosJogadorObject._jogadorID)
				|| (this._jogadorID != null && this._jogadorID.equals(lDadosJogadorObject._jogadorID)));
			lEquals &= ((this._carros == lDadosJogadorObject._carros)
				|| (this._carros != null && this._carros.equals(lDadosJogadorObject._carros)));
			lEquals &= ((this._pilotos == lDadosJogadorObject._pilotos)
				|| (this._pilotos != null && this._pilotos.equals(lDadosJogadorObject._pilotos)));
			return lEquals;
		}
		return false;
	}
}