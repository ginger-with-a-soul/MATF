package proroci;

public class KuglaProrok extends Prorok {
	private String tipKristala;

	String[] reciProrocanstvo = {"Godine 2020. bice 2020. godina!", "Sledece godine iPhone ce biti jos skuplji", "Sutra ce biti vrucina", "Godine 2018. na kolokvijumu iz OOP-a nece biti polimorfizma"};

	public KuglaProrok(String ime, int brojOstvarenihProrocanstava, int ukupanBrojProrocanstava, String tipKristala) {
		super(ime, brojOstvarenihProrocanstava, ukupanBrojProrocanstava);
		if(tipKristala != "monociklicni" && tipKristala != "tetragonalni") {
			this.tipKristala = "kineski";
		}
		else{
			this.tipKristala = tipKristala;
		}
	}

	String prorekni(){
		for(String rec : reciProrocanstvo){
			System.out.println(rec);
		}

		return "";
	}

	@Override
	public String toString() {
		return "[kugla prorok]:" + getIme() + ", uspelo: " + getBrojOstvarenihProrocanstava() + ", ukupno:" +getUkupanBrojProrocanstava() + ", tip kristala: " + tipKristala;
	}

}
