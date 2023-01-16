package EntregaFinal.src.SubContas;

public enum userType {
	Administrador(0), JogadorBase(1), JogadorPremium(2);
	public int num;
	userType(int num){
		this.num = num;
	}

	public static userType fromInt(int i){
		return switch (i){
			case 0 -> Administrador;
			case 1 -> JogadorBase;
			case 2 -> JogadorPremium;
			default -> throw new IllegalStateException("Unexpected value: " + i);
		};
	}
}