package EntregaFinal.src.SubSimulacao;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

import EntregaFinal.src.SubCampeonatos.Circuito;
import EntregaFinal.src.SubCampeonatos.SubCampeonatosFacade;
import EntregaFinal.src.SubCampeonatos.TempoMetereologico;

public class CorridaPremium extends Corrida {
	private List<EstadoPremium> _listaEstados = new ArrayList<EstadoPremium>();

	public CorridaPremium(Circuito circuito, Map<String,DadosJogador> dadosJogadores) {
		super(circuito,dadosJogadores);
	}

	public List<EstadoPremium> getListaEstados() {
		return this._listaEstados;
	}

	public void set_listaEstados(List<EstadoPremium> _listaEstados) {
		this._listaEstados = _listaEstados;
	}

	@Override
	public DadosJogador getDadosJogador(String aJogadorID) {
		return super.getDadosJogador(aJogadorID);
	}

	@Override
	public SubCampeonatosFacade get_circuito() {
		return super.get_circuito();
	}

	@Override
	public void set_circuito(SubCampeonatosFacade _circuito) {
		super.set_circuito(_circuito);
	}

	public void set_listaEstados(ArrayList<EstadoPremium> _listaEstados) {
		this._listaEstados = _listaEstados;
	}

	@Override
	public Map<String, DadosJogador> get_dadosJogador() {
		return super.get_dadosJogador();
	}

	@Override
	public Circuito getCircuito() {
		return super.getCircuito();
	}

	@Override
	public void setCircuito(Circuito circuito) {
		super.setCircuito(circuito);
	}

	@Override
	public void set_dadosJogador(Map<String, DadosJogador> _dadosJogador) {
		super.set_dadosJogador(_dadosJogador);
	}

	public List<EstadoPremium> get_listaEstados() {
		return _listaEstados;
	}

	public int hashCode() {
		int lHashCode = 0;
		if ( this._listaEstados != null ) {
			lHashCode += this._listaEstados.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof CorridaPremium) {
			CorridaPremium lCorridaPremiumObject = (CorridaPremium) aObject;
			boolean lEquals = true;
			lEquals &= ((this._listaEstados == lCorridaPremiumObject._listaEstados)
				|| (this._listaEstados != null && this._listaEstados.equals(lCorridaPremiumObject._listaEstados)));
			return lEquals;
		}
		return false;
	}

	

	public boolean ultrapassa(DadosJogador jogador1,DadosJogador jogador2, int i,String gdu, TempoMetereologico temp){

		//Dados do jogador 1
		EstadoJogador estadoJogador1 =_listaEstados.get(i).get_estadosJogadoresMap().get(jogador1.get_jogadorID());
		int cilindrada1 =jogador1.get_carro().get_cilindrada();
		int potencia1 = jogador1.get_carro().get_potencia();
		float cts1 = jogador1.get_piloto().get_cts();
		float sva1 = jogador1.get_piloto().get_sva();
		int segmento1 = estadoJogador1.get_segmento();
		int volta1 = estadoJogador1.get_volta();

		//Dados do jogador 1
		EstadoJogador estadoJogador2 =_listaEstados.get(i).get_estadosJogadoresMap().get(jogador2.get_jogadorID());
		int cilindrada2 =jogador2.get_carro().get_cilindrada();
		int potencia2 = jogador2.get_carro().get_potencia();
		float cts2 = jogador2.get_piloto().get_cts();
		float sva2 = jogador2.get_piloto().get_sva();
		int segmento2 = estadoJogador2.get_segmento();
		int volta2 = estadoJogador2.get_volta();

		//Condições de ultrapassagem
		if(volta1 > volta2) return true;
		if(volta1 < volta2) return false;
		if(segmento1  > segmento2) return true;
		if(segmento1 < segmento2) return false;
		if(estadoJogador2.get_estadoCarro().equals(EstadoCarro.Despistado) || estadoJogador2.get_estadoCarro().equals(EstadoCarro.Avariado)) return true;
		int prob1 = probUltrapassa(cilindrada1,potencia1,cts1,sva1,temp);
		int prob2 = probUltrapassa(cilindrada2,potencia2,cts2,sva2,temp);
		int gduValue;
		if(gdu == "possível")gduValue = 0;
		else if(gdu == "difícil")gduValue = 5;
		else gduValue = 10;
		if(prob1 > prob2 + gduValue) return true;
		return false;
	}

