package kloniranje;

public class Zivotinjaa implements Cloneable {
	private String vrsta;

	public Zivotinjaa(String vrsta) {
		this.vrsta = vrsta;
	}

	public Zivotinjaa(){
		this("Blanko vrsta");
	}

	public void zvuk(){

	}
}
