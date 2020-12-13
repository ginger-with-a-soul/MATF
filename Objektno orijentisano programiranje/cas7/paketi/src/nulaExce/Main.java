package nulaExce;

public class Main {
	public static void main(String[] args) {
		int x = 10;

		try{
			System.out.println("Preparing to divide with 0...");
			x /= 0;
			System.out.println("Won't be printed!");
		} catch (ArithmeticException e){
			System.out.println("Division is over and exception has been caught");
			System.out.println(e.getMessage());
			System.out.println(e.getLocalizedMessage());
		}
	}
}
