package Stek;

import Stek.tacka;

public class main {

	public static void main(String[] args) {
		matfStek<tacka> tacke = new matfStek<>();
		int n = 5;
		for (int i = 0; i < n; i++) {
			tacke.push(new tacka(i, n+i));
		}
		System.out.println(tacke);
		System.out.println(tacke.peek());
		System.out.println(tacke.pop());
		System.out.println(tacke.peek());
		tacke.push(new tacka(22, 33));
		System.out.println(tacke.peek());
	}
}
