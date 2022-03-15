import java.time.LocalTime;
import java.util.Date;
import java.lang.Math;

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


		public Telemovel(){
			this.marca = "Apple";
			this.modelo = "Iphone";
			this.display = "1920x1080";
			this.dimensao_msg = null;
			this.dimensao_fotos_apk = "0";
			this.dimensao_fotos = null;
			this.dimensao_apk = null;
			this.espaco_total = 256000;
			this.fotos = 0;
			this.apk = 0;
			this.apk_ins = null;

		}

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

	public class Youtube{

		private String name;
		private String content;
		private String date;
		private String resolution;
		private Double duration;
		private String [] comments;
		private Integer likes;
		private Integer dislikes;

		public Youtube(){
			this.name = null;
			this.content = null;
			this.date = null;
			this.resolution = null;
			this.resolution = null;
			this.duration = 0.0;
			this.comments = null;
			this.likes = 0;
			this.dislikes = 0;
		}

		public void insereComentario(String comentario){
			this.comments[this.comments.length] = comentario;
		}

		public void thumbsUp(){
			this.likes++;
		}

		public String processa(){
			System.out.println(this.content);
			return this.content;
		}


	}

	public class Lampada{

		private Byte on_off_eco;
		private Double consume;
		private long[] start_on;
		private long[] start_eco;
		private long[] start_off;
		private Double all_consume;

		public Lampada(){
			this.on_off_eco = 0; // 0 - off 1 - on 2 - eco
			this.consume = 0.0; // 0 - off 1 - eco 5 - on
			this.start_on = null;
			this.start_eco = null;
			this.start_off = null; // default começa desligada
			this.all_consume = 0.0;
		}

	}

	public class Futebol{

		private String visitado;
		private String visitante;
		private Byte status; // 0 - not started 1 - playing 2 - ended
		private Byte events; // 0 - to start 1 - goals 2 - resultado
		private Integer [] resultado;

		public Futebol(){
			this.visitado = null;
			this.visitante = null;
			this.status = 0;
			this.events = 1;
			this.resultado = null;
		}

		public void startGame(){
			this.status = 1;
			this.events = 1;
		}

		public void endGame(){
			this.status = 2;
			this.events = 1;
		}

		public void goloVisitado(){
			this.resultado[0] += 1;
		}

		public void goloVisitante(){
			this.resultado[1] +=1;
		}

		public String resultadoAtual(){
			return this.resultado[0] + "X" + this.resultado[1];
		}


	}

	public class Carro{


		private String brand;
		private String model;
		private Date built;
		private Double consume;
		private Double kms;
		private Double avg_consume;
		private Double kms_last;
		private Double avg_last;
		private Double regen;
		private Byte status;


		public Carro(){
			this.brand = null;
			this.model = null;
			this.built = null;
			this.consume = 0.0;
			this.kms = 0.0;
			this.avg_consume = 0.0;
			this.kms_last = 0.0;
			this.avg_last = 0.0;
			this.regen = 0.0;
			this.status = 0; // 0 - off 1 - on
		}

		public void ligaCarro(){
			this.status = 1;
		}

		public void desligaCarro(){
			this.status = 0;

		}

		public void resetUltimaViagem(){
			this.kms_last = 0.0;
			this.avg_last = 0.0;
		}

		public void avancaCarro(double metros, double velocidade){
			Double kms = (metros * velocidade)/1000;
			this.kms_last += kms;
		}

		public void travaCarro(double metros){
			this.kms_last += metros/1000;
			this.regen += metros/1000;

		}

	}

	public class Linha_Encomenda{

		private String code;
		private String description;
		private Double price_pv;
		private Double amount;
		private Double iva;
		private Double promo;

		public Linha_Encomenda(){
			this.code = null;
			this.description = null;
			this.price_pv = 0.0;
			this.amount = 0.0;
			this.iva = 0.0;
			this.promo = 0.0;
		}

		public double calculaValorLinhaEnc(){
			double percentage = (this.iva - this.promo)/100;
			double final_price = this.price_pv+(this.price_pv*percentage);
			return final_price;
		}

		public double calculaValorDesconto(){
			double final_price = this.price_pv-(this.price_pv*(this.promo/100));
			return  calculaValorLinhaEnc() - final_price;
		}

	}

	public class Encomenda{

		private String name_client;
		private Integer num_fiscal_client;
		private String address_client;
		private Integer num_package;
		private Date package_date;
		private Linha_Encomenda [] linha_encomenda;

		public Encomenda(){
			this.name_client = null;
			this.num_fiscal_client = 0;
			this.address_client = null;
			this.num_package = 0;
			this.package_date = null;
			this.linha_encomenda = null;
		}

		Linha_Encomenda le1 = new Linha_Encomenda();

		public double calculaValorTotal(){
			return le1.calculaValorLinhaEnc();
		}

		public double calculaValorDesconto(){
			return le1.calculaValorDesconto();
		}

		public int numeroTotalProdutos(){
			int pack = 0;
			for(int i = 0;i<this.linha_encomenda.length;i++) pack++;
			return pack;
		}

		public boolean existeProdutoEncomenda(String refProduto){
			for(int i = 0;i<this.linha_encomenda.length;i++){
				if(refProduto == this.linha_encomenda[i].code) return true;
			}
			return false;
		}

		public void adicionaLinha(Linha_Encomenda linha){
			this.linha_encomenda[this.linha_encomenda.length] = linha;
		}

		public void removeProduto(String codProd){
			for(int i = 0;i<this.linha_encomenda.length;i++){
				if(this.linha_encomenda[i].code == codProd){
					this.linha_encomenda[i] = this.linha_encomenda[this.linha_encomenda.length-1];
					break;
				}
			}
		}
	}

	public static void main(String [] args){

		Ficha03 f1 = new Ficha03();
		Ficha03.Circulo c1 = f1.new Circulo();

		Ficha03.Telemovel t1 = f1.new Telemovel();

		Ficha03.Youtube y1 = f1.new Youtube();

		Ficha03.Lampada l1 = f1.new Lampada();

		Ficha03.Futebol fut1 = f1.new Futebol();

		Ficha03.Carro car1 = f1.new Carro();

		Ficha03.Linha_Encomenda le1 = f1.new Linha_Encomenda();

		Ficha03.Encomenda e1 = f1.new Encomenda();
	}

}