	public boolean fimDeCorrida(EstadoPremium estado){
		for(EstadoJogador estadoJogador : estado.get_estadosJogadoresMap().values())
			if((estadoJogador.get_volta() != getCircuito().get_nr_voltas() + 1) && (estadoJogador.get_estadoCarro() != EstadoCarro.Avariado))
				return false;

		return true;
	}

	@Override
	public int probUltrapassa(int cilindrada, int potencia, float cts, float sva, TempoMetereologico temp) {
		return super.probUltrapassa(cilindrada, potencia, cts, sva, temp);
	}

	@Override
	public boolean avariou(int fiabilidade) {
		return super.avariou(fiabilidade);
	}

	@Override
	public boolean despistou(float sva, float cts, TempoMetereologico temp) {
		return super.despistou(sva, cts, temp);
	}

	public List<DadosJogador> run(){
		int i = 0;
		_listaEstados.add(new EstadoPremium(get_dadosJogador().keySet()));
		List<DadosJogador> result = new ArrayList<>();

		for(DadosJogador dadosJogador : get_dadosJogador().values()){
			result.add(dadosJogador);
		}

		while(!fimDeCorrida(_listaEstados.get(i))) {

			//Copia-se o EstadoBase anterior para poder-se alterar, guardando assim todos os estados.
			_listaEstados.add(_listaEstados.get(i));
			i++;
			//Volta a pôr os carros despistados na corrida
			for (EstadoPremium estado : _listaEstados) {
				for(EstadoJogador estadoJogador : estado.get_estadosJogadoresMap().values())
					if(estadoJogador.get_estadoCarro() == EstadoCarro.Despistado)
						estadoJogador.set_estadoCarro(EstadoCarro.OK);
			}


			//Verifica se o carro do jogador despistou ou avariou e guarda os valores importantes de cada jogador para fazer as ultrapassagens
			int j = 0;
			for(DadosJogador jogador : result){
				//Elementos dos dados do jogador que vão influenciar a ação de andar
				EstadoJogador estadoJogador =_listaEstados.get(i).get_estadosJogadoresMap().get(jogador.get_jogadorID());
				//int cilindrada =jogador.get_carro().get_cilindrada();
				int fiabilidade = jogador.get_carro().get_fiabilidade();
				//int potencia = jogador.get_carro().get_potencia();
				float cts = jogador.get_piloto().get_cts();
				float sva = jogador.get_piloto().get_sva();
				int segmento = estadoJogador.get_segmento();

				//EstadoJogador do jogador
				boolean despistou = despistou(sva,cts,getCircuito().get_tempo_metereologico());
				boolean avariou = avariou(fiabilidade);
				if(despistou) _listaEstados.get(i).getEstadoJogador(jogador.get_jogadorID()).set_estadoCarro(EstadoCarro.Despistado);
				if(avariou) _listaEstados.get(i).getEstadoJogador(jogador.get_jogadorID()).set_estadoCarro(EstadoCarro.Avariado);

				if(j != 0){
					if(!(despistou || avariou) && (estadoJogador.get_volta() < getCircuito().get_nr_voltas() + 1)){
						if(ultrapassa(jogador, result.get(j-1), i,getCircuito().get_segmentos().get(segmento).get_gDU(),getCircuito().get_tempo_metereologico())){
							Collections.swap(result, j, j-1);
						}
					}
				}
				j++;
			}

			for(DadosJogador jogador : result){
				EstadoJogador estadoJogador =_listaEstados.get(i).get_estadosJogadoresMap().get(jogador.get_jogadorID());
				int segmento = estadoJogador.get_segmento();
				int volta = estadoJogador.get_volta();
				if(_listaEstados.get(i).getEstadoJogador(jogador.get_jogadorID()).get_estadoCarro() == EstadoCarro.OK)
					if(getCircuito().get_segmentos().size() != segmento)
						estadoJogador.set_segmento(segmento++);
					else{
						estadoJogador.set_segmento(1);
						estadoJogador.set_volta(volta++);
					}
			}

		}
		return result;
	}
}