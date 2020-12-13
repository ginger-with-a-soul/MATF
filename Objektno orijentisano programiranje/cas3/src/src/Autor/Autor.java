package Autor;

import java.time.Year;

public class Autor {

	private String ime, prezime;
	private int godinaRodjenja;

	public Autor(String ime, String prezime, int godinaRodjenja) {
		this.ime = ime;
		this.prezime = prezime;
		this.godinaRodjenja = godinaRodjenja;
	}

	public String getIme() {
		return ime;
	}

	public String getPrezime() {
		return prezime;
	}

	public int getGodinaRodjenja() {
		return godinaRodjenja;
	}

	public int getGodine(){
		return (Year.now().getValue() - godinaRodjenja);
	}


	public String toString(){
		return "\nAutor: " + ime + " " + prezime + "\nGodina rodjenja: " + godinaRodjenja;
	}
}
