package nizovi;

import java.util.Arrays;
import java.util.Scanner;

public class matrice {
	private static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		System.out.println("Input the number of rows: ");

		int n = 0;

		if(sc.hasNextInt()) {
			n = sc.nextInt();
		}
		else {
			System.out.println("Bad input");
			System.exit(1);
		}

		int[][] jaggedArray = new int[n][];

		for (int i = 0; i < n; i++) {
			System.out.println("Input the number of columns: ");
			int m = sc.nextInt();
			jaggedArray[i] = new int[m];
			for (int j = 0; j < m; j++) {
				jaggedArray[i][j] = sc.nextInt();
			}
		}

		show1(jaggedArray);
		changeRows(jaggedArray, n);
		show2(jaggedArray);

	}

	private static void show1(int[][] jaggedArray){
		System.out.println(Arrays.deepToString(jaggedArray));
	}

	private static void changeRows(int[][] jaggedArray, int n){
		System.out.println("What row would you like to change: ");
		int j = 0, k = 0;
		if(sc.hasNextInt()){
			j = sc.nextInt();
			k = sc.nextInt();
			if(j > k || k >= n || j < 0){
				System.out.println("Bad j and/or k range!");
				System.exit(1);
			}
		}
		else{
			System.out.println("Bad j and/or k range!");
			System.exit(1);
		}

		int[] tmp = jaggedArray[j];
		jaggedArray[j] = jaggedArray[k];
		jaggedArray[k] = tmp;
	}

	private static void show2(int[][] jaggedArray){
		System.out.println(Arrays.deepToString(jaggedArray));
	}
}
