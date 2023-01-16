package EntregaFinal.src.SubCampeonatos;

import java.util.ArrayList;
import java.util.List;

import EntregaFinal.src.data.CircuitoDAO;

public class Campeonato {
	private String _nome;
	private Integer _nr_circuitos;
	private Boolean _disponibilidade;
	private List<Circuito> _circuitos = new ArrayList<>();

	public Campeonato(){
		this._nome = "";
		this._nr_circuitos = 0;
		this._disponibilidade = true;
	}

	public Campeonato(String nome, Boolean disponibilidade){
		this._nome = nome;
		this._nr_circuitos = 0;
		this._disponibilidade = disponibilidade;
	}

	public Campeonato(String nome, Integer nr_circuitos, Boolean disponibilidade){
		this._nome = nome;
		this._nr_circuitos = nr_circuitos;
		this._disponibilidade = disponibilidade;
	}

	public void set_circuitos(ArrayList<Circuito> _circuitos) {
		this._circuitos = _circuitos;
	}

	public void set_disponibilidade(Boolean _disponibilidade) {
		this._disponibilidade = _disponibilidade;
	}

	public void set_nome(String _nome) {
		this._nome = _nome;
	}

	public void set_nr_circuitos(Integer _nr_circuitos) {
		this._nr_circuitos = _nr_circuitos;
	}

	public List<Circuito> get_circuitos() {
		return this._circuitos;
	}

	public Boolean get_disponibilidade() {
		return _disponibilidade;
	}

	public String get_nome() {
		return _nome;
	}

	public Integer get_nr_circuitos() {
		return _nr_circuitos;
	}

	public void addCircuito(String aNome) {
		this._circuitos.add(CircuitoDAO.getInstance().get(aNome));
	}

	public int hashCode() {
		int lHashCode = 0;
		if ( this._nome != null ) {
			lHashCode += this._nome.hashCode();
		}
		if ( this._nr_circuitos != null ) {
			lHashCode += this._nr_circuitos.hashCode();
		}
		if ( this._disponibilidade != null ) {
			lHashCode += this._disponibilidade.hashCode();
		}
		if ( this._circuitos != null ) {
			lHashCode += this._circuitos.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof Campeonato) {
			Campeonato lCampeonatoObject = (Campeonato) aObject;
			boolean lEquals = true;
			lEquals &= ((this._nome == lCampeonatoObject._nome)
				|| (this._nome != null && this._nome.equals(lCampeonatoObject._nome)));
			lEquals &= ((this._nr_circuitos == lCampeonatoObject._nr_circuitos)
				|| (this._nr_circuitos != null && this._nr_circuitos.equals(lCampeonatoObject._nr_circuitos)));
			lEquals &= ((this._disponibilidade == lCampeonatoObject._disponibilidade)
				|| (this._disponibilidade != null && this._disponibilidade.equals(lCampeonatoObject._disponibilidade)));
			lEquals &= ((this._circuitos == lCampeonatoObject._circuitos)
				|| (this._circuitos != null && this._circuitos.equals(lCampeonatoObject._circuitos)));
			return lEquals;
		}
		return false;
	}
}