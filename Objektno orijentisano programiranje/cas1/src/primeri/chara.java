package primeri;

import java.util.Scanner;
import java.util.concurrent.ConcurrentHashMap;

public class chara {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String x = "";
		System.out.println("Unesite neki string: ");
		if(sc.hasNext()){
			x = sc.next();
			System.out.println("Uneli ste: " + x);
		}
		else{
			System.out.println("Niste uneli string!");
			System.exit(1);
		}
		char y = proveri_prvo_slovo(x);
		System.out.println("Prvo slovo Vase reci je: " + y);

		if(Character.isLowerCase(y)){
			System.out.println("Transformisano: " + Character.toUpperCase(y));
		}
		else if(Character.isUpperCase(y)){
			System.out.println("Transformisano: " + Character.toLowerCase(y));
		}
		else if(Character.isDigit(y)){
			System.out.println("Transformisano: " + Character.getNumericValue(y));
		}

	}

	private static char proveri_prvo_slovo(String x){
		return x.charAt(0);
	}
}
