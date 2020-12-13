package videoteka;

import java.sql.SQLOutput;
import java.util.Scanner;

public class Videoteka {

	public static void ispis(){
		System.out.println("Izaberite 'V' ili 'R' za Vip odnosnot Regularnog clana: ");
	}

	public static void main(String[] args) {
		Film f1 = new Film("Povratak u buducnost", "adventure, comedy, sci-fi", 8.5);
		Film f2 = new Film("Hari Poter i zatvorenik iz Askabana", "adventure, family, fantasy", 8.0);
		Film f3 = new Film("Titanik", "drama, romance", 7.8);
		Film f4 = new Film("Gospodar prstenova: Dve kule", "adventure, drama, fantasy", 9.3);

		Scanner sc = new Scanner(System.in);
		System.out.print("Unesite broj clanova: ");
		int k = sc.nextInt();

		RegularanClan[] nizRegClan = new RegularanClan[k];
		VipClan[] nizVipClan = new VipClan[k];

		int brojReg = 0, brojVip = 0;

		for(int i = 0; i < k; i++){
			ispis();
			char c = sc.next().charAt(0);
			if(c == 'R'){
				System.out.print("Izabrali ste Regularno clana\nUnesite ime i omiljeni zanr: ");
				nizRegClan[brojReg] = new RegularanClan(sc.next(), sc.next());
				brojReg++;
			}
			else if(c == 'V'){
				System.out.println("Izabrali ste Vip clana: ");
				System.out.println("Unesite ime i omiljeni zanr: ");
				nizVipClan[brojVip] = new VipClan(sc.next(), sc.next());
				brojVip++;
			}
			else{
				System.out.println("Niste izabrali ni 'V' ni 'R'!");
			}
		}

		System.out.println(nizRegClan[0]+ "\n" + nizVipClan[0] + "\n" + nizVipClan[1] + "\n");

		nizRegClan[0].iznajmiReg(f3);
		System.out.println(nizRegClan[0]);
		nizVipClan[0].iznajmiVip(f1);

		System.out.println();

		nizVipClan[1].iznajmiVip(f3);
		nizVipClan[1].iznajmiVip(f4);

		System.out.println();

		nizRegClan[0].iznajmiReg(f3);
		nizRegClan[0].vratiReg();
		nizRegClan[0].iznajmiReg(f2);
		nizVipClan[0].iznajmiVip(f3);
		nizVipClan[0].iznajmiVip(f4);
	}
}
