package videoteka;

public class RegularanClan extends Clan {
	private Film iznajmljenFilm;
	static boolean pozajmio = false;

	public RegularanClan(String ime, String omiljeni_zanr){
		super(ime, omiljeni_zanr);
		this.iznajmljenFilm = null;
	}

	public Film getIznajmljeni_film() {
		return iznajmljenFilm;
	}

	public void iznajmiReg(Film f){
		if(iznajmljenFilm == null && !pozajmio){
			iznajmljenFilm = f;
			iznajmljenFilm.setIznajmljen(true);
			pozajmio = true;
			System.out.println(getIme() + " iznajmljuje " + iznajmljenFilm.getNaziv());
		}
		else{
			System.out.println(getIme() + ", ne mozete iznajmiti vise filmova istovremeno! Trenutno iznajmljeni film: " + iznajmljenFilm.getNaziv());
		}
	}

	public void vratiReg(){
		if(pozajmio){
			iznajmljenFilm.setIznajmljen(false);
			pozajmio = false;
			System.out.println(getIme() + " vraca " + iznajmljenFilm.getNaziv());
			iznajmljenFilm = null;
		}
		else{
			System.out.println("Niste pozajmili ni jedan film!");
		}
	}

	@Override
	public String toString(){
		if(pozajmio){
			return "Ime: " + getIme() + "; Omiljeni zanr: " + getOmiljeni_zanr() + "; Trenutno iznajmljeno: " + iznajmljenFilm.getNaziv() + "; Clanarina: 1000.0";
		}
		else{
			return "Ime: " + getIme() + "; Omiljeni zanr: " + getOmiljeni_zanr() + "; Clanarina: 1000.0";
		}
	}
}
