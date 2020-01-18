package pathfinder1;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

//Implementation of the A* algorithm (2D grid, 4-way movement, cost(node1,node2) = 1 for any couple (node1,node2)
//Maze must be squared or rectangular, no check yet on the validity of the input

public class Finder {

	// Uniform cost for moving between any two nodes
	static final int cost = 1;

	static boolean pathFinder(String maze) {

		// Declaration of the lists:
		List<Node> openList = new ArrayList<Node>();
		List<Node> closedList = new ArrayList<Node>();

		// Build maze as a 2D array of nodes from the String input
		Node[][] nodes = buildNodesFromString(maze);

		// Start A* :

		// Initialiste starting and ending nodes
		//Node start = nodes[0][0];
		//Node end = nodes[nodes.length - 1][nodes.length - 1];
		
		
		//Start node is defined by the character 's' in the string maze
		Node start = getLimitNodes(nodes, 's');
		//End node is defined by the character 'e' in the string maze
		Node end = getLimitNodes(nodes, 'e');

		System.out.println(start.x + " " +start.y +" " + start.isValid);
		System.out.println(end.x + " " +end.y +" " + end.isValid);
		
		// Push start node to openList
		openList.add(start);

		// Core algorithm:
		while (!openList.isEmpty()) {
			
			// Get node from openList with minimum score
			Node current = getNodeFromOpenListWithMinimumScore(openList);
			
			//If current node is end node, there is a path, return true (or the path)
			if( current == end) {
				printNodes(nodes);
				System.out.println();
				printPath(nodes, constructPath(closedList, end, start));
				return true;
			}
				
			// Remove current node from openList
			removeCurrentNodeFromOpenList(current, openList);
			
			// Add current node to closedList
			closedList.add(current);
			// Add valid neighbors to openList if not in closedList:
			List<Node> neighbours = getValidNeighboursFromNodes(current, nodes, closedList);

			// Debug

			for (Node neighbor : neighbours) {
				neighbor.setParent(current);
				neighbor.setScore(end);
				// If neighbor is not already in openList add to openList
				if (!openList.contains(neighbor))
					openList.add(neighbor);
				// Else update score of neighbor already in openList
				else {
					// If new cost(g) to arrive to neighbor is less than previous cost (cost of
					// neighbor in openList) update score g
					// i.e the new path to the location 'neighbor' is better than the previous best
					// path
					if (neighbor.gScore < getNodeFromList(neighbor, openList).gScore) {
						getNodeFromList(neighbor, openList).setScore(end);
						getNodeFromList(neighbor, openList).setParent(current);
					}

				}
			}		
		}
		return false;
	}
	
	
	static public void printNodes(Node[][] nodes) {
		
		for(int x = 0 ; x != nodes.length; x++) {
			for(int y = 0; y != nodes[0].length; y++) {
				System.out.print(nodes[x][y]+" ");
			}
			System.out.println("");
		}
		
	}
	
	
	//Detect starting/ending node in nodes, status : char 's' for starting node , char 'e' for ending node
	static Node getLimitNodes(Node[][] nodes, char status) {
		
		//rows
		final int Nx = nodes.length;
		//col
		final int Ny = nodes[0].length;
		Node pointToFind = null ;
		
		for (int x = 0; x != Nx; x++) {
			for (int y = 0; y != Ny; y++) {
				if(nodes[x][y].status == status ) {
					pointToFind = nodes[x][y];
				}
			}
		}
		
		//S'il n'est pas trouvé ou précisé par l'utilisateur, on assigne des valeurs par defaut au start/end
		if(pointToFind == null) {
			//Warning: si nodes[0][0] n'est pas walkable, on le set free
			
			if(status == 's') {
				System.out.println("Le point de départ n'a pas été précisé, par défaut défini à nodes[0][0]");
				nodes[0][0].status = '.';
				return nodes[0][0];
			}
			else if (status == 'e') {
				System.out.println("Le point final (a atteindre) n'a pas été précisé, par défaut défini à nodes[length-1][length-1]");
				nodes[nodes.length - 1][nodes.length - 1].status = '.';
				return nodes[nodes.length - 1][nodes.length - 1];
			}
		}
		return pointToFind;
	}
	
	

