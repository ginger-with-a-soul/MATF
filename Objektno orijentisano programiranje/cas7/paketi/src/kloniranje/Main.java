package kloniranje;

public class Main  {
	public static void main(String[] args) {

		try {
			Pas mojPas = new Pas("Dona", "Pitbul");
			Pas vasPas = (Pas) mojPas.clone();

			System.out.println(mojPas);
			System.out.println(vasPas);

			vasPas.setIme("Maza");
			vasPas.getBuva().setIme("Buvce");

			System.out.println(mojPas);
			System.out.println(vasPas);

			Buvaa klonBuva = (Buvaa) mojPas.getBuva().clone();

			mojPas.setBuva(klonBuva);
			mojPas.getBuva().setIme("KlonBuva");

			System.out.println(mojPas);
			System.out.println(vasPas);

		}catch (CloneNotSupportedException e){
			System.err.println(e.getMessage());
		}
	}
}
