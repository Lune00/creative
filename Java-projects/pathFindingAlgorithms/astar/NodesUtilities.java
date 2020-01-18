import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

//Gather all functions working on array of nodes ( Node[][] )
public class NodesUtilities {

	static public void printNodes(Node[][] nodes) {
		for (int x = 0; x != nodes.length; x++) {
			for (int y = 0; y != nodes[0].length; y++) {
				System.out.print(nodes[x][y] + " ");
			}
			System.out.println("");
		}
	}

	// Detect starting/ending node in nodes, status : char 's' for starting node ,
	// char 'e' for ending node
	static Node getLimitNodes(Node[][] nodes, char status) {

		// rows
		final int Nx = nodes.length;
		// col
		final int Ny = nodes[0].length;
		Node pointToFind = null;

		for (int x = 0; x != Nx; x++) {
			for (int y = 0; y != Ny; y++) {
				if (nodes[x][y].status == status) {
					pointToFind = nodes[x][y];
				}
			}
		}

		// S'il n'est pas trouvé ou précisé par l'utilisateur, on assigne des valeurs
		// par defaut au start/end
		if (pointToFind == null) {
			// Warning: si nodes[0][0] n'est pas walkable, on le set free

			if (status == 's') {
				System.out.println("Le point de départ n'a pas été précisé, par défaut défini à nodes[0][0]");
				nodes[0][0].status = '.';
				return nodes[0][0];
			} else if (status == 'e') {
				System.out.println(
						"Le point final (a atteindre) n'a pas été précisé, par défaut défini à nodes[length-1][length-1]");
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

		final int Nx = nodes.length;
		final int Ny = nodes[0].length;

		for (int x = 0; x != Nx; x++) {
			for (int y = 0; y != Ny; y++) {

				// if node dans le path on ecrit le char correspondant au chemin
				if (path.contains(new Node(x, y))) {
					System.out.print("x" + " ");
				} else
					System.out.print(nodes[x][y] + " ");
			}
			System.out.println();
		}
	}

	// Input a maze string, return a 2D array of Nodes based on
	static Node[][] buildNodesFromString(String maze) {

		String[] rows = maze.split("\n");
		final int Nx = rows.length;
		final int Ny = rows[0].length();

		Node[][] nodes = new Node[Nx][Ny];

		for (int x = 0; x != Nx; x++) {
			for (int y = 0; y != Ny; y++) {
				nodes[x][y] = new Node(x, y, rows[x].charAt(y));
			}
		}

		return nodes;
	}

	// Reconstruit le chemin trouvé, en partant de end, et en remontant les parents
	// jusqu'à arriver au start(pas de parent)
	public static List<Node> constructPath(List<Node> closedList, Node end, Node start) {
		List<Node> path = new ArrayList<Node>();
		Node current = end;
		while (current.parent != null) {
			path.add(current);
			current = current.parent;
		}
		path.add(start);
		// Reverse order
		Collections.reverse(path);
		return path;
	}

}
