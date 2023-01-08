package task3.src.SubSimulacao;

import task3.src.data.CarroDAO;
import task3.src.data.PilotoDAO;

public class JogadorAtivo{
	private Boolean _pronto;
	private int _nAfinaçoes;
	private DadosJogador _dados;
	private int campeonatoAtivoId;

	public JogadorAtivo(String id){
		this._dados = new DadosJogador(id, null, null);
		this.campeonatoAtivoId = 0;
		this._pronto = false;
		this._nAfinaçoes = 0;
	}
	public JogadorAtivo(String Id, String aCarro, String aPiloto, int nAfin, int campeonatoAtivoId){
		this._pronto = false;
		this._nAfinaçoes = nAfin;
		this._dados = new DadosJogador(Id, CarroDAO.getInstance().get(aCarro), PilotoDAO.getInstance().get(aPiloto));
		this.campeonatoAtivoId = campeonatoAtivoId;
	}

	public JogadorAtivo(DadosJogador dj, boolean pronto, int nAfinacoes, int campeonatoAtivoId){
		this._dados = dj;
		this._pronto = pronto;
		this._nAfinaçoes = nAfinacoes;
		this.campeonatoAtivoId = campeonatoAtivoId;
	}
	
	public DadosJogador get_dados() {
		return _dados;
	}

	public int getCampeonatoAtivoId(){
		return this.campeonatoAtivoId;
	}

	public void setCampeonatoAtivoId(int campeonatoAtivoId) {
		this.campeonatoAtivoId = campeonatoAtivoId;
	}

	public int get_nAfinaçoes() {
		return _nAfinaçoes;
	}

	public Boolean get_pronto() {
		return _pronto;
	}

	public void set_dados(DadosJogador _dados) {
		this._dados = _dados;
	}

	public void set_nAfinaçoes(int _nAfinaçoes) {
		this._nAfinaçoes = _nAfinaçoes;
	}

	public void set_pronto(Boolean _pronto) {
		this._pronto = _pronto;
	}
	
	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof JogadorAtivo) {
			JogadorAtivo lJogadorAtivoObject = (JogadorAtivo) aObject;
			boolean lEquals = true;
			lEquals &= ((this._pronto == lJogadorAtivoObject._pronto)
				|| (this._pronto != null && this._pronto.equals(lJogadorAtivoObject._pronto)));
			lEquals &= this._nAfinaçoes == lJogadorAtivoObject._nAfinaçoes;
			lEquals &= ((this._dados == lJogadorAtivoObject._dados)
				|| (this._dados != null && this._dados.equals(lJogadorAtivoObject._dados)));
			return lEquals;
		}
		return false;
	}
}