package task3.src.SubContas;

public enum userType {
	Administrador(0), JogadorBase(1), JogadorPremium(2);
	public int num;
	userType(int num){
		this.num = num;
	}

	public static userType fromInt(int i){
		switch (i){
			case 0: return Administrador;
			case 1: return JogadorBase;
			case 2: return JogadorPremium;
			default: throw new IllegalStateException("Unexpected value: " + i);
		}
	}
}