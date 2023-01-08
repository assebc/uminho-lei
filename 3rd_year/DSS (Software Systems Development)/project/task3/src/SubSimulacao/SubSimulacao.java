package task3.src.SubSimulacao;

import task3.src.SubCampeonatos.Campeonato;
import task3.src.SubCarros.Carro;
import task3.src.data.CampeonatoAtivoDAO;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class SubSimulacao implements ISubSimulacao {
	public CampeonatoAtivoDAO _campeonatoMap = CampeonatoAtivoDAO.getInstance();
	
	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof SubSimulacao) {
			SubSimulacao lSubSimulaçaoObject = (SubSimulacao) aObject;
			boolean lEquals = true;
			lEquals &= ((this._campeonatoMap == lSubSimulaçaoObject._campeonatoMap)
				|| (this._campeonatoMap != null && this._campeonatoMap.equals(lSubSimulaçaoObject._campeonatoMap)));
			return lEquals;
		}
		return false;
	}

	public void registarJogador(int aCampeonato, String aJogadorID, String aCarro, String aPiloto) {
		CampeonatoAtivo cAtiv;	
		if(!this._campeonatoMap.containsKey(aCampeonato)){
			throw new IllegalArgumentException("CampeonatoAtivo não existe: " + aCampeonato);
			
		}
		cAtiv = this._campeonatoMap.get(aCampeonato);
		
		cAtiv.novoJogador(aJogadorID, aCarro, aPiloto);
		this._campeonatoMap.put(aCampeonato, cAtiv);
	}

	public void jogadorPronto(int aCampeonato, String aJogadorID) {
		if(!this._campeonatoMap.containsKey(aCampeonato)){
			throw new IllegalArgumentException("CampeonatoAtivo não existe: " + aCampeonato);
		}
		CampeonatoAtivo cAtiv = this._campeonatoMap.get(aCampeonato);
		cAtiv.jogadorPronto(aJogadorID);
	}

	public CorridaBase simularCorridaBase(int aCampeonato) {
		if(!this._campeonatoMap.containsKey(aCampeonato)){
			throw new IllegalArgumentException("CampeonatoAtivo não existe: " + aCampeonato);
		}
		CampeonatoAtivo cAtiv = this._campeonatoMap.get(aCampeonato);
		return cAtiv.simularCorridaBase();
	}

	public CorridaPremium simularCorridaPremium(int aCampeonato) {
		if(!this._campeonatoMap.containsKey(aCampeonato)){
			throw new IllegalArgumentException("CampeonatoAtivo não existe: " + aCampeonato);
		}
		CampeonatoAtivo cAtiv = this._campeonatoMap.get(aCampeonato);
		return cAtiv.simularCorridaPremium();
	}

	public List<DadosJogador> ranking(int aCampeonato) {
		if(!this._campeonatoMap.containsKey(aCampeonato)){
			throw new IllegalArgumentException("CampeonatoAtivo não existe: " + aCampeonato);
		}
		CampeonatoAtivo cAtiv = this._campeonatoMap.get(aCampeonato);
		return cAtiv.ranking();
	}

	public void afinarCarro(int aCampeonato, String aJogadorID, Carro aFunc) {
		if(!this._campeonatoMap.containsKey(aCampeonato)){
			throw new IllegalArgumentException("CampeonatoAtivo não existe: " + aCampeonato);
		}
		CampeonatoAtivo cAtiv = this._campeonatoMap.get(aCampeonato);
		cAtiv.afinarCarro(aJogadorID, aFunc);
	}

	public boolean temProxCorrida(int aCampeonato) {
		if(!this._campeonatoMap.containsKey(aCampeonato)){
			throw new IllegalArgumentException("CampeonatoAtivo não existe: " + aCampeonato);
		}
		CampeonatoAtivo cAtiv = this._campeonatoMap.get(aCampeonato);
		return cAtiv.temProxCorrida();
	}

	public int comecarCampeonato(Campeonato campeonato) {
		CampeonatoAtivo cAtiv = new CampeonatoAtivo(campeonato);
		this._campeonatoMap.put(cAtiv.getId(), cAtiv);
		return cAtiv.getId();
	}

	public Map<Campeonato, List<String>> buscarCampeonatosEmProgresso() {
		Map<Campeonato, List<String>> camps = new HashMap<>();
		List<String> players = new ArrayList<>();
		List<CampeonatoAtivo> camps_ativ = new ArrayList<>(this._campeonatoMap.values());
		for(CampeonatoAtivo c : camps_ativ){
			players = new ArrayList<>(c.get_jogadorAtivoMap()
									   .values()
									   .stream()
									   .map(cA -> cA.get_dados().get_jogadorID())
        							   .collect(Collectors.toList()));
			for(String s:players){
				//Este if agora n funciona :(
				/*
				if(!c.get_jogadorAtivoMap().get(s).get_idCampeonato().equals(c.get_campeonato().get_nome()))
					players.remove(s);
				 */
			}					
			camps.put(c.get_campeonato(),players);
		}
		return camps;
	}

	@Override
	public void run(String camp) {
		CampeonatoAtivo c = this._campeonatoMap.values()
							.stream()
							.filter(ca -> ca.get_campeonato().get_nome().equals(camp))
							.findFirst()
							.get();
		c.run();
	}

	@Override
	public List<List<DadosJogador>> getPosPorCorridaJogadores(String camp) {
		CampeonatoAtivo c = this._campeonatoMap.values()
							.stream()
							.filter(ca -> ca.get_campeonato().get_nome().equals(camp))
							.findFirst()
							.get();
		return c.getPosPorCorridaJogadores();
	}

}