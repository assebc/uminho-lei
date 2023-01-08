package task3.src.SubContas;

import task3.src.data.ContasDAO;

public class SubContasFacade implements ISubContas {
	private ContasDAO _contas = ContasDAO.getInstance();

	public boolean nomeDisponivel(String aNome) {
		return !this._contas.containsKey(aNome);
	}

	public void registarConta(String aNome, String aPassword, userType aType) {
		this._contas.put(aNome, new Conta(aNome,aPassword,aType));
	}

	public boolean validarConta(String aNome, String aPassword) {
		if(_contas.containsKey(aNome) && _contas.get(aNome).get_password()==aPassword) return true;
		else return false;
	}

	public userType autenticarConta(String aNome) {
		return _contas.get(aNome).get_type();
	}

	public void atribuirPontos(String aNome, Integer aPontos) {
		Conta c = _contas.get(aNome);
		int p = c.get_pontos() + aPontos;
		c.set_pontos(p);
	}

	public int hashCode() {
		int lHashCode = 0;
		if ( this._contas != null ) {
			lHashCode += this._contas.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof SubContasFacade) {
			SubContasFacade lSubContasFacadeObject = (SubContasFacade) aObject;
			boolean lEquals = true;
			lEquals &= ((this._contas == lSubContasFacadeObject._contas)
				|| (this._contas != null && this._contas.equals(lSubContasFacadeObject._contas)));
			return lEquals;
		}
		return false;
	}
}