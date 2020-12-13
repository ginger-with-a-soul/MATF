package nizExce;

public class Main {
	public static void main(String[] args) {
		int[] a = {1, 3, 5, 4};
		Niz x = new Niz(a);

		System.out.println(x.get(2));

		try{
			System.out.println("Pokusava da procita element u nizu na poziciji 4...");
			System.out.println(x.get(4));
			System.out.println("Uspeo");
		} catch(ArrayIndexOutOfBoundsException e){
			System.out.println("Nije uspeo");
			System.err.println(e.getMessage());
			e.getStackTrace();
		}
	}
}
