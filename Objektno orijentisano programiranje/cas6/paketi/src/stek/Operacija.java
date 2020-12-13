package stek;

public enum Operacija {
	EXIT(0),
	PUSH(1),
	POP(2),
	TOP(3),
	SHOW(4),
	SIZE(5);

	private final int op;

	Operacija(int op) {
		this.op = op;
	}
}
