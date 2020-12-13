package kloniranje;

public class Pas extends Zivotinjaa implements Cloneable {
	private String ime, rasa;
	private Buvaa buva;

	public Pas(String ime, String rasa) {
		super("Pas");
		this.ime = ime;
		this.rasa = rasa;
		this.buva = new Buvaa("Buvica", "Buvljak");
	}

	public String getIme() {
		return ime;
	}

	public String getRasa() {
		return rasa;
	}

	public Buvaa getBuva() {
		return buva;
	}

	public void setIme(String ime) {
		this.ime = ime;
	}


	public void setBuva(Buvaa buva) {
		this.buva = buva;
	}

	@Override
	public String toString() {
		return "Pas{" +
				"ime='" + ime + '\'' +
				", rasa='" + rasa + '\'' +
				", buva=" + buva +
				'}';
	}

	public Object clone() throws CloneNotSupportedException{
		return super.clone();
	}
}
