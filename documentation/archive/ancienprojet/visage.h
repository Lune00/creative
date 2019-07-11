#ifndef H_VISAGE_H
#define H_VISAGE_H

#include<string>
#include "initperso.h"



class VISAGE
{
	
	
	
	private:
	
	//***ATTRIBUTS VISAGE:
	
	//***SENS (GAMEPLAY):
	int m_vue;
	int m_ouie;
	int m_odorat;
	int m_gout;
	bool m_sexe;

	//presence ou non des differentes parties (GAMEPLAY)
	bool isNez,isOeilG,isOeilD,isOrG,isOrD,isCheveux,isDents,isLunettes,isBarbe,isLangue;
	
	
	//vrai si long,faux si court
	bool m_cheveuxlongs;
	//vrai si la dentition est abimée,faux sinon
	bool m_dentscassees;
	//1 si barbe, 2 si moustache, 3 si rouflaquetets
	int m_typebarbe;
	//states:
	int m_StoeilG,m_StoeilD;
	int m_StoreilleG,m_StoreilleD;
	int m_Stnez,m_Stdentition;
	int m_Stlunettes;
	int m_Stlangue;
	
	
	//Description:
	
	//Couleurs:
	std::string m_couleurYeux,m_couleurCheveux;
	
	//Chevelure:
	std::string m_DEScheveux,m_RES_cheveux;
	
	//Barbe;
	std::string m_DESbarbe;
	
	//Nez:
	std::string m_formeNez,m_apparatNez;
	
	//Yeux:
	std::string m_tailleYeux,m_formeYeux,m_sourcils;
	
	//Menton:
	std::string m_menton;
	
	//FORME VISAGE:
	std::string m_visageforme;
	
	//Front:
	std::string m_front;
	
	//bouche:
	std::string m_dentition,m_langue,m_bouche;
	
	//teint:
	std::string m_teint;
	
	//physionomie:
	std::string m_physionomie;
	
	//Oreilles:
	std::string m_tailleOreilles,m_positionOreilles,m_apparatOreilles;
	
	//Lunettes:
	std::string m_formeLunettes;
	

	//***DESCRIPTION:
	std::string m_GLOBAL;
	
	std::string m_RES_oreilles;
	std::string m_RES_yeux;
	std::string m_RES_nez;
	std::string m_RES_barbe;
	

	std::string m_regard1,m_regard2;
	std::string m_sens;
	
	public:
	
	VISAGE();
	~VISAGE();
	
	void initall();
	
	//attributs
	void initSens();
	void initPresence();
	void initAttributs();
	
	//description:
	void inityeux();
	void initoreilles();
	void initnez();
	void initcheveux();
	void initbarbe();
	void initautres();
	void emptyall();

	//affichage:
	
	void PRINT();

	//Aspect général:
	void printVisage_general();
	//Cheveux,front,sourcils,yeux,oreilles
	void printVisage_haut();
	//Nez,bouche,dent,langue,menton,barbe
	void printVisage_bas();

	
	//**** Accesseur/mutateurs ****
	
	// SENS:
	
	int& VUE() {return m_vue;}
	const int& VUE() const {return m_vue;}
	
	int& OUIE() {return m_ouie;}
	const int& OUIE() const {return m_ouie;}
	
	int& ODORAT() {return m_odorat;}
	const int& ODORAT() const {return m_odorat;}
	
	int& GOUT() {return m_gout;}
	const int& GOUT() const {return m_gout;}
	
	
	// Presence attributs:
	
	bool& OEILG() {return isOeilG;}
	const bool& OEILG() const {return isOeilG;}
	
	bool& OEILD() {return isOeilD;}
	const bool& OEILD() const {return isOeilD;}
	
	bool& ORED() {return isOrD;}
	const bool& ORED() const {return isOrD;}
	
	bool& OREG() {return isOrG;}
	const bool& OREG() const {return isOrG;}
	
	bool& NEZ() {return isNez;}
	const bool& NEZ() const {return isNez;}
	
	bool& DENTS() {return isDents;}
	const bool& DENTS() const {return isDents;}
	
	bool& CHEVEUX() {return isCheveux;}
	const bool& CHEVEUX() const {return isCheveux;}
	
	bool& LUNETTES() {return isLunettes;}
	const bool& LUNETTES() const {return isLunettes;}

	bool& BARBE() {return isBarbe;}
	const bool& BARBE() const {return isBarbe;}
	
	bool& LANGUE() {return isLangue;}
	const bool& LANGUE() const {return isLangue;}
	
};







#endif