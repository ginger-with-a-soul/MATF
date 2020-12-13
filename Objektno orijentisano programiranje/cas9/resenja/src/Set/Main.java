package Set;


public class Main {
	public static void main(String[] args) {
		double[][] skupTacaka = {
				{1, 2}, {3, 4.5}, {9, 1.1},
				{11.2, 13.1}, {1, 2}, {1, 2},
				{1, 2}, {1, 2}, {3, 4.5}};

		PoligonalnaLinija poli = new PoligonalnaLinija(skupTacaka);
		System.out.println(poli.brojTemena());
		System.out.println(poli);
	}
}
