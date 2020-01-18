public class App {

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

		AstarFinder.findPath(maze4);
	}
	
}
