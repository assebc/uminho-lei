package EntregaFinal.src.SubSimulacao;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import EntregaFinal.src.SubCampeonatos.Circuito;
import EntregaFinal.src.SubCampeonatos.SubCampeonatosFacade;
import EntregaFinal.src.SubCampeonatos.TempoMetereologico;

public abstract class Corrida {
	private Circuito circuito;
	private SubCampeonatosFacade _circuito;
	private Map<String,DadosJogador> _dadosJogador = new HashMap<>();

	public Corrida(Circuito circuito, Map<String, DadosJogador> dadosJogadores) {
		this.circuito = circuito;
		this._dadosJogador = dadosJogadores;
	}

	public DadosJogador getDadosJogador(String aJogadorID) {
		return this._dadosJogador.get(aJogadorID);
	}
	
	public SubCampeonatosFacade get_circuito() {
		return _circuito;
	}

	public Map<String, DadosJogador> get_dadosJogador() {
		return _dadosJogador;
	}

	public Circuito getCircuito() {
		return circuito;
	}

	public void setCircuito(Circuito circuito) {
		this.circuito = circuito;
	}

	public void set_circuito(SubCampeonatosFacade _circuito) {
		this._circuito = _circuito;
	}

	public void set_dadosJogador(Map<String, DadosJogador> _dadosJogador) {
		this._dadosJogador = _dadosJogador;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof Corrida) {
			Corrida lCorridaObject = (Corrida) aObject;
			boolean lEquals = true;
			lEquals &= ((this._circuito == lCorridaObject._circuito)
				|| (this._circuito != null && this._circuito.equals(lCorridaObject._circuito)));
			lEquals &= ((this._dadosJogador == lCorridaObject._dadosJogador)
				|| (this._dadosJogador != null && this._dadosJogador.equals(lCorridaObject._dadosJogador)));
			return lEquals;
		}
		return false;
	}

	public boolean despistou(float sva, float cts, TempoMetereologico temp){
		int svaux = (int) (75 + (1-sva)*2*10);
		if(temp == TempoMetereologico.Chuva) svaux = svaux - (int) ((cts*10)/2);
		else svaux = svaux - (int) (((1-cts)*10)/2);
		Random rand = new Random();
		int r = rand.nextInt(100);
		if(r > sva) return true;
		return false;
	}

	public boolean avariou(int fiabilidade){
		Random rand = new Random();
		int r = rand.nextInt(100);
		if(r > fiabilidade) return true;
		return false;
	}

	public int probUltrapassa(int cilindrada, int potencia, float cts, float sva, TempoMetereologico temp){
		if(temp == TempoMetereologico.Chuva) return (int) ((cilindrada/100)*0.2 + (potencia/10)*0.2 + sva*100*0.5 + (1-cts)*100*0.1);
		else return (int) ((cilindrada/100)*0.2 + (potencia/10)*0.2 + sva*100*0.5 + cts*100*0.1);
	}
	
	
}