package stek;

import java.util.Arrays;

public class Niz implements Stek {
	private int[] elementi;
	private static int vrhSteka, tmp;
	private int kapacitet;

	public Niz(int kapacitet) {
		this.kapacitet = kapacitet;
		vrhSteka = 0;
		elementi = new int[kapacitet];
	}

	public Niz() {
		this(10);
	}

	@Override
	public void pop() {
		if(vrhSteka == 0) {
			System.out.println("Stek je prazan!");
			return;
		}
		System.out.println(elementi[vrhSteka-1]);
		elementi[vrhSteka] = 0;
		vrhSteka--;
	}

	@Override
	public int top() {
		if(vrhSteka == 0){
			System.out.println("Stek prazana!");
			return 0;
		}
		System.out.println(elementi[vrhSteka-1]);
		return elementi[vrhSteka];
	}

	@Override
	public int size() {
		System.out.println(vrhSteka);
		return vrhSteka;
	}

	@Override
	public void show() {
		tmp = vrhSteka;
		while(tmp >= 0){
			System.out.println(elementi[tmp]);
			tmp--;
		}
	}

	@Override
	public void push(int x) {
		if(kapacitet-1 == vrhSteka){
			kapacitet *= 2;
			elementi = Arrays.copyOf(elementi, kapacitet);
		}
		elementi[vrhSteka] = x;
		System.out.println(elementi[vrhSteka]);
		vrhSteka++;
	}
}
