package task3.src.SubSimulacao;

import task3.src.SubCampeonatos.Campeonato;
import task3.src.SubCarros.Carro;

import java.util.List;
import java.util.Map;

public interface ISubSimulacao {

	public void registarJogador(int aCampeonato, String aJogadorID, String aCarro, String aPiloto);

	public void jogadorPronto(int aCampeonato, String aJogadorID);

	public CorridaBase simularCorridaBase(int aCampeonato);

	public CorridaPremium simularCorridaPremium(int aCampeonato);

	public List<DadosJogador> ranking(int aCampeonato);

	public void afinarCarro(int aCampeonato, String aJogadorID, Carro aFunc);

	public boolean temProxCorrida(int aCampeonato);

	public int comecarCampeonato(Campeonato campeonato);

	public Map<Campeonato, List<String>> buscarCampeonatosEmProgresso();

	public void run(String camp);

	public List<List<DadosJogador>> getPosPorCorridaJogadores(String camp);

}