package task3.src.SubPilotos;

import java.util.List;

public interface ISubPiloto {

	public boolean nomePilotoDisponivel(String aNome);

	public boolean niveisPericiaValidos(float aCts, float aSva);

	public void registarPiloto(Piloto aPiloto);

	public Piloto gePiloto(String piloto);

	public boolean hasPiloto(String piloto);

	public List<Piloto> listPilotos();

}