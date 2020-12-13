package Map;

public class Tacka<T> {
	private T x, y;

	public Tacka(T x, T y) {
		this.x = x;
		this.y = y;
	}

	public Tacka(){
		this.x = null;
		this.y = null;
	}

	public T getX() {
		return x;
	}

	public T getY() {
		return y;
	}

	@Override
	public String toString() {
		return "Tacka{" +
				"x=" + x +
				", y=" + y +
				'}';
	}
}
