package stek;

import java.util.Scanner;

public class Main {
	public static void prikaziInstrukciju(){
		System.out.println("Unesite operaciju: 0 - exit, 1 - push, 2 - pop, 3 - top, 4 - show, 5 - size");
	}

	public static void main(String[] args) {

		Niz s = new Niz();
		Scanner sc = new Scanner(System.in);
		prikaziInstrukciju();
		Operacija o = Operacija.values()[sc.nextInt()];
		while(o != Operacija.EXIT){
			switch (o){
				case PUSH:
					System.out.println("Unesite vrednost za push: ");
					s.push(sc.nextInt());
					break;
				case POP:
					s.pop();
					break;
				case TOP:
					s.top();
					break;
				case SHOW:
					s.show();
				case SIZE:
					s.size();
					break;
			}
			prikaziInstrukciju();
			o = Operacija.values()[sc.nextInt()];
		}
	}
}
