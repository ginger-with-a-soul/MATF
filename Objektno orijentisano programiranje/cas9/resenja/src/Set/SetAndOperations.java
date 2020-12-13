package Set;

import java.util.Arrays;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class SetAndOperations {
	public static void main(String[] args) {
		Set<Integer> s1 = new TreeSet<>(Arrays.asList(1, 2, 3, 5, 6, 7));
		Set<Integer> s2 = new TreeSet<>();
		s2.add(1);
		s2.addAll(Arrays.asList(1, 2, 3, 4, 5, 6, 8));

		Set<Integer> s1Us2 = new TreeSet<>(s1);
		s1Us2.addAll(s2);
		iterate(s1Us2);

		Set<Integer> s1Collisions2 = new TreeSet<>(s1);
		s1Collisions2.retainAll(s2);
		iterate(s1Collisions2);

		Set<Integer> s2diffs1 = new TreeSet<>(s2);
		s2diffs1.removeAll(s1);
		iterate(s2diffs1);
	}

	private static void iterate(Set<Integer> s1Us2) {
		Iterator<Integer> iter = s1Us2.iterator();
		while(iter.hasNext()){
			System.out.print(iter.next() + " ");
		}
		System.out.println();
	}
}
