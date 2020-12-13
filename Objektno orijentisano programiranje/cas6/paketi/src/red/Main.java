package red;

import java.util.Scanner;

public class Main {
	public static void prikaziOpcije(){
		System.out.println("Izaberite opciju: 0 - exit, 1 - push, 2 - pop, 3 - front, 4 - size, 5 - show");
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Niz red = new Niz();

		prikaziOpcije();
		Operacija o = Operacija.fromInt(sc.nextInt());

		while(o != Operacija.EXIT){
			switch(o){
				case PUSH: System.out.println("Unesite red koji zelite da ubacite: "); red.push(sc.nextInt()); break;
				case POP: red.pop(); break;
				case FRONT: red.front(); break;
				case SIZE: red.size(); break;
				case SHOW: red.show(); break;
			}
			prikaziOpcije();
			o = Operacija.fromInt(sc.nextInt());
		}
	}
}
