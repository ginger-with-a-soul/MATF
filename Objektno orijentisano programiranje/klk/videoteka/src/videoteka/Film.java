package videoteka;

public class Film {
	private String naziv, zanr;
	private double ocena;
	private boolean iznajmljen;

	public Film(String naziv, String zanr, double ocena) {
		this.naziv = naziv;
		this.zanr = zanr;
		this.ocena = ocena;
		this.iznajmljen = false;
	}

	public Film(Film f){
		this.naziv = f.naziv;
		this.zanr = f.zanr;
		this.ocena = f.ocena;
		this.iznajmljen = f.iznajmljen;
	}

	public String getNaziv() {
		return naziv;
	}

	public String getZanr() {
		return zanr;
	}

	public double getOcena() {
		return ocena;
	}

	public boolean isIznajmljen() {
		return iznajmljen;
	}

	public void setIznajmljen(boolean iznajmljen) {
		this.iznajmljen = iznajmljen;
	}

	@Override
	public String toString() {
		return "Naziv: " + naziv + "; Zanr: " + zanr + "; Ocena: " + ocena;
	}
}
