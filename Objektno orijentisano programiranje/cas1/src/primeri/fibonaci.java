package primeri;

import java.util.Scanner;

public class fibonaci {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Unesite broj: ");
		if(sc.hasNextInt()){
			int x = sc.nextInt();
			System.out.println("Fibonaci iterativno: " + iterativni(x));
			System.out.println("Fibonaci rekurzivno: " + rekurzivno(x));
		}
	}

	private static int rekurzivno(int x){
		if(x == 2 || x == 1){
			return 1;
		}

		return rekurzivno(x-2) + rekurzivno(x-1);
	}

	private static int iterativni(int x){
		int fib = 1, prevFib = 1;
		for (int i = 2; i < x; i++) {
			int tmp = fib;
			fib += prevFib;
			prevFib = tmp;
		}

		return fib;
	}
}
