package nizovi;

import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;

public class nizovi {

	private static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {

		int[] a = unesi();

		System.out.println("Unesite operaciju koju zelite:\n1) Modifikacija niza\n2) Sortiranje niza opadajuce\n" +
				"3) Sortiranje niza rastuce\n4) Binarna pretraga niza\n5) Popunjavanje niza\n6) Kopiranje niza");

		int o = sc.nextInt();

		if(o == 1){
			modifikuj(a);
		}
		else if(o == 2){
			Arrays.sort(a);
		}
		else if(o == 3){
			Arrays.sort(a);
		}
		else if(o == 4){
			System.out.println("Unesite element za koji zelite da proverite da li se nalazi u nizu: ");
			int k = sc.nextInt();
			int i = Arrays.binarySearch(a, k);
			if(i < 0){
				System.out.println("Element nije u nizu!");
			}
			else{
				System.out.println("Element jeste u nizu!");
			}
			System.exit(0);
		}
		else if(o == 5){
			Arrays.fill(a, 1);
		}
		else{
			int[] b = Arrays.copyOf(a, a.length);
			show(b);
		}

		ispisi(a);


	}

	private static void modifikuj(int[] a){
		System.out.println("Unesite konstantu modifikacije: ");
		int c = sc.nextInt();
		for (int i = 0; i < a.length; i++) {
			a[i] *= c;
		}
	}

	private static int[] unesi(){

		System.out.println("Unesite broj elemenata niza: ");

		int n = 0;
		if(sc.hasNextInt()){
			n = sc.nextInt();
		}
		else{
			System.out.println("Los unos!");
			System.exit(1);
		}
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = sc.nextInt();
		}

		return a;
	}

	private static void ispisi(int[] a){
		for(int e : a){
			System.out.print(e + " ");
		}
		System.out.println();
	}

	private static void show(int[] a){
		System.out.println(Arrays.toString(a));
	}
}