	// Return the valid neighbours from the nodes array, if they are not present in
	// the closedList
	// Valid neighbor means: valid(walkable) and not in closedList(not visited yet)
	static List<Node> getValidNeighboursFromNodes(Node current, Node[][] nodes, List<Node> closedList) {

		List<Node> neighbours = new ArrayList<Node>();

		final int Nx = nodes.length;
		final int Ny = nodes[0].length;
		int xC = current.x;
		int yC = current.y;

		for (int x = xC - 1; x <= xC + 1; x++) {
			for (int y = yC - 1; y <= yC + 1; y++) {

				// Same as current skiped
				if (x == xC && y == yC)
					continue;
				// Skip diagonals?
				if (x != xC && y != yC)
					continue;

				// if node is valid on grid
				if (x < Nx && x >= 0 && y < Ny && y >= 0)
					if (nodes[x][y].isValid && !closedList.contains(nodes[x][y]))
						neighbours.add(nodes[x][y]);
			}
		}
		return neighbours;
	}

	static void removeCurrentNodeFromOpenList(Node current, List<Node> openList) {
		openList.remove(current);
	}

	static Node getNodeFromOpenListWithMinimumScore(List<Node> openList) {

		Node selected = openList.get(0);
		for (int i = 0; i != openList.size(); i++) {
			if (openList.get(i).getFscore() < selected.getFscore())
				selected = openList.get(i);
		}

		return selected;
	}

	static Node getNodeFromList(Node target, List<Node> nodes) {
		return nodes.get(nodes.indexOf(target));
	}
	
	
	static void printPath(Node[][] nodes, List<Node> path) {
		
		// Nested class related
		Finder finder = new Finder();
		
		final int Nx = nodes.length;
		final int Ny = nodes[0].length;
		
		for (int x = 0; x != Nx; x++) {
			for (int y = 0; y != Ny; y++) {
				
				//if node dans le path on ecrit le char correspondant au chemin
				if( path.contains( finder.new Node(x, y) ) ) {
					System.out.print("x"+ " ");
				}
				else
					System.out.print(nodes[x][y]+ " ");
			}
			System.out.println();
		}
		
		
	}

	static Node[][] buildNodesFromString(String maze) {

		String[] rows = maze.split("\n");
		final int Nx = rows.length;
		final int Ny = rows[0].length();
		
		Node[][] nodes = new Node[Nx][Ny];

		// Nested class related
		Finder finder = new Finder();

		for (int x = 0; x != Nx; x++) {
			for (int y = 0; y != Ny; y++) {
				nodes[x][y] = finder.new Node(x, y, rows[x].charAt(y));
			}
		}

		return nodes;
	}

	class Node {

		public Node() {
			// TODO Auto-generated constructor stub
		}

		
		//Only used for printing the path
		public Node(int x, int y) {
			this.x = x;
			this.y = y;
		}
		
		public Node(int x, int y, char status) {
			this.x = x;
			this.y = y;
			this.status = status;
			setIsValid(status);
		}

		// row
		int x;
		// col
		int y;
		boolean isValid;
		Node parent;
		int hScore;
		int gScore;
		//. : free W: wall s: Start e: End
		char status;

		public void setIsValid(char status) {
			if (status == 'W')
				isValid = false;
			else
				isValid = true;
		}

		public void setParent(Node node) {
			parent = node;
		}

		public void setScore(Node end) {
			setGscore();
			setHscore(end);
		}

		// Incremental cost of the node
		public void setGscore() {
			gScore = parent.gScore + cost;
		}

		// Heuristic score of the node == Manhattan distance from the end
		public void setHscore(Node end) {
			hScore = Math.abs(end.x - x) + Math.abs(end.y - y);
		}

		// Total score of the node
		public int getFscore() {
			return hScore + gScore;
		}

//		@Override
//		public String toString() {
//			if (isValid)
//				return "(" + x + ", " + y + ") fscore="+getFscore();
//			else
//				return "(" + x + ", " + y + ")";
//		}
		
		@Override
		public String toString() {
			if (isValid)
				return "" + status;
			else
				return "W";
		}

		@Override
		public boolean equals(Object o) {
			return o instanceof Node && x == ((Node) o).x && y == ((Node) o).y;
		}

	}
	
	//Reconstruit le chemin trouvé, en partant de end, et en remontant les parents jusqu'à arriver au start(pas de parent)
	public static List<Node> constructPath(List<Node> closedList, Node end, Node start) {
		List<Node> path = new ArrayList<Node>();
		Node current = end;
		while(current.parent != null) {
			path.add(current);
			current = current.parent;
		}
		path.add(start);
		//Reverse order
		Collections.reverse(path);
		return path;
	}
	

}