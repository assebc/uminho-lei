package EntregaFinal.src.SubCarros;

import java.util.List;

public interface ISubCarro {

	public boolean categoriaValida(String aC);

	public boolean fiabilidadeValida(int aF);

	public void registarCarro(Carro aCarro);

	public boolean cilindradaValida(int aCilindrada, String aCategoria);

	public Carro getCarro(String id);

	public List<Carro> listCarros();

	public boolean hasCarro(String id);

}