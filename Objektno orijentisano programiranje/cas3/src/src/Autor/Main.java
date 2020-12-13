package Autor;

import java.util.Scanner;

public class Main {

	private static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		System.out.println("Input the number of authors: ");
		int i = sc.nextInt();
		Autor[] autori = new Autor[i];
		for (int j = 0; j < i; j++) {
			autori[j] = new Autor(sc.next(), sc.next(), sc.nextInt());
		}

		for(Autor a : autori){
			System.out.println(a);
			System.out.println(a.getGodine());
		}

	}
}
