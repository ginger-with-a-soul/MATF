package Map;

import java.util.*;

public class PointsAndGrades {
	public static void main(String[] args) {
		Map<String, Integer> mapaBodova = new TreeMap<>();
		mapaBodova.put("Nemanja Nemanjic", 100);
		mapaBodova.put("Ana Anic", 97);
		mapaBodova.put("Stefan Stefanovic", 101);
		mapaBodova.put("Marko Markovic", 85);
		mapaBodova.put("Jovana Jovanovic", 80);
		mapaBodova.put("Nina Ninic", 96);

		Map<String, List<Integer>> mapaOcena = new TreeMap<>();

		mapaOcena.put("Nemanja Nemanjic", new ArrayList<>(Arrays.asList(6, 7, 8, 9)));
		mapaOcena.put("Ana Anic", new ArrayList<>(Arrays.asList(10, 10, 10, 10)));
		mapaOcena.put("Stefan Stefanovic", new ArrayList<>(Arrays.asList(9, 10, 10, 10)));
		mapaOcena.put("Jovana Jovanovic", new ArrayList<>(Arrays.asList(6, 8, 8, 10)));
		mapaOcena.put("Nina Ninic", new ArrayList<>(Arrays.asList(8, 8, 8, 10)));

		for(String kljuc : mapaBodova.keySet()){
			System.out.println("- " + kljuc);
		}

		int ukupnoBodova = 0;

		for(Integer bod : mapaBodova.values()){
			ukupnoBodova += bod;
		}

		System.out.println((double)ukupnoBodova/mapaBodova.size());

		for(Map.Entry<String, Integer> el : mapaBodova.entrySet()){
			System.out.println(el.getKey() + " " + el.getValue());
		}

		Map<String, Double> mapaProseka = new TreeMap<>();

		for(Map.Entry<String, List<Integer>> el : mapaOcena.entrySet()){
			String ime = el.getKey();
			double prosek = 0;
			for(Integer ocena : el.getValue()){
				prosek += ocena;
			}
			prosek /= el.getValue().size();
			mapaProseka.put(ime, prosek);
		}

		for(Map.Entry<String, Double> el : mapaProseka.entrySet()){
			System.out.println(el.getKey() + " " + el.getValue());
		}
	}
}
