package Set;

public class Tacka implements Comparable<Tacka> {
	private double x, y;

	public Tacka(double x, double y) {
		this.x = x;
		this.y = y;
	}

	public Tacka(Tacka t){
		this(t.x, t.y);
	}

	public Tacka(){
		this.x = 0;
		this.y = 0;
	}

	public double getX() {
		return x;
	}

	public double getY() {
		return y;
	}

	@Override
	public String toString() {
		return "Tacka{" +
				"x=" + x +
				", y=" + y +
				'}';
	}

	@Override
	public int compareTo(Tacka tacka) {
		if(x == tacka.x){
			return Double.compare(y, tacka.y);
		}
		return Double.compare(x, tacka.x);
	}
}
