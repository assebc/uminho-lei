package task3.src.SubCarros;

import java.util.ArrayList;
import java.util.List;

import task3.src.data.CarroDAO;

public class SubCarroFacade implements ISubCarro {
	private CarroDAO _carros;

	@Override
	public boolean categoriaValida(String aC) {
		if(aC == "C1" || aC == "c1" || aC == "C2"|| aC == "c2" || aC == "GT" || aC == "gt" || aC == "SC" || aC == "sc")
			return true;
		return false;
	}

	@Override
	public boolean fiabilidadeValida(int aF) {
		if(0 < aF && aF < 100)
			return true;
		return false;
	}

	@Override
	public void registarCarro(Carro aCarro) {
		String id = String.valueOf(_carros.size());
		aCarro.set_iD(id);
		this._carros.put(id,aCarro);
	}

	@Override
	public boolean cilindradaValida(int aCilindrada, String aCategoria) {
		boolean b = false;
		if((aCategoria == "C1" || aCategoria == "c1") && (aCilindrada == 6000) )
			b = true;

		if((aCategoria == "C2" || aCategoria == "c2") && (2000 <= aCilindrada) && (aCilindrada <= 4000))
			b = true;

		if((aCategoria == "GT" || aCategoria == "gt") && (3000 <= aCilindrada) && (aCilindrada <= 5000))
			b = true;

		if((aCategoria == "SC" || aCategoria == "sc") && (aCilindrada == 2500) )
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