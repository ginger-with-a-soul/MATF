package primeri;

import java.util.Scanner;

public class sc_ispis_provera {
	private static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {

		System.out.println("Zdravo! Unesite sta zelite da radite:\n1) Zbir brojeva\n2) Provera tipa broja\n3) Suma brojeva\n4) Provera parnosti");
		int o;
		if(sc.hasNextInt()){
			o = sc.nextInt();
			if(o == 1){
				System.out.println(zbir());
			}
			else if(o == 2){
				System.out.println(provera_tipa());
			}
			else if(o == 3){
				System.out.println("Suma je: " + suma());
			}
			else if(o == 4){
				System.out.println("Broj je " + parnost());
			}
			else{
				System.out.println("Niste izabrali ponudjenu opciju!");
				System.exit(1);
			}
		}

	}

	 private static double zbir(){
		double x, y;
		System.out.println("Unesite dva broja: ");
		x = sc.nextDouble();
		y = sc.nextDouble();
		return x + y;
	}

	 private static String provera_tipa(){
		System.out.println("Unesite neki tip: ");
		if(sc.hasNextInt()){
			return "INT je";
		}
		else if(sc.hasNextFloat()){
			return "FLOAT je";
		}
		else if(sc.hasNextBoolean()){
			return "BOOLEAN je";
		}
		else if(sc.hasNext()){
			return "STRING je";
		}
		else{
			return "DOUBLE je";
		}
	}

	private static double suma(){
		System.out.println("Unesite broj brojeva: ");
		int n = sc.nextInt();
		double suma = 0, x;
		while(n-- != 0){
			x = sc.nextDouble();
			suma += x;
		}
		return suma;
	}

	private static String parnost(){
		System.out.println("Unesite broj: ");
		double x;
		if(sc.hasNextDouble()){
			x = sc.nextDouble();
			if(x % 2 == 1){
				return "neparan";
			}
			else{
				return "paran";
			}
		}
		else{
			return "NaN";
		}
	}

}
