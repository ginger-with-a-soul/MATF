package nizExce;

import java.util.Arrays;

public class Niz {
	private int[] a;

	public Niz(int n) {
		a = new int[n];
	}

	public Niz(int[] tmp){
		a = new int[tmp.length];
		a = Arrays.copyOf(tmp, tmp.length);
	}

	public int get(int i){
		if(i < 0 || i >= a.length){
			throw new ArrayIndexOutOfBoundsException("Lose indeksiranje");
		}
		return a[i];
	}
}
