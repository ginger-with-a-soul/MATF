package covek;

public class Main {
	public static void main(String[] args) {
		Covek c = new Covek("Dimitrije", "Stankov", 20);
		System.out.println(c.thank_you());
		EngleskiJezik ej = c;
		System.out.println(c.getGodine());
		ej.goodbye();
		SrpskiJezik sj = c;
		if(ej instanceof EngleskiJezik) {
			System.out.println("Dimitrije says " + ej.hello());
		}
	}
}
