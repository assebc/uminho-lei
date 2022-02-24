import java.util.Scanner;

public class Ficha01{

	public static void Exercicio1(){

		Scanner input = new Scanner(System.in);
		System.out.println("Introduza o dia");
		int dia = input.nextInt();
		System.out.println("Introduza o mes");
		int mes = input.nextInt();
		System.out.println("Introduza o ano");
		int ano = input.nextInt();

		int res = (ano-1900)*365 + (ano-1900)/4;
		if (ano%4 == 0 && (ano%100 != 0 && ano%400 != 0)){
			if(mes<=1) res -= 1;
		}

		for(int i = 1;i<mes;i++){
			if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) res+=31;
			else if(i == 4 || i == 6 || i == 9 || i == 11) res += 30;
			else res += 28;

		}

		res += dia;
		int dsem = res%7;
		switch(dsem){
			case 0:
				System.out.println("Domingo");
				break;
			case 1:
				System.out.println("Segunda");
				break;
			case 2:
				System.out.println("Terça");
				break;
			case 3:
				System.out.println("Quarta");
				break;
			case 4:
				System.out.println("Quinta");
				break;
			case 5:
				System.out.println("Sexta");
				break;
			case 6:
				System.out.println("Sabado");
				break;
		}
	}

	public static double CelsiusParaFarenheit(double graus){

		double farenheit = graus * 33.8;
		System.out.println("Celsius "+graus);
		System.out.println("Farenheit "+farenheit);
		return farenheit;

	}

	public static int MaximoNumeros(int a, int b){

		if(a>b){
			System.out.println("O maior é "+a);
			return a;
		} else if (b>a){
			System.out.println("O maior é "+b);
			return b;
		} else {
			System.out.println("São iguais");
			return a;
		}

	}

	public static void main(String[] args){
		//Exercicio1();
		//CelsiusParaFarenheit(2);
		//MaximoNumeros(20,30);
	}
}