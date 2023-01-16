package EntregaFinal.src.SubSimulacao;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class EstadoPremium {
	private Map<String,EstadoJogadorPremium> _estadosJogadoresMap = new HashMap<>();

	public EstadoJogadorPremium getEstadoJogador(String aJogadorID) {
		return this._estadosJogadoresMap.get(aJogadorID);
	}

	public EstadoPremium(Set<String> jogadoresID){
		for(String jogadorID : jogadoresID){
			_estadosJogadoresMap.put(jogadorID,new EstadoJogadorPremium());
		}
	}

	public Map<String, EstadoJogadorPremium> get_estadosJogadoresMap() {
		return _estadosJogadoresMap;
	}

	public void set_estadosJogadoresMap(Map<String, EstadoJogadorPremium> _estadosJogadoresMap) {
		this._estadosJogadoresMap = _estadosJogadoresMap;
	}
	
	public int hashCode() {
		int lHashCode = 0;
		if ( this._estadosJogadoresMap != null ) {
			lHashCode += this._estadosJogadoresMap.hashCode();
		}
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	public boolean equals(Object aObject) {
		if (this == aObject) {
			return true;
		} else if (aObject instanceof EstadoPremium) {
			EstadoPremium lEstadoPremiumObject = (EstadoPremium) aObject;
			boolean lEquals = true;
			lEquals &= ((this._estadosJogadoresMap == lEstadoPremiumObject._estadosJogadoresMap)
				|| (this._estadosJogadoresMap != null && this._estadosJogadoresMap.equals(lEstadoPremiumObject._estadosJogadoresMap)));
			return lEquals;
		}
		return false;
	}
}