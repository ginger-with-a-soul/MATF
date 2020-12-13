public class Main {

	public static void main(String[] args) {
		Tacka kP = new Tacka();
		Pravougaonik p = new Pravougaonik(kP, 5, 7);
		Kvadrat k = new Kvadrat(5);
		System.out.println(p);
		System.out.println(k);
	}
}
