import java.util.ArrayList;
import java.util.List;


public class AstarFinder {

	// Return a path (array of nodes, if path is empty not path exist)
	static List<Node> findPath(String maze) {

		// Declaration of the lists:
		List<Node> openList = new ArrayList<Node>();
		List<Node> closedList = new ArrayList<Node>();

		// Build maze as a 2D array of nodes from the String input
		Node[][] nodes = NodesUtilities.buildNodesFromString(maze);

		// Start A* :

		// Initialiste starting and ending nodes
		//Node start = nodes[0][0];
		//Node end = nodes[nodes.length - 1][nodes.length - 1];


		//Start node is defined by the character 's' in the string maze
		Node start = NodesUtilities.getLimitNodes(nodes, 's');
		//End node is defined by the character 'e' in the string maze
		Node end = NodesUtilities.getLimitNodes(nodes, 'e');

		System.out.println(start.x + " " +start.y +" " + start.isValid);
		System.out.println(end.x + " " +end.y +" " + end.isValid);

		// Push start node to openList
		openList.add(start);

		// Core algorithm:
		while (!openList.isEmpty()) {

			// Get node from openList with minimum score
			Node current = NodesUtilities.getNodeFromOpenListWithMinimumScore(openList);

			//If current node is end node, there is a path, return true (or the path)
			if( current == end) {
				
				List<Node> path = NodesUtilities.constructPath(closedList, end, start);
				NodesUtilities.printNodes(nodes);
				System.out.println();
				NodesUtilities.printPath(nodes, path);
				return path ;
			}

			// Remove current node from openList
			NodesUtilities.removeCurrentNodeFromOpenList(current, openList);

			// Add current node to closedList
			closedList.add(current);
			// Add valid neighbors to openList if not in closedList:
			List<Node> neighbours = NodesUtilities.getValidNeighboursFromNodes(current, nodes, closedList);

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
					if (neighbor.gScore < NodesUtilities.getNodeFromList(neighbor, openList).gScore) {
						NodesUtilities.getNodeFromList(neighbor, openList).setScore(end);
						NodesUtilities.getNodeFromList(neighbor, openList).setParent(current);
					}

				}
			}		
		}
		
		//Empty path => no path
		return new ArrayList<Node>();
	}
}
