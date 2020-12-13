package izraz;

public class Promenljiva extends Izraz {
	private String ime;
	private double vrednost;

	public Promenljiva(String ime, double vrednost){
		this.ime = ime;
		this.vrednost = vrednost;
	}

	public Promenljiva(){
		this("generic", 0);
	}

	public String getIme() {
		return ime;
	}

	public double getVrednost() {
		return vrednost;
	}

	@Override
	public double izracunaj() {
		return vrednost;
	}

	public void setVrednost(double vrednost) {
		this.vrednost = vrednost;
	}

	@Override
	public String toString() {
		return "Promenljiva{" +
				"ime='" + ime + '\'' +
				'}';
	}
}
