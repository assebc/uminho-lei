import java.util.Arrays;
import java.util.ArrayList;
import java.util.Scanner;

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


	public static void Exercicio2(){
		int [][] notasTurma = new int [5][5]; // i alunos j cadeiras

		System.out.println("Nota");
		Scanner input = new Scanner(System.in);
		int base = input.nextInt();
		for(int i = 0;i<5;i++){
			for(int j = 0;j<5;j++){
				notasTurma[i][j] = base;
				
			}
			System.out.println(Arrays.toString(notasTurma[i]));
			base++;
		}

		
		System.out.println("Determina UC entre 0 e menor que 5");
		int uc = input.nextInt();
		int med = 0;
		for(int j = 0;j<5;j++) med += notasTurma[uc][j];
		med /= 5;
		System.out.print("Media da uc " +uc); // concat 1
		System.out.println(" é "+med); // concat 2

		System.out.println("Determina aluno entre 0 e menor que 5");
		int aluno = input.nextInt();
		int med_aluno = 0;
		for(int j = 0;j<5;j++) med_aluno += notasTurma[aluno][j];
		med_aluno /= 5;
		System.out.print("Media do aluno " +aluno); // concat 1
		System.out.println(" é "+med_aluno); // concat 2

		

		int max = 0, ucB = 0, alunoB = 0;
		for(int i = 0;i<5;i++){
			for(int j = 0;j<5;j++){
				if (notasTurma[i][j] > max){
					max = notasTurma[i][j];
					alunoB = i;
					ucB = j;
				}
			}
		}
		System.out.print("A maior nota é a "+ ucB);
		System.out.print(" do "+ alunoB);
		System.out.println(" e é "+max);

		int small = 20, ucS = 0, alunoS = 0;
		for(int i = 0;i<5;i++){
			for(int j = 0;j<5;j++){
				if (notasTurma[i][j] < small){
					small = notasTurma[i][j];
					alunoS = i;
					ucS = j;
				}
			}
		}
		System.out.print("A menor nota é a "+ ucS);
		System.out.print(" do "+ alunoS);
		System.out.println(" e é "+small);
		

		int [] aux = new int [25];
		System.out.println("Acima de?");
		int limit = input.nextInt();
		int ocorr = 0, rind = 0;
		for(int i = 0;i<5;i++){
			for(int j = 0;j<5;j++){
				if(notasTurma[i][j]>limit){
					ocorr++;
					aux[rind++] = notasTurma[i][j];
				}
			}
		}
		int [] result = new int [ocorr];
		for(int i = 0;i<ocorr;i++) result[i] = aux[i];
		System.out.println(Arrays.toString(result));
		
		float mediaUc = 0, ucs = 0;
		int ind = 0;
		for(int i = 0;i<5;i++){
			for(int j = 0;j<5;j++){
				ucs += notasTurma[i][j];
			}
			if(ucs/5 > mediaUc){
				mediaUc = ucs/5;
				ind = i;
			}
			ucs = 0;
		}
		System.out.print("Maior média é " +ind);
		System.out.println(" com "+mediaUc);


		input.close();
	}

	public static void swap(int [] array, int i, int j){
		int tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}

	public static void Exercicio3(){

		int [] array = {10, 32, 21, 54, 13, 16}; // 10 13 16 21 32 54
		System.out.println(Arrays.toString(array));
		for(int i = 0;i<array.length-1;i++){
			for(int j = i+1;j<array.length;j++){
				if(array[i]>array[j]) swap(array,j,i);
			}
		}
		System.out.println(Arrays.toString(array));
		Scanner input = new Scanner(System.in);
		System.out.println("Diga 2 indices");
		int a = input.nextInt();
		int b = input.nextInt();

		int [] sub_array = new int [b-a+1];
		int indsub = 0;
		for(int i = a;i<b+1;i++){
			sub_array[indsub++] = array[i];
		}

		System.out.println(Arrays.toString(sub_array));
		input.close();

	}

	public static boolean searchFor(Object a, Object [] as){

		for(int i = 0;i<as.length;i++){
			if (a == as[i]) return true;
		}

		return false;
	}

	public static Object [] sem_repetidos(Object [] a){

		Object [] aux = new Object [a.length];
		int aind = 0;
		for(int i = 0;i<a.length;i++){
			if(!searchFor(a[i],aux)) aux[aind++] = a[i];
		}
		Object [] sem_repetidos = new Object [aind];
		for(int i = 0;i<aind;i++){
			sem_repetidos[i] = aux[i];
		}

		System.out.println("array -> " +Arrays.toString(a));
		System.out.println("sem_repetidos -> " +Arrays.toString(sem_repetidos));
		

		return sem_repetidos;
	}

	public static Object [] repetidos(Object [] a){

		Object [] aux = new Object [a.length];
		int aind = 0, aiai = 0;
		for(int i = 0;i<a.length;i++){
			if(searchFor(a[i],aux)){
				aux[aind++] = a[i];
				aiai++;
			}
		}
		Object [] repetidos = new Object [aind];
		for(int i = 0;i<aind;i++){
			repetidos[i] = aux[i];
		}

		System.out.println("array -> " +Arrays.toString(a));
		System.out.println("repetidos -> " +Arrays.toString(repetidos));
		System.out.println("repetidos são -> " +aiai);
		

		return repetidos;
	}

	public static void Exercicio5(){

		Scanner input = new Scanner(System.in);
		System.out.println("Quantas STRINGS pretende ter?");
		int size = input.nextInt();
		String [] array = new String [size];
		int ind = 0;
		while(size>0){
			array[ind++] = input.next();
			size--;
		}

		Object [] result = sem_repetidos(array); // smth is wrong here

		int big_string = 0;
		for(int i = 0;i<array.length;i++){
			if(array[i].length()>big_string) big_string = array[i].length();
		}
		System.out.println("maior -> " +big_string);

		Object [] result_2 = repetidos(array); // smth is wrong here

	}

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

			case 5 :
			Exercicio5();
			break;


		}
	}
}