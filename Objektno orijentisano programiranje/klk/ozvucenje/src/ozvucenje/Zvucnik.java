package ozvucenje;

public class Zvucnik {
	private String proizvodjac, model;
	private int snaga;
	private boolean ukljucen;

	public Zvucnik(String proizvodjac, String model, int snaga) {
		this.proizvodjac = proizvodjac;
		this.model = model;
		this.snaga = snaga;
		this.ukljucen = false;
	}

	public Zvucnik(Zvucnik z){
		this.proizvodjac = z.getProizvodjac();
		this.model = z.getModel();
		this.snaga = z.getSnaga();
		this.ukljucen = z.isUkljucen();
	}

	public String getProizvodjac() {
		return proizvodjac;
	}

	public String getModel() {
		return model;
	}

	public int getSnaga() {
		return snaga;
	}

	public boolean isUkljucen() {
		return ukljucen;
	}

	void switchOnOff(){
		this.ukljucen = !this.ukljucen;
	}

	@Override
	public String toString() {
		if(ukljucen) {
			return "Zvucnik " + getProizvodjac() + " " + getModel() + ", snage " + getSnaga() + " je ukljucen";
		}
		else{
			return "Zvucnik " + getProizvodjac() + " " + getModel() + ", snage " + getSnaga() + " je iskljucen";
		}
	}
}
