#ifndef H_INITPERSO_H
#define H_INITPERSO_H

#include "datalist.h"
#include "arithmetique.h"

typedef float const statistic;
typedef int const parametre;


class INITPERSO
{
	private:
	
	static DATA m_data;
	static CALCULUS m_maths; //appel du constructeur ici car static
	
	//Paramètres de distribution:
	
	//Distribution sens confondus:
	static statistic m_sens_MOYENNE,m_sens_VARIANCE;
	static statistic m_state; //chance sur 100 d'être en bon etat
	static statistic m_particulier; // float entre 0 et 1, chance d'avoir un trait particulier
	
	
	
	//Parametres pour fabrique des histoires:
	
	static std::string lieu,action,tiers;
	
	
	
	public:
	
	INITPERSO();
	~INITPERSO();
	
	
	//Renvoie Vrai si Homme, faux si Femme
	static bool initSexe();
	//Renvoie vrai si un trait particulier, faux sinon
	static bool randomize();
	
	//Ajoute un entier compris entre minbonus et maxbonus a l'int valeurActuelle de sorte a ne pas depasser valMax
	static int addbonus(int valeurActuelle,int valMax,int minbonus,int maxbonus);
	
	//Compare deux string deux a deux tirés dans le meme fichier(meme famille), regarde s'il existe une balise REFUSE.S'il en existe une, compare les deux mots et regardent s'ils sont mutuellement exclusifs,sinon renvoie automatiquement faux. S'ils le sont renvoie vrai, sinon faux.
	static bool makeREFUSE(std::string subdir,std::string famille,std::string mot1,std::string mot2);	
	//VISAGE:
	
	//Attribut a chaque sens un score entre 0 et 100 qui determine la qualité du sens:
	static int initSens();
	
	//attribut a chaque partie du visage une probabilité d'être présente:
	static bool initPresence(int min,int max,int seuil);
	
	//atribut a chaque partie presente son etat:ok,ornée,abimé
	//1 : ok
	//2 : altéré ( orné,abimé...)
	//renvoie un entier correspondant a l'un de ces etats avec une probabilité cha
	static int initState(int seuil);
	
	//renvoie un int au hasard compris entre min et max inclus
	static int initInt(int min,int max);
	
	//Fonction générale qui appelle : initSens(),initPresence()
	static int initATTRIBUTS();
	
	//Appel appelString(), renvoie un string avec les mot principal plus une prob Prob les mots appelés
	static std::string initTEXTE_S(float Prob,std::string subdir,std::string famille,std::string ID,std::string options,std::string DES);
	
	//Appel appelVector(), renvoie un string avec les mot principal plus une prob Prob les mots appelés
	static std::vector<std::string> initTEXTE_V(float Prob,std::string subdir,std::string famille,std::string ID,std::string options,std::string DES);
	
	//Appel getTAT(), renvoie un string contenant un texte a trou remplit, chaque trou étant rempli par un mot uniquement:
	static std::string initTAT(std::string subdir,std::string famille,std::string ID,std::string options,std::string DES);
	
	//HISTOIRES:
	
	
	
	
	
	
	
};






#endif
