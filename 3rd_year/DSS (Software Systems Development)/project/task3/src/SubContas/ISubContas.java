package task3.src.SubContas;

public interface ISubContas {

	public boolean nomeDisponivel(String aNome);

	public void registarConta(String aNome, String aPassword, userType aType);

	public boolean validarConta(String aNome, String aPassword);

	public userType autenticarConta(String aNome);

	public void atribuirPontos(String aNome, Integer aPontos);

}