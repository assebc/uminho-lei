package EntregaFinal.src.SubPilotos;

import java.util.ArrayList;
import java.util.List;

import EntregaFinal.src.data.PilotoDAO;

public class SubPilotoFacade implements ISubPiloto {
	private final PilotoDAO _pilotos = PilotoDAO.getInstance();

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof SubPilotoFacade) {
			SubPilotoFacade lSubPilotoFacadeObject = (SubPilotoFacade) aObject;
			boolean lEquals = true;
			lEquals &= ((this._pilotos == lSubPilotoFacadeObject._pilotos)
				|| (this._pilotos != null && this._pilotos.equals(lSubPilotoFacadeObject._pilotos)));
			return lEquals;
		}
		return false;
	}

	public boolean nomePilotoDisponivel(String aNome) {
		return !this._pilotos.containsKey(aNome);
	}

	public boolean niveisPericiaValidos(float aCts, float aSva) {
		return (aCts >= 0.0 && aCts <= 1) && (aSva >= 0.0 && aSva <= 1.0);
	}

	public void registarPiloto(Piloto aPiloto) {
		this._pilotos.put(aPiloto.get_nome(),aPiloto);
	}

    public static SubPilotoFacade getInstance() {
        return new SubPilotoFacade();
    }

	@Override
	public Piloto gePiloto(String piloto) {
		return _pilotos.get(piloto);
	}

	@Override
	public boolean hasPiloto(String piloto) {
		return _pilotos.containsKey(piloto);
	}

	@Override
	public List<Piloto> listPilotos() {
		return new ArrayList<>(_pilotos.values());
	}
}