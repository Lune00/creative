public class Node {

	// Uniform cost for moving between any two nodes
	static final int cost = 1;
	
	
	public Node() {
		
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

	//	@Override
	//	public String toString() {
	//		if (isValid)
	//			return "(" + x + ", " + y + ") fscore="+getFscore();
	//		else
	//			return "(" + x + ", " + y + ")";
	//	}

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
