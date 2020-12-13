package izraz;

public class Broj extends Izraz {
	private double vrednost;

	public Broj(double vrednost){
		this.vrednost = vrednost;
	}

	public Broj(){
		this(0);
	}

	public double izracunaj(){
		return vrednost;
	}

	@Override
	public String toString() {
		return "Broj{" +
				"vrednost=" + vrednost +
				'}';
	}

	public double getVrednost() {
		return vrednost;
	}
}
