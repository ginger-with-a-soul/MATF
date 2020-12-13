package proroci;

public class Prorok {
	private String ime;
	private int brojOstvarenihProrocanstava, ukupanBrojProrocanstava;

	public Prorok(String ime, int brojOstvarenihProrocanstava, int ukupanBrojProrocanstava) {
		this.ime = ime;
		this.brojOstvarenihProrocanstava = brojOstvarenihProrocanstava;
		this.ukupanBrojProrocanstava = ukupanBrojProrocanstava;
	}

	public Prorok(Prorok p){
		this.ime = p.ime;
		this.brojOstvarenihProrocanstava = p.brojOstvarenihProrocanstava;
		this.ukupanBrojProrocanstava = p.ukupanBrojProrocanstava;
	}

	public String getIme() {
		return ime;
	}

	public int getBrojOstvarenihProrocanstava() {
		return brojOstvarenihProrocanstava;
	}

	public int getUkupanBrojProrocanstava() {
		return ukupanBrojProrocanstava;
	}

	void zabeleziIshodProrocanstva(boolean status){
		this.ukupanBrojProrocanstava++;
		if(status){
			this.brojOstvarenihProrocanstava++;
		}
	}
}
