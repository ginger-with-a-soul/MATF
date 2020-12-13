public class Tacka {
	private double x, y;

	private static int brojTacaka = 0;

	public Tacka(double x, double y){
		this.x = x;
		this.y = y;
		brojTacaka++;
	}

	public Tacka(){
		this(0, 0);
	}

	public Tacka(Tacka t){
		this(t.x, t.y);
	}

	public static double distance(Tacka a, Tacka b){
		return Math.sqrt(Math.pow(a.x - b.x, 2) + Math.pow(a.y - b.y, 2));
	}

	public double distance(Tacka t){
		return Tacka.distance(this, t);
	}

	public static int getBrojTacaka() {
		return brojTacaka;
	}

	public double getX() {
		return x;
	}

	public double getY() {
		return y;
	}

	public void translate(double dx, double dy){
		x += dx;
		y += dy;
	}

	@Override
	public String toString() {
		return "Tacka{" +
				"x=" + x +
				", y=" + y +
				'}';
	}
}
