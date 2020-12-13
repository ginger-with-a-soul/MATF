package proroci;

public class TarotProrok extends Prorok {
	private TarotKarta[] karte;

	public TarotProrok(String ime, int brojOstvarenihProrocanstava, int ukupanBrojProrocanstava, TarotKarta[] karte) {
		super(ime, brojOstvarenihProrocanstava, ukupanBrojProrocanstava);
		this.karte = karte;
	}

	public TarotKarta[] getKarte() {
		return karte;
	}

	void izvuciKartu(){
		for(TarotKarta k : karte){
			System.out.println(k);
		}
	}

	String proreci(TarotKarta tk){
		for (int i = 0; i < karte.length; i++) {
			return karte[i].toString();
		}
		return karte[0].toString();
	}

	@Override
	public String toString() {
		return "[tarot prorok]: " + getIme() + ", uspelo: " + getBrojOstvarenihProrocanstava() + ", ukupno: " + getUkupanBrojProrocanstava() + ", poseduje karata:" + karte.length;
	}
}
