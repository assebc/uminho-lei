public class Ficha03{
	public class Circulo {

		private double x;
		private double y;
		private double raio;


		public Circulo(){
			this.x = 0;
			this.y = 0;
			this.raio = 1;
		}

		public Circulo(double cx, double cy, double craio){
			this.x = cx;
			this.y = cy;
			this.raio = craio;
		}

		public double getX(){
			return this.x;
		}

		public double getY(){
			return this.y;
		}

		public double getRaio(){
			return this.raio;
		}


		public void setX(double x){
			this.x = x;
		}

		public void setY(double y){
			this.y = y;
		}

		public void setRaio(double raio){
			this.raio = raio;
		}

		public void alteraCentro(double x, double y){
			setX(x);
			setY(y);
		}

		public double calculaArea(){
			return 3.14*(this.raio)*(this.raio);
		}

		public double calculaPerimetro(){
			return 3.14*2*this.raio;
		}

		public boolean equals(Object o){
			if(this == o) return true;
			if((o == null) || (this.getClass() != o.getClass())) return false;
			Circulo c = (Circulo) o;
			return (this.x == c.getX() && this.y == c.getY() && this.raio == c.getRaio());
		}

		public String toString(){
			return "Cx = " +this.x + " - Cy = " +this.y + "- Raio = " +this.raio;
		}

		public Circulo clone(){
			return new Circulo();
		}
	}
	public class Telemovel{

		private String marca;
		private String modelo;
		private String display;
		private String [] dimensao_msg;
		private String dimensao_fotos_apk;
		private String [] dimensao_fotos;
		private String [] dimensao_apk;
		private int espaco_total;
		private int fotos;
		private int apk;
		private String [] apk_ins;


		public boolean existeEspaco(int numeroBytes){
			int dims = 0;
			for(int i = 0;i<this.dimensao_msg.length;i++) dims += Integer.parseInt(this.dimensao_msg[i]);
			int total = Integer.parseInt(this.dimensao_fotos_apk) + dims + numeroBytes;
			int left = this.espaco_total - total;
			if (left == 0) return false;

			return true;
		}

		public void instalaApp(String nome, int tamanho){
			if(existeEspaco(tamanho) == true){
				this.dimensao_fotos_apk = Integer.toString(Integer.parseInt(this.dimensao_fotos_apk) + tamanho);
				int dims = 0;
				for(int i = 0;i<this.dimensao_apk.length;i++) dims += Integer.parseInt(this.dimensao_apk[i]);
				this.dimensao_apk[this.dimensao_apk.length] = Integer.toString(tamanho);
				this.apk_ins[this.apk++] = nome;
			}
		}

		public void recebeMsg(String msg){
			this.dimensao_msg[this.dimensao_msg.length] = Integer.toString(msg.length());
		}

		public double tamMedioApps(){
			double med = 0;
			for(int i = 0;i<this.dimensao_apk.length;i++) med += Double.parseDouble(this.dimensao_apk[i]);
			med = med / dimensao_apk.length;
			return med;
		}

		public String maiorMsg(){
			int maior = 0;
			for(int i = 0;i<this.dimensao_msg.length;i++) if(maior<Integer.parseInt(dimensao_msg[i])) maior = Integer.parseInt(dimensao_msg[i]);
			return Integer.toString(maior);
		}

		public void removeApp(String nome, int tamanho){
			int j = 0;
			for(int i = 0;i<this.apk_ins.length;i++)
				if(nome == this.apk_ins[i])
					this.apk_ins[i] = this.apk_ins[this.apk_ins.length-1];
			this.dimensao_fotos_apk = Integer.toString(Integer.parseInt(dimensao_fotos_apk)-tamanho);
			
		}

	}

	public static void main(String [] args){

	}

}

