package izraz;

public class Oduzimanje extends BinarnaOperacija{

	public Oduzimanje(Izraz levi, Izraz desni){
		super(levi, desni);
	}

	public double izracunaj(){
		return getLevi().izracunaj() - getDesni().izracunaj();
	}

	@Override
	public String toString() {
		return getLevi().toString() + " - " + getDesni().toString();
	}
}
