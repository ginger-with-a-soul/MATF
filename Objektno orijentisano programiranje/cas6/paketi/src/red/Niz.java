package red;

import java.util.Arrays;

public class Niz implements Red {
	private int[] elementi;
	private int krajReda, kapacitet, pocetakReda;

	public Niz(int kapacitet) {
		this.kapacitet = kapacitet;
		elementi = new int[kapacitet];
		pocetakReda = 0;
		krajReda = 0;
	}

	public Niz() {
		this(10);
	}

	@Override
	public void push(int x) {
		if(kapacitet == krajReda){
			kapacitet *= 2;
			elementi = Arrays.copyOf(elementi, kapacitet);
		}
		elementi[krajReda++] = x;

	}

	@Override
	public void pop() {
		if(krajReda == 0 || pocetakReda > krajReda){
			System.out.println("Red je prazan!");
			return;
		}
		System.out.println(elementi[pocetakReda++]);
	}

	@Override
	public void front() {
		System.out.println(elementi[pocetakReda]);
	}

	@Override
	public void size() {
		int tmp = krajReda - pocetakReda;
		if(tmp < 0){
			System.out.println("Red je prazan!");
		}
		else{
			System.out.println("U redu ima " + tmp + " element/a");
		}
	}

	@Override
	public void show() {
		int pr = pocetakReda;
		if(krajReda - pocetakReda <= 0){
			System.out.println("Red je prazan!");
		}
		else{
			while(pr < krajReda){
				System.out.println(elementi[pr++]);
			}
		}
	}
}
