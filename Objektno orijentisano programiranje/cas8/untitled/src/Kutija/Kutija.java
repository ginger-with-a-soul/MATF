package Kutija;

public class Kutija<T> {
	private T predmet;
	private boolean sadrziPredmet;

	public Kutija(){}

	public Kutija(T predmet){
		this.predmet = predmet;
		this.sadrziPredmet = true;
	}

	public T uzmiPredmet(){
		if(sadrziPredmet){
			this.sadrziPredmet = false;
			return this.predmet;
		}
		else{
			System.out.println("The box is empty!");
			return null;
		}
	}

	public void ubaciPredmet(T predmet){
		if(sadrziPredmet){
			System.out.println("The box already contains an item!");
			return;
		}
		else{
			sadrziPredmet = true;
			this.predmet = predmet;
		}
	}

	@java.lang.Override
	public java.lang.String toString() {
		return "Kutija{" +
				"predmet=" + predmet +
				", sadrziPredmet=" + sadrziPredmet +
				'}';
	}
}
