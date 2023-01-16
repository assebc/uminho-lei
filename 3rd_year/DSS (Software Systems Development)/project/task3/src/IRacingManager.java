package EntregaFinal.src;

import java.util.List;
import java.util.Map;

import EntregaFinal.src.SubContas.*;
import EntregaFinal.src.SubCampeonatos.*;
import EntregaFinal.src.SubCarros.*;
import EntregaFinal.src.SubPilotos.*;
import EntregaFinal.src.SubSimulacao.*;

/**
 * IRacingManager
 */
public interface IRacingManager{

    // Contas
    
    boolean nomeDisponivel(String aNome);

	void registarConta(String aNome, String aPassword, userType aType);

	boolean validarConta(String aNome, String aPassword);

	userType autenticarConta(String aNome);

	void atribuirPontos(String aNome, Integer aPontos);

    // Campeonatos

    Boolean nomeCampeonatoDisponivel(String aNome);

	Boolean nomeCircuitoDisponivel(String aNome);

	void registarCircuito(Circuito aCircuito);

	List<Circuito> circuitosExistentes();

	void registarCampeonato(Campeonato aCampeonato);

	List<Campeonato> campeonatosIndisponiveis();

	void disponibilizarCampeonato(Campeonato aCampeonato);

	List<Campeonato> campeonatosDisponiveis();

	void indisponibilizarCampeonato(Campeonato aCampeonato);

	Integer calcularRetas(Integer aNrCurvas, Integer aNrChicanes);

    // Carros

    boolean categoriaValida(String aC);

	boolean fiabilidadeValida(int aF);

	void registarCarro(Carro aCarro);

	boolean cilindradaValida(int aCilindrada, String aCategoria);

	List<Carro> listCarros();
	
	boolean hasCarro(String id);

	Carro getCarro(String id);

    // Pilotos

    boolean nomePilotoDisponivel(String aNome);

	boolean niveisPericiaValidos(float aCts, float aSva);

	void registarPiloto(Piloto aPiloto);

	List<Piloto> listPilotos();

	Piloto getPiloto(String nome);

	boolean hasPiloto(String nome);
    
    // Simulação

    void registarJogador(int aCampeonato, String aJogadorID, int aCarro, String aPiloto);

    void jogadorPronto(int aCampeonato, String aJogadorID);

	CorridaBase simularCorridaBase(int aCampeonato);

	CorridaPremium simularCorridaPremium(int aCampeonato);

	List<DadosJogador> ranking(int aCampeonato);

	void afinarCarro(int aCampeonato, String aJogadorID, Carro aFunc);

	boolean temProxCorrida(int aCampeonato);

	public int comecarCampeonato(Campeonato campeonato);

	public Map<Campeonato, List<String>> buscarCampeonatosEmProgresso();

	public void run(String camp);

	public List<List<DadosJogador>> getPosPorCorridaJogadores(String camp);
}
