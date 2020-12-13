package videoteka;

public class VipClan extends Clan {
	private int popust, cenaClanarine;
	static int brojClanova = 0;

	public VipClan(String ime, String omiljeni_zanr) {
		super(ime, omiljeni_zanr);
		brojClanova++;
		if(brojClanova % 3 == 1){
			this.cenaClanarine = 1800;
			this.popust = 10;
		}
		else{
			this.cenaClanarine = 2000;
			this.popust = 0;
		}
	}

	public int getPopust() {
		return popust;
	}

	public void iznajmiVip(Film f) {
		if (!f.isIznajmljen()) {
			f.setIznajmljen(true);
			System.out.println(getIme() + " iznajmljuje " + f.getNaziv());
		} else {
			System.out.println(getIme() + ", film " + f.getNaziv() + " je trenutno iznajmljen.");
		}
	}

	public void vratiVip(Film f){
		if(f.isIznajmljen()){
			f.setIznajmljen(false);
			System.out.println(getIme() + " vraca " + f.getNaziv());
		}
		else{
			System.out.println("Film nije pozajmljen!");
		}
	}

	@Override
	public String toString() {
		return "Ime: " + getIme() + "; Omiljeni zanr: " + getOmiljeni_zanr() + "; Clanarina: " + cenaClanarine;
	}
}
