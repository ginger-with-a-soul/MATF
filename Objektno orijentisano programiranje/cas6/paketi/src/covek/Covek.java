package covek;

public class Covek implements SrpskiJezik, EngleskiJezik{
	private String ime, prezime;
	private int godine;

	public Covek(String ime, String prezime, int godine) {
		this.ime = ime;
		this.prezime = prezime;
		this.godine = godine;
	}

	public String getIme() {
		return ime;
	}

	public String getPrezime() {
		return prezime;
	}

	public int getGodine() {
		return godine;
	}

	@Override
	public String hello() {
		return "Hello :)";
	}

	@Override
	public String goodbye() {
		return "Goodbye :)";
	}

	@Override
	public String thank_you() {
		return "Thank you :)";
	}

	@Override
	public String thanks() {
		return "Thanks :)";
	}

	@Override
	public String zdravo() {
		return "Zdravo :D";
	}

	@Override
	public String dovidjenja() {
		return "Dovidjenja :D";
	}

	@Override
	public String zahvaljujem() {
		return "Zahvaljujem :D";
	}

	@Override
	public String hvala() {
		return "Hvala :D";
	}
}
