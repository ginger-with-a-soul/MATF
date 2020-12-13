package proroci;

public class TarotKarta {
	private int vreme;
	private String opis, poreklo;

	public TarotKarta(int vreme, String opis, String poreklo) {
		this.poreklo = poreklo;
		this.opis = opis;
		if(vreme != -1 && vreme != 1) {
			this.vreme = 0;
		}
		else{
			this.vreme = vreme;
		}
	}

	public TarotKarta(TarotKarta t){
		this.vreme = t.vreme;
		this.opis = t.opis;
		this.poreklo = t.poreklo;
	}

	public int getVreme() {
		return vreme;
	}

	public String getOpis() {
		return opis;
	}

	public String getPoreklo() {
		return poreklo;
	}

	@Override
	public String toString() {
		return "[tarot karta] vreme: " +  + ", opis: " + getOpis() + ", poreklo: " + getPoreklo();
	}
}
