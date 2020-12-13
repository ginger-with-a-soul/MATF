package Par;

public class UredjeniPar<T1, T2> {

	private T1 a;
	private T2 b;

	public UredjeniPar(T1 a, T2 b) {
		this.a = a;
		this.b = b;
	}

	public T1 getA() {
		return a;
	}

	public T2 getB() {
		return b;
	}

	@Override
	public String toString() {
		return getA() + " " + getB();
	}
}
