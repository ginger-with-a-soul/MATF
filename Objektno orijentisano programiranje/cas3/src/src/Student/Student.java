package Student;

public class Student {
	private String ime, prezime, indeks;
	private double prosek;

	public Student(String ime, String prezime, String indeks, double prosek) {
		this.ime = ime;
		this.prezime = prezime;
		this.indeks = indeks;
		this.prosek = prosek;
	}

	public String getIme() {
		return ime;
	}

	public String getPrezime() {
		return prezime;
	}

	public String getIndeks() {
		return indeks;
	}

	public int getGodinaUpisa(){
		String tmp = "20" + indeks.charAt(7) + indeks.charAt(8);
		return Integer.parseInt(tmp);
	}

	public int getBrojIndeksa(){
		String tmp = "" + indeks.charAt(2) + indeks.charAt(3) + indeks.charAt(4);
		return Integer.parseInt(tmp);
	}

	public void setIndeks(String indeks){
		if(validirajIndeks(indeks)){
			this.indeks = indeks;
		}
		else{
			System.out.println("Indeks" + indeks + "nije u dobroj formi!");
		}
	}

	private boolean validirajIndeks(String indeks){
		indeks = indeks.toLowerCase();
		if(indeks.charAt(0) != 'm' && indeks.charAt(0) != 'a'){
			return false;
		}
		String smerovi = "mnvlrif";
		if(!smerovi.contains("" + indeks.charAt(1))){
			return false;
		}

		for(int i = 2; i < indeks.length(); i++){
			if(!Character.isDigit(indeks.charAt(i))){
				return false;
			}
		}

		return true;
	}

	private String validirajSmer(String indeks){
		char modul = indeks.charAt(0);
		char smer = indeks.charAt(1);

		if(modul == 'm'){
			switch (smer){
				case 'a': return "Teorijska matematika";
				case 'r': return "Racunarstvo i informatika";
				case 'i': return "Informatika";
				case 'l': return "Profesor matematike i racunarstva";
				case 'v': return "Statistika i aktuarska i finansijska matematika";
				case 'n': return "Primenjena matematika";
				default: return null;
			}
		}
		else if(modul == 'a'){
			if(smer == 'i'){
				return "Astroinformatika";
			}
			else if(smer == 'a'){
				return "Astrofizika";
			}
			else{
				return null;
			}
		}
		else{
			return null;
		}
	}

	public String getSmer(){
		String validacija = validirajSmer(indeks);
		if(validacija == null){
			return "Smer nije korektan";
		}
		else{
			return validacija;
		}
	}

	public double getProsek(){
		return prosek;
	}

	public String toString(){
		return "Ime: " + ime + "\nPrezime: " + prezime + "\nIndeks: " + indeks + "\nProsek: " + prosek;
	}
}
