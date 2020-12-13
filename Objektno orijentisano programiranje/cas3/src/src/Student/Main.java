package Student;

public class Main {

	public static void main(String[] args) {
		Student s1 = new Student("Dimitrije", "Stankov", "mi3072017", 7.6);
		Student s2 = new Student("Jovan", "Milic", "mi1272017", 8);
		Student s3 = new Student("Neko", "Los", "ar1231234", 0);

		Student[] studenti = {s1, s2, s3};
		for (Student student : studenti) {
			System.out.println(student);
		}

		Student x = new Student("Test", "Set", "indeks", 2.1);
		x.setIndeks("mi0012019");

		System.out.println(x);
	}
}
