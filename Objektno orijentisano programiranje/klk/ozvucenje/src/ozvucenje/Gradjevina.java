package ozvucenje;

import java.util.Scanner;

public class Gradjevina {
	public static void main(String[] args) {
		Zvucnik[] z = {new Zvucnik("Yamaha", "HS8", 75), new Zvucnik("Yamaha", "HS7", 60),
				new Zvucnik("Logitec", "Z313", 25)};

		System.out.println(z[1].toString());

		z[1].switchOnOff();

		System.out.println(z[1].toString());

		Scanner sc = new Scanner(System.in);

		Skladiste s = new Skladiste(sc.next(), sc.nextDouble(), sc.nextDouble(), sc.nextDouble());

		System.out.println(s.toString());

		s.dodajPalete(8); s.dodajPalete(4); s.dodajPalete(2); s.dodajPalete(2);

		MuzickaSala ms = new MuzickaSala(sc.next(), sc.nextDouble(), sc.nextDouble(), sc.nextInt(), z);

		System.out.println(ms.toString());
	}
}
