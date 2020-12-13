public class Pravougaonik extends Oblik{
	protected double visina, sirina;

	public Pravougaonik(Tacka centar, double visina, double sirina){
		super(centar);
		init(visina, sirina);
	}

	public Pravougaonik(double x, double y, double visina, double sirina){
		super(x, y);
		init(visina, sirina);
	}

	public Pravougaonik(double visina, double sirina){
		super();
		init(visina, sirina);
	}

	public Pravougaonik(Pravougaonik p){
		super(p.centar);
		init(p.visina, p.sirina);
	}

	private void init(double visina, double sirina){
		this.visina = visina;
		this.sirina = sirina;
	}

	public double getVisina() {
		return visina;
	}

	public double getSirina() {
		return sirina;
	}

	@Override
	public String toString() {
		return "Pravougaonik{" +
				"visina=" + visina +
				", sirina=" + sirina +
				", centar=" + centar +
				'}';
	}
}
