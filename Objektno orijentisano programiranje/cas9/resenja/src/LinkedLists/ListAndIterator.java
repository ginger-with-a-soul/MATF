package LinkedLists;

import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;

public class ListAndIterator {
	public static void main(String[] args) {
		LinkedList<String> lista = new LinkedList<>(Arrays.asList("Dimitrije", "Stankov", "307", "/", "2017"));

		Iterator<String> iterator = lista.iterator();

		while(iterator.hasNext()){
			System.out.println(iterator.next());
		}

		System.out.println(lista.get(1));
		lista.remove(1);
		System.out.println(lista.get(1));
		lista.addFirst("Student");
		lista.addLast(".");

		for(String rec : lista){
			System.out.println(rec + " ");
		}
	}

}
