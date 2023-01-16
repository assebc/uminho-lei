package EntregaFinal.src.SubCarros;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import EntregaFinal.src.data.CarroDAO;

public class SubCarroFacade implements ISubCarro {
	private final CarroDAO _carros = CarroDAO.getInstance();

	@Override
	public boolean categoriaValida(String aC) {
		return Objects.equals(aC, "C1") || Objects.equals(aC, "c1") || Objects.equals(aC, "C2") ||
				Objects.equals(aC, "c2") || Objects.equals(aC, "GT") || Objects.equals(aC, "gt") ||
				Objects.equals(aC, "SC") || Objects.equals(aC, "sc");
	}

	@Override
	public boolean fiabilidadeValida(int aF) {
		if(0 < aF && aF < 100)
			return true;
		return false;
	}

	@Override
	public void registarCarro(Carro aCarro) {
		int id = _carros.size();
		aCarro.set_iD(id);
		this._carros.put(id,aCarro);
	}

	@Override
	public boolean cilindradaValida(int aCilindrada, String aCategoria) {
		boolean b = false;
		if((Objects.equals(aCategoria, "C1") || Objects.equals(aCategoria, "c1")) && (aCilindrada == 6000) )
			b = true;

		else if((Objects.equals(aCategoria, "C2") || Objects.equals(aCategoria, "c2")) && (2000 <= aCilindrada) && (aCilindrada <= 4000))
			b = true;

		else if((Objects.equals(aCategoria, "GT") || Objects.equals(aCategoria, "gt")) && (3000 <= aCilindrada) && (aCilindrada <= 5000))
			b = true;

		else if((Objects.equals(aCategoria, "SC") || Objects.equals(aCategoria, "sc")) && (aCilindrada == 2500) )
			b = true;

		return b;
	}

	public int hashCode() {
		int lHashCode = 0;
		if ( this._carros != null ) {
			lHashCode += this._carros.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof SubCarroFacade) {
			SubCarroFacade lSubCarroFacadeObject = (SubCarroFacade) aObject;
			boolean lEquals = true;
			lEquals &= ((this._carros == lSubCarroFacadeObject._carros)
				|| (this._carros != null && this._carros.equals(lSubCarroFacadeObject._carros)));
			return lEquals;
		}
		return false;
	}

    public static SubCarroFacade getInstance() {
        return null;
    }

	@Override
	public Carro getCarro(String id) {
		return _carros.get(id);
	}

	@Override
	public List<Carro> listCarros() {
		List<Carro> carros = new ArrayList<>(_carros.values());
		return carros;
	}

	@Override
	public boolean hasCarro(String id) {
		return _carros.containsKey(id);
	}
}