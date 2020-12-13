package Stek;

public class matfStek<T> implements generickiStek<T> {

	private class Cvor<G>{
		G vrednost;
		Cvor<G> sledeci;

		Cvor(G vrednost) {
			this.vrednost = vrednost;
		}

		@Override
		public String toString() {
			return "Cvor{" +
					"vrednost=" + vrednost +
					'}';
		}
	}

	private Cvor<T> koren;

	public matfStek(){
		this.koren = null;
	}

	@Override
	public T peek() {
		if(koren == null){
			throw new potkoracenjeSteka();
		}

		return koren.vrednost;
	}

	@Override
	public T pop() {
		if(koren == null){
			throw  new potkoracenjeSteka();
		}
		Cvor<T> c = koren;
		koren = koren.sledeci;
		return c.vrednost;
	}

	@Override
	public void push(T el) {
		Cvor<T> c = new Cvor<>(el);
		c.sledeci = koren;
		koren = c;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("[");

		Cvor<T> iterator = koren;
		while(iterator != null){
			sb.append(iterator.vrednost).append(" ");
			iterator = iterator.sledeci;
		}
		sb.append("]");

		return sb.toString();
	}
}
