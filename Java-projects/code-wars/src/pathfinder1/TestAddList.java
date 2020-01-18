package pathfinder1;

import java.util.ArrayList;
import java.util.List;

public class TestAddList {

	public static void main(String[] args) {

		List<Foo> foos = new ArrayList<Foo>();
		TestAddList t = new TestAddList();
		foos.add(t.new Foo(0, 1, "a"));
		foos.add(t.new Foo(1, 0, "b"));

		Foo foo = t.new Foo(0, 1, "b");

		if (foos.contains(foo))
			System.out.println("présent dans la liste");

		System.out.println(foos.get( foos.indexOf(foo) ));

	}

	class Foo {

		int x;
		int y;
		String str;

		public Foo() {
			// TODO Auto-generated constructor stub
		}

		public Foo(int x, int y, String str) {
			this.x = x;
			this.y = y;
			this.str = str;
		}

		@Override
		public boolean equals(Object o) {
			return o instanceof Foo && this.x == ((Foo) o).x && this.y == ((Foo) o).y;
		}

		@Override
		public String toString() {
			return "Foo [x=" + x + ", y=" + y + ", str=" + str + "]";
		}
		
	

	}
}
