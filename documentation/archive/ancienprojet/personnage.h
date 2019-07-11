#ifndef H_PERSONNAGE_H
#define H_PERSONNAGE_H

#include<string>
#include"functions.h"
#include"initperso.h"
#include"visage.h"
#include"story-generator.h"

class PERSO
{
	
	private:
		
		
	//Generateur d'histoire (commun a toutes les instances):comment faire pour que visage puisse s'en servir?
	static STORYG m_generator;
	
	//PHYSIQUE:
	
	// Vrai si un homme, faux si une femme
	bool m_sexe;
	
	//Visage:
	VISAGE m_visage;
	
	public:
	
	PERSO();
	~PERSO();
	
	void getPortrait();
	
	
	bool& SEXE() {return m_sexe;}
	const bool& SEXE() const {return m_sexe;}
	
	
};











#endif