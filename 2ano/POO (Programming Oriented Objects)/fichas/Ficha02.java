import java.util.Arrays;
import java.util.Scanner;
import java.lang.Math;

public class Ficha02{

	public static void Exercicio1(){
	
		Scanner input = new Scanner(System.in);

		System.out.println("Qual a dimensão do array?");
		int size = input.nextInt();
		int min = 0;
		int [] array = new int [size];

		for(int i = 0;i<array.length;i++){
			if (i==0){
				min = input.nextInt();
				array[i] = min;
			}
			else{
				int value = input.nextInt();
				if (min > value) min = value;
				array[i] = value;
			}
		}

		System.out.println("O menor valor é "+min);

		System.out.println("Diga dois indices entre 0 e menores que " +size);
		int a = input.nextInt();
		int b = input.nextInt();
		int size_subarray = b-a+1;
		int [] subarray = new int [size_subarray];
		int ind = 0;
		for(int j = a;j<b+1;j++)
			subarray[ind++] = array[j];
			
		String string_subarray = Arrays.toString(subarray);
		System.out.println(string_subarray);

		int ind2 = 0, rind = 0;
		System.out.println("Diga o size do array");
		int result_size = input.nextInt();

		int [] result = new int [result_size];
		for(int h = 0;h<subarray.length;h++){
			while(ind2<array.length){
				if(subarray[h] != array[ind2++]) continue;
				else{
					result[rind++] = subarray[h];
					ind2 = 0;
					break;
				}
			}
			
		}

		String result_string = Arrays.toString(result);
		System.out.println(result_string);

		input.close();

	}


	public static void Exercicio2(){}
	public static void Exercicio3(){}
	public static void Exercicio4(){}
	public static void Exercicio5(){}
	public static void Exercicio6(){}
	public static void Exercicio7(){}


	public static void main(String [] args){

		switch(Integer.parseInt(args[0])){

			case 1 :
			Exercicio1();
			break;

			case 2 :
			Exercicio2();
			break;

			case 3 :
			Exercicio3();
			break;

			case 4 :
			Exercicio4();
			break;

			case 5 :
			Exercicio5();
			break;

			case 6 :
			Exercicio6();
			break;

			case 7 :
			Exercicio7();
			break;


		}
	}
}