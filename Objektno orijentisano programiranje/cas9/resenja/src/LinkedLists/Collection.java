package LinkedLists;

import java.util.*;

public class Collection {
	public static void main(String[] args) {
		List<Integer> lista = Arrays.asList(1, 2, 3, 4, 5, 6);

		Collections.reverse(lista);
		iterate(lista);

		Collections.rotate(lista, 2);

		Collections.shuffle(lista);
		iterate(lista);

		Collections.sort(lista);
		iterate(lista);

		System.out.println(Collections.max(lista));
		System.out.println(Collections.min(lista));


	}

	private static void iterate(List<Integer> lista) {
		Iterator<Integer> iter = lista.iterator();
		while (iter.hasNext()) {
			System.out.println(iter.next());
		}
	}
}
