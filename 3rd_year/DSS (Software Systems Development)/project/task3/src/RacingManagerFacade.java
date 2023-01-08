package task3.src;

import java.util.List;
import java.util.Map;

import task3.src.SubContas.*;
import task3.src.SubCampeonatos.*;
import task3.src.SubCarros.*;
import task3.src.SubPilotos.*;
import task3.src.SubSimulacao.*;

public class RacingManagerFacade implements IRacingManager{
    
	private ISubContas contasFacade;
	private ISubCampeonatos campeonatosFacade;
	private ISubCarro carroFacade;
	private ISubPiloto pilotoFacade;
	private ISubSimulacao simulacaoFacade;

    public RacingManagerFacade(){
		this.contasFacade = new SubContasFacade();
		this.campeonatosFacade = new SubCampeonatosFacade();
		this.carroFacade = new SubCarroFacade();
		this.pilotoFacade = new SubPilotoFacade();
		this.simulacaoFacade = new SubSimulacao();
	}

    // Contas
    
    public boolean nomeDisponivel(String aNome){return this.contasFacade.nomeDisponivel(aNome);}

	public void registarConta(String aNome, String aPassword, userType aType){this.contasFacade.registarConta(aNome, aPassword, aType);}

	public boolean validarConta(String aNome, String aPassword){return this.contasFacade.validarConta(aNome, aPassword);}

	public userType autenticarConta(String aNome){return this.contasFacade.autenticarConta(aNome);}

	public void atribuirPontos(String aNome, Integer aPontos){this.contasFacade.atribuirPontos(aNome, aPontos);}

    // Campeonatos

    public Boolean nomeCampeonatoDisponivel(String aNome){return this.campeonatosFacade.nomeCampeonatoDisponivel(aNome);}

	public Boolean nomeCircuitoDisponivel(String aNome){return this.campeonatosFacade.nomeCircuitoDisponivel(aNome);}

	public void registarCircuito(Circuito aCircuito){this.campeonatosFacade.registarCircuito(aCircuito);}

	public List<Circuito> circuitosExistentes(){return this.campeonatosFacade.circuitosExistentes();}

	public void registarCampeonato(Campeonato aCampeonato){this.campeonatosFacade.registarCampeonato(aCampeonato);}

	public List<Campeonato> campeonatosIndisponiveis(){return this.campeonatosFacade.campeonatosIndisponiveis();}

	public void disponibilizarCampeonato(Campeonato aCampeonato){this.campeonatosFacade.disponibilizarCampeonato(aCampeonato);}

	public List<Campeonato> campeonatosDisponiveis(){return this.campeonatosFacade.campeonatosDisponiveis();}

	public void indisponibilizarCampeonato(Campeonato aCampeonato){this.campeonatosFacade.indisponibilizarCampeonato(aCampeonato);}

	public Integer calcularRetas(Integer aNrCurvas, Integer aNrChicanes){return this.campeonatosFacade.calcularRetas(aNrCurvas, aNrChicanes);}

    // Carros

    public boolean categoriaValida(String aC){return this.carroFacade.categoriaValida(aC);}

	public boolean fiabilidadeValida(int aF){return this.carroFacade.fiabilidadeValida(aF);}

	public void registarCarro(Carro aCarro){this.carroFacade.registarCarro(aCarro);}

	public boolean cilindradaValida(int aCilindrada, String aCategoria){return this.carroFacade.cilindradaValida(aCilindrada, aCategoria);}

	@Override
	public Carro getCarro(String id) {
		return carroFacade.getCarro(id);
	}

	@Override
	public boolean hasCarro(String id) {
		return carroFacade.hasCarro(id);
	}

	@Override
	public List<Carro> listCarros() {
		return carroFacade.listCarros();
	}


    // Pilotos

    public boolean nomePilotoDisponivel(String aNome){return this.pilotoFacade.nomePilotoDisponivel(aNome);}

	@Override
	public boolean niveisPericiaValidos(float aCts, float aSva){return this.pilotoFacade.niveisPericiaValidos(aCts, aSva);}

	@Override
	public void registarPiloto(Piloto aPiloto){this.pilotoFacade.registarPiloto(aPiloto);}

	@Override
	public Piloto getPiloto(String nome) {
		return this.pilotoFacade.gePiloto(nome);
	}

	@Override
	public boolean hasPiloto(String nome) {
		return this.pilotoFacade.hasPiloto(nome);
	}

	@Override
	public List<Piloto> listPilotos() {
		return this.pilotoFacade.listPilotos();
	}


    
    // Simulação

	@Override
	public void registarJogador(int aCampeonato, String aJogadorID, String aCarro, String aPiloto) {
		this.simulacaoFacade.registarJogador(aCampeonato, aJogadorID, aCarro, aPiloto);
		
	}

	@Override
	public void jogadorPronto(int aCampeonato, String aJogadorID) {
		this.simulacaoFacade.jogadorPronto(aCampeonato, aJogadorID);
		
	}

	@Override
	public CorridaBase simularCorridaBase(int aCampeonato) {
		return this.simulacaoFacade.simularCorridaBase(aCampeonato);
	}

	@Override
	public CorridaPremium simularCorridaPremium(int aCampeonato) {
		return this.simulacaoFacade.simularCorridaPremium(aCampeonato);
	}

	@Override
	public List<DadosJogador> ranking(int aCampeonato) {
		return this.simulacaoFacade.ranking(aCampeonato);
	}

	@Override
	public void afinarCarro(int aCampeonato, String aJogadorID, Carro aFunc) {
		this.simulacaoFacade.afinarCarro(aCampeonato, aJogadorID, aFunc);
		
	}

	@Override
	public boolean temProxCorrida(int aCampeonato) {
		return this.simulacaoFacade.temProxCorrida(aCampeonato);
	}

	@Override
	public int comecarCampeonato(Campeonato campeonato) {
		return this.simulacaoFacade.comecarCampeonato(campeonato);
	}

	@Override
	public Map<Campeonato, List<String>> buscarCampeonatosEmProgresso() {
		return this.simulacaoFacade.buscarCampeonatosEmProgresso();
	}

	@Override
	public List<List<DadosJogador>> getPosPorCorridaJogadores(String camp) {
		return this.simulacaoFacade.getPosPorCorridaJogadores(camp);
	}

	@Override
	public void run(String camp) {
		this.simulacaoFacade.run(camp);	
	}

}
