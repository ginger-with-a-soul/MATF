package izraz;

import java.util.Scanner;

public class Main {

	private static Scanner sc = new Scanner(System.in);
	static double x = sc.nextDouble(), y = sc.nextDouble(), z = sc.nextDouble();

	private static Izraz prviIzraz(){

		Broj b1 = new Broj(x);
		Broj b2 = new Broj(y);
		Sabiranje s = new Sabiranje(b1, b2);
		return s;
	}

	private static Izraz drugiIzraz(){
		Broj b1 = new Broj(x);
		Broj b2 = new Broj(y);
		Broj b3 = new Broj(z);

		Mnozenje m = new Mnozenje(b1, b2);

		return m;
	}

	private static Izraz treciIzraz(){
		Broj b1 = new Broj();
		Promenljiva x1 = new Promenljiva("x1", 2);
		Promenljiva gen = new Promenljiva();

		Oduzimanje o = new Oduzimanje(gen, x1);
		System.out.println(o.izracunaj() + "");

		Mnozenje m = new Mnozenje(b1, o);

		return m;
	}

	public static void main(String[] args) {
		Izraz i1 = prviIzraz();
		System.out.println(i1 + " = " + i1.izracunaj());
		Izraz i2 = drugiIzraz();
		System.out.println(i2 + " = " + i2.izracunaj());
		Izraz i3 = treciIzraz();
		System.out.println(i3 + " = " + i3.izracunaj());
	}
}
