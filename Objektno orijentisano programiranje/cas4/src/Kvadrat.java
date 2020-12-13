public class Kvadrat extends Pravougaonik {
	public Kvadrat(Tacka c, double a){
		super(c, a, a);
	}
	public Kvadrat(double x, double y, double a){
		super(x, y, a, a);
	}

	public Kvadrat(double visina){
		super(visina, visina);
	}

	public Kvadrat(Kvadrat k){
		super(k.centar, k.visina, k.visina);
	}

	public double getDimenzija(){
		return this.visina;
	}

	public String toString(){
		return "Kvadrat ima: centar" + centar + " i sirinu:" + sirina;
	}
}
