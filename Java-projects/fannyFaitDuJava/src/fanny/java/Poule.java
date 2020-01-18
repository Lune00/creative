package fanny.java;

import java.time.LocalDate;

public class Poule {

	String nom;
	float taille;
	float poids;
	LocalDate dateNaissance;

	public Poule() {

		nom = "Josette";
		System.out.println("Une poule est née! Elle s'appelle " + nom + " !");
		
	}

	void sayHello() {
		System.out.println("Cot cot cot!");
	}

}
