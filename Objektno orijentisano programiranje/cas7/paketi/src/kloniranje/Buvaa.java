package kloniranje;

public class Buvaa extends Zivotinjaa implements Cloneable {
	private String ime, podvrsta;

	public Buvaa(String ime, String podvrsta) {
		super("Buva");
		this.ime = ime;
		this.podvrsta = podvrsta;
	}

	public void setIme(String ime) {
		this.ime = ime;
	}

	public void setPodvrsta(String podvrsta) {
		this.podvrsta = podvrsta;
	}

	public String getIme() {
		return ime;
	}

	public String getPodvrsta() {
		return podvrsta;
	}

	public void zvuk(){
		System.out.println("Pssstt");
	}

	@Override
	public String toString() {
		return "Buvaa{" +
				"ime='" + ime + '\'' +
				", podvrsta='" + podvrsta + '\'' +
				'}';
	}

	public Object clone() throws CloneNotSupportedException{
		return super.clone();
	}
}
