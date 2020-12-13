package Stek;

public class tacka {
	private int x, y;

	public tacka(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	@Override
	public String toString() {
		return "tacka{" +
				"x=" + x +
				", y=" + y +
				'}';
	}
}
