package Set;

import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class PoligonalnaLinija {
	private Set<Tacka> temena;

	private Set<Tacka> napraviSet (){
		return new TreeSet<>();
	}

	public PoligonalnaLinija(double[][] koordinate){
		temena = napraviSet();
		for(double[] x : koordinate){
			temena.add(new Tacka(x[0], x[1]));
		}
	}

	public PoligonalnaLinija(){
		temena = napraviSet();
	}

	public PoligonalnaLinija(Tacka t){
		temena = napraviSet();
		temena.add(new Tacka(t.getX(), t.getY()));
	}

	public int brojTemena(){
		return temena.size();
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		Iterator<Tacka> iter = temena.iterator();
		while(iter.hasNext()){
			sb.append(iter.next() + " ");
		}
		return sb.toString();
	}
}
