package ozvucenje;

public class Prostorija {
	private String naziv;
	private double duzina, sirina, povrsina;

	public Prostorija(String naziv, double duzina, double sirina) {
		this.naziv = naziv;
		this.duzina = duzina;
		this.sirina = sirina;
		this.povrsina = duzina * sirina;
	}

	public String getNaziv() {
		return naziv;
	}

	public double getDuzina() {
		return duzina;
	}

	public double getSirina() {
		return sirina;
	}

	@Override
	public String toString() {
		return "Prostorija " + getNaziv() + " povrsine " + povrsina + "m^2";
	}
}
