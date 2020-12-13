package Tacka;

import java.util.Scanner;

public class Main {

	private static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		System.out.println("Input the number of points: ");
		int n = sc.nextInt();

		Tacka t0 = new Tacka();
		Tacka[] tacke = new Tacka[n-1];

		for (int i = 0; i < n - 1; i++) {
			tacke[i] = new Tacka(sc.nextDouble(), sc.nextDouble());
		}

		for(Tacka t : tacke){
			System.out.println(t + " " + t.euklidskoRastojanje(t0));
		}

		t0.translirajVertikalno(2);
		t0.transliranHorizontalno(3);

		System.out.println(t0);
	}
}
