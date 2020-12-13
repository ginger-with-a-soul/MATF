package ozvucenje;

public class Skladiste extends Prostorija {
	private double preostaloMesta, stranicaPalete, paleta;

	public Skladiste(String naziv, double duzina, double sirina, double stranicaPalete) {
		super(naziv, duzina, sirina);
		this.stranicaPalete = stranicaPalete;
		this.preostaloMesta = getDuzina() * getSirina();
		this.paleta = stranicaPalete * stranicaPalete;
	}

	public double getPreostaloMesta() {
		return preostaloMesta;
	}

	public double getStranicaPalete() {
		return stranicaPalete;
	}

	public void setPreostaloMesta(double preostaloMesta) {
		this.preostaloMesta = preostaloMesta;
	}

	public void setStranicaPalete(double stranicaPalete) {
		this.stranicaPalete = stranicaPalete;
	}

	void dodajPalete(int brojPaleta){
		if(preostaloMesta / paleta >= brojPaleta){
			System.out.println("Uspesno su smestene sve palete!");
			preostaloMesta -= brojPaleta*paleta;
		}
		else if(preostaloMesta < paleta){
			System.out.println("Neuspesno smestanje, skladiste je puno!");
		}
		else{
			System.out.println("Uspesno je smesteno " + Math.floor(preostaloMesta/paleta) + " od " + brojPaleta + " paleta.");
			preostaloMesta = 0;
		}
	}

	@Override
	public String toString() {
		return "Skladiste " + getNaziv() + " povrsine " + getSirina() * getDuzina() + "m^2 (slobodno " + getPreostaloMesta() + "m^2).";
	}
}
