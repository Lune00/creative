package boucingBalls;

public class BouncingBall {
	
	
	public static int bouncingBall(double h, double bounce, double window) {
		
		//Invalid experiment
		if( h < 0 || bounce <= 0 || bounce >= 1 || window >= h) {
			return -1;
		}
		
		int nbPassages = 0 ;
		return nombreDePassage(h, bounce, window, nbPassages);
	    
	}

	public static int nombreDePassage(double y, double bounce, double w, int nbPassages ) {
				
		//Si le prochain rebond plus bas que la fenetre on renvoie que le passage descendant
		if(y * bounce < w) {
			return nbPassages + 1;
		}
		
		//Si le prochain rebond plus haut que la fenetre on ajoute 2 passages devant la fenetre (descendant et ascendant)
		nbPassages = nbPassages + 2;
		y = y * bounce;
		
		return nombreDePassage(y, bounce, w, nbPassages);
	}
	
}
