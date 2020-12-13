package Tacka;

public class Tacka {
	private double x, y;

	public Tacka() {
		this.x = x;
		this.y = y;
	}

	public Tacka(double x, double y) {
		this.x = x;
		this.y = y;
	}

	public double getX() {
		return x;
	}

	public double getY() {
		return y;
	}

	public double euklidskoRastojanje(Tacka t){
		return Math.sqrt(Math.pow(this.x - t.x, 2) + Math.pow(this.y - t.y, 2));
	}

	public void transliranHorizontalno(double dx){
		this.x += dx;
	}

	public void translirajVertikalno(double dy){
		this.y += dy;
	}

	public String toString(){
		return "\nx: " + x + "\ny: " + y;
	}
}
