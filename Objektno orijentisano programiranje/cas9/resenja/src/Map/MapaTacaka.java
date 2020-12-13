package Map;

import java.util.Map;
import java.util.TreeMap;

public class MapaTacaka {
	public static void main(String[] args) {
		Map<String, Tacka> mapa = new TreeMap<>();
		mapa.put("A",  new Tacka(2.1, 3));
		mapa.put("H", new Tacka(0, 1));
		mapa.put("K", new Tacka(4, 3.5));
		mapa.put("J", new Tacka("dim", 2));

		for(Map.Entry<String, Tacka> el : mapa.entrySet()){
			System.out.println(el.getKey() + " " + el.getValue());
		}
	}
}
