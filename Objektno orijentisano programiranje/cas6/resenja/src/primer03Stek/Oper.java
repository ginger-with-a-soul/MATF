package primer03Stek;

public enum Oper {
	POP_OPER(0),
	PUSH(1),
	TOP(2),
	SHOW(3);

	private final int op;

	private Oper(int op){
		this.op = op;
	}
}
