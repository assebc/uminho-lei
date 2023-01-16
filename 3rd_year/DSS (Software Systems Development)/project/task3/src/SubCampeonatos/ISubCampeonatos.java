package EntregaFinal.src.SubCampeonatos;

import java.util.List;

public interface ISubCampeonatos {

	public Boolean nomeCampeonatoDisponivel(String aNome);

	public Boolean nomeCircuitoDisponivel(String aNome);

	public void registarCircuito(Circuito aCircuito);

	public List<Circuito> circuitosExistentes();

	public void registarCampeonato(Campeonato aCampeonato);

	public List<Campeonato> campeonatosIndisponiveis();

	public void disponibilizarCampeonato(Campeonato aCampeonato);

	public List<Campeonato> campeonatosDisponiveis();

	public void indisponibilizarCampeonato(Campeonato aCampeonato);

	public Integer calcularRetas(Integer aNrCurvas, Integer aNrChicanes);
}