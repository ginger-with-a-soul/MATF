package multipleCatch;

import java.util.Scanner;

public class tryWithResources {
	public static void main(String[] args) {
		int a = 10;
		int[] niz = {1, 3, 5, 2};

		try(Scanner sc = null){
			//a /= 0;
			a = niz[4];
		}catch (ArithmeticException | NullPointerException e){
			System.out.println("Aritmeticka ili Null Pointer greska!");
			System.out.println(e.getMessage());
			e.printStackTrace();
		}catch (Exception e){
			System.out.println("Sve druge greske!");
			System.out.println(e.getMessage());
		}

	}
}
