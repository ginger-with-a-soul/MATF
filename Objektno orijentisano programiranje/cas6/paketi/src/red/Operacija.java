package red;

public enum Operacija {
	EXIT(0),
	PUSH(1),
	POP(2),
	FRONT(3),
	SIZE(4),
	SHOW(5);

	public static Operacija fromInt(int o){
		switch(o){
			case 0: return EXIT;
			case 1: return PUSH;
			case 2: return POP;
			case 3: return FRONT;
			case 4: return SIZE;
			case 5: return SHOW;
			default: return EXIT;
		}
	}

	private final int op;

	Operacija(int op) {
		this.op = op;
	}
}
