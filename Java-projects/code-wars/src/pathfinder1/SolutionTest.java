package pathfinder1;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

// TODO: Replace examples and use TDD development by writing your own tests

public class SolutionTest {
//
//    @Test 
//    public void sampleTests() {
//
//      String a = ".W.\n"+
//                 ".W.\n"+
//                 "...",
//               
//             b = ".W.\n"+
//                 ".W.\n"+
//                 "W..",
//               
//             c = "......\n"+
//                 "......\n"+
//                 "......\n"+
//                 "......\n"+
//                 "......\n"+
//                 "......",
//               
//             d = "......\n"+
//                 "......\n"+
//                 "......\n"+
//                 "......\n"+
//                 ".....W\n"+
//                 "....W.";
//
//        assertEquals(true,  Finder.pathFinder(a));
//        assertEquals(false, Finder.pathFinder(b));
//        assertEquals(true,  Finder.pathFinder(c));
//        assertEquals(false, Finder.pathFinder(d));
//    }

	public static void main(String[] args) {

		String maze = "...\n" + "...\n" + "...";
		String maze2 = "...\n" + "WW.\n" + "WW.";
		String maze3 = 
			  ".W...W\n"+
              ".W.W.W\n"+
              ".....W\n"+
              ".W.W.W\n"+
              ".W...W\n"+
              "...W..";
		
		String maze4 = 
				".....\n"+
				".W.W.\n"+
				".WsW.\n"+
				".WWWW\n"+
				".....\n"+
				"..W..\n"+
				"..W.W\n"+
				"W.WeW";

		System.out.println(Finder.pathFinder(maze4));
		//System.out.println(Finder.pathFinder(maze2));
	}

}
