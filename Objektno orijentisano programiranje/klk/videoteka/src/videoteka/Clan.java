package videoteka;

public class Clan {
	private String ime, omiljeni_zanr;

	public Clan(String ime, String omiljeni_zanr) {
		this.ime = ime;
		this.omiljeni_zanr = omiljeni_zanr;
	}

	public String getIme() {
		return ime;
	}

	public String getOmiljeni_zanr() {
		return omiljeni_zanr;
	}

	@Override
	public String toString() {
		return "Ime: " + ime + "; Omiljeni zanr: " + omiljeni_zanr;
	}
}
