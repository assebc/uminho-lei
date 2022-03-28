package task1;

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
			//System.out.println("O maior é "+a);
			return a;
		} else if (b>a){
			//System.out.println("O maior é "+b);
			return b;
		} else {
			//System.out.println("São iguais");
			return a;
		}

	}

	public static String CriaDescricaoConta(String nome, double saldo){

		String res = nome + " " + saldo;
		System.out.println(res);
		return res;

	}

	public static double EurosParaLibras(double valor, double taxaConversao){

		double res = valor * taxaConversao;
		System.out.println(res);
		return res;
	}
	public static void Readints(){

		Scanner input = new Scanner(System.in);
		int x = input.nextInt();
		int y = input.nextInt();
		float med = (float) (x+y)/2;
		if (MaximoNumeros(x,y) == x){
			String opt1 = x + " " + y;
			System.out.println(opt1);
			System.out.println("A média é "+med);
		} else {
			String opt2 = y + " " + x;
			System.out.println(opt2);
			System.out.println("A média é "+med);
		}

	}

	public static long Factorial(String[] args){

		int num = Integer.parseInt(args[0]);
		long res = 1;
		while(num>0){
			res *= num;
			num--;
		}
		System.out.println("Fatorial é "+res);
		return res;
	}

	public static long TempoGasto(String[] args){

		long start = System.currentTimeMillis();
		Factorial(args);
		long finish = System.currentTimeMillis();
		long time = finish - start;
		String ans = "Demorou cerca de " + time + " milisegundos";
		System.out.println(ans);
		return time;
	}

	public static void main(String[] args){
		Exercicio1();
		CelsiusParaFarenheit(2);
		MaximoNumeros(20,30);
		CriaDescricaoConta("Matilde", 11.11);
		EurosParaLibras(10, 0.84);
		Readints();
		Factorial(args);
		TempoGasto(args);
	}
}