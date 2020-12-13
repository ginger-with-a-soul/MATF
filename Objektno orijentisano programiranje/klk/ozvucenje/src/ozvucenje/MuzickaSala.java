package ozvucenje;

public class MuzickaSala extends Prostorija {
	private int brMesta;
	private boolean[] mesta = new boolean[brMesta];
	private Zvucnik[] ozvucenje;
	private static int brojac = 0;
	private double power = 1.0;

	static int brojInstanci(){
		return brojac;
	}

	public MuzickaSala(String naziv, double duzina, double sirina, int brMesta, Zvucnik[] ozvucenje) {
		super(naziv, duzina, sirina);
		this.brMesta = brMesta;
		this.ozvucenje = ozvucenje;
		java.util.Arrays.fill(mesta, false);
	}

	public int getBrMesta() {
		return brMesta;
	}

	public boolean[] getMesta() {
		return mesta;
	}

	public Zvucnik[] getOzvucenje() {
		return ozvucenje;
	}

	void zauzmiMesto(int i){
		if(!mesta[i]){
			mesta[i] = true;
		}
		else{
			System.out.println("Mesto pod rednim brojm " + i + " je vec zauzeto!");
		}
	}

	boolean proveriOzvucenje(){
		power = 1.0;
		for (int i = 0; i < brMesta; i++) {
			if(!mesta[i]){
				power = 1.2;
				break;
			}
		}
		return true;
	}

	@Override
	public String toString() {
		return "Muzicka sala " + getNaziv() + " povrsine " + getSirina()*getDuzina() + "m^2 sa " + getBrMesta() + " mesta za sedenje.";
	}
}
