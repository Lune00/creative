#include "visage.h"
#include "functions.h"
#include "initperso.h"
#include<string>
#include<iostream>
using namespace std;


VISAGE::VISAGE()
{
	emptyall();
	initPresence();
	initSens();
	initAttributs();
	//PRINT();
	printVisage_bas();
	//initall();
	
}

VISAGE::~VISAGE()
{
	
}

/*
 
 void VISAGE::initall()
 {
 initATTRIBUTS();
 inityeux();
 initpoils();
 initbouche();
 initautres();
 initsens();
 }
 
 */
 
void VISAGE::initSens()
{
	m_vue=INITPERSO::initSens();
	m_gout=INITPERSO::initSens();
	m_odorat=INITPERSO::initSens();
	m_ouie=INITPERSO::initSens();
}

void VISAGE::initPresence()
{
	isNez=INITPERSO::initPresence(0,100,0);
	isOeilG=INITPERSO::initPresence(0,100,85);
	isOeilD=INITPERSO::initPresence(0,100,85);
	isLunettes=INITPERSO::initPresence(0,100,50);
	isOrG=INITPERSO::initPresence(0,100,97);
	isOrD=INITPERSO::initPresence(0,100,97);
	isCheveux=INITPERSO::initPresence(0,100,90);
	isBarbe=INITPERSO::initPresence(0,100,80);if(isBarbe) m_typebarbe=INITPERSO::initInt(1,3);
	isDents=INITPERSO::initPresence(0,100,70);
	isLangue=INITPERSO::initPresence(0,100,90);
	m_cheveuxlongs=INITPERSO::initPresence(0,100,40);	
}


void VISAGE::initAttributs()
{
	//initcheveux();
	//inityeux();
	//initoreilles();
	initnez();
	//initbarbe();
	//initautres();
}





void VISAGE::inityeux()
{

	if(OEILG())
	 {
		m_StoeilG=INITPERSO::initState(30);
	 } 
	
	if(OEILD())
	 {
		m_StoeilD=INITPERSO::initState(30);
	 }
	
	
	if( ! (OEILG() & OEILD()) )
	 {
		if(!OEILG() & OEILD() ) m_RES_yeux=INITPERSO::initTEXTE_S(1.,"visage","oeil","MISSING","GAU","*");
			else if (OEILG() & !OEILD() ) m_RES_yeux=INITPERSO::initTEXTE_S(1.,"visage","oeil","MISSING","DROI","*");
				else 
					 {
						m_RES_yeux=INITPERSO::initTEXTE_S(1.,"visage","oeil","MISSING","DEUX","*");
						m_vue=0;
						m_ouie=INITPERSO::addbonus(m_ouie,100,10,30);
					 }
				 }
	
	else
	 {
		m_RES_yeux.clear();
	 }

	m_couleurYeux=INITPERSO::initTEXTE_S(0.,"visage","oeil","COLOR","*","*");
	m_sourcils=INITPERSO::initTEXTE_S(1.,"visage","oeil","SOURCILS","*","*");
	
	
	if(INITPERSO::randomize())
	{
		m_formeYeux=INITPERSO::initTEXTE_S(0.,"visage","oeil","FORME","*","*");
	}
	
	if(INITPERSO::randomize())
	 {
		m_tailleYeux=INITPERSO::initTEXTE_S(0.,"visage","oeil","TAILLE","*","*");
	 }	
	
	
}



void VISAGE::initoreilles()
{
	//Oreilles:
	
	if(OREG())
	 {
		m_StoreilleG=INITPERSO::initState(50);
	 }
	
	if(ORED())
	 {
		m_StoreilleD=INITPERSO::initState(50);
	 }
	 
if(OREG() & ORED())
  {
	
	if(m_StoreilleG == 2 && m_StoreilleD == 2) m_apparatOreilles=INITPERSO::initTEXTE_S(1.,"visage","oreilles","2PERCES","*","*");
	else  if(m_StoreilleG == 2 && m_StoreilleD == 1) m_apparatOreilles=INITPERSO::initTEXTE_S(1.,"visage","oreilles","GAUCHE","*","*");
	else if(m_StoreilleG == 1 && m_StoreilleD == 2) m_apparatOreilles=INITPERSO::initTEXTE_S(1.,"visage","oreilles","DROITE","*","*");	 
	else m_apparatOreilles.clear();
  }	 

		
else  if( ! (OREG() & ORED()) )
	 {
		if(!OREG() & ORED() ) m_RES_oreilles=INITPERSO::initTEXTE_S(1.,"visage","oreilles","MISSING","GAU","*");
		else if (OEILG() & !OEILD() ) m_RES_oreilles=INITPERSO::initTEXTE_S(1.,"visage","oreilles","MISSING","DROI","*");
		else 
		 {
			m_RES_oreilles=INITPERSO::initTEXTE_S(1.,"visage","oreilles","MISSING","DEUX","*");
			m_ouie=INITPERSO::addbonus(m_ouie,100,-20,0);
		 }
	 }
	
else
	 {
		m_RES_oreilles.clear();
	 }


	if(INITPERSO::randomize())
	 {
		m_tailleOreilles=INITPERSO::initTEXTE_S(0.,"visage","oreilles","TAILLE","*","*");
	 }
	 
	 
	if(INITPERSO::randomize())
	 {
		m_positionOreilles=INITPERSO::initTEXTE_S(0.,"visage","oreilles","FORME","*","*");
	 }
}




void VISAGE::initcheveux()
{

	if(CHEVEUX())
	 {
		m_couleurCheveux=INITPERSO::initTEXTE_S(0.,"visage","cheveu","COLOR","*","*");
		
		if(m_cheveuxlongs) m_DEScheveux=phraseET(INITPERSO::initTEXTE_V(0.5,"visage","cheveu","MAINL","*","*"));
		else m_DEScheveux=phraseET(INITPERSO::initTEXTE_V(0.5,"visage","cheveu","MAINC","*","*"));
		
	 }
	else
	 {
	 	m_couleurCheveux.clear();
		m_DEScheveux="Il est chauve.";
	 }

	
}



void VISAGE::initnez()
{
	
	if(NEZ())
	{
		m_Stnez=INITPERSO::initState(50);
		m_formeNez=INITPERSO::initTAT("visage","nez","FORME","*","*");
		
		
		if(m_Stnez==2) m_apparatNez=INITPERSO::initTEXTE_S(1.,"visage","nez","PERCE","*","*");
		else m_apparatNez.clear();
		m_RES_nez.clear();
	}
	
	else
	{
	   cout<<"MISSING NEZ:"<<endl;
	   m_formeNez.clear();
	   m_apparatNez.clear();
	   //m_RES_nez=INITPERSO::initTEXTE_S(0.,"visage","nez","MISSING","*","*");
	   m_RES_nez="a perdu son nez "+INITPERSO::initTAT("histoire","Mainhistoire","MAIN","A","*");
	}
	
}


//1 si barbe, 2 si moustache, 3 si rouflaquetets
void VISAGE::initbarbe()
{

	if(BARBE())
	{
	   
	   if(m_typebarbe==1)	   m_DESbarbe=	phraseSPACE(INITPERSO::initTEXTE_V(1.,"visage","barbe","DESB","*","*"));
	   else if(m_typebarbe==2) m_DESbarbe=	phraseSPACE(INITPERSO::initTEXTE_V(1.,"visage","barbe","DESM","*","*"));
	   else if(m_typebarbe==3) m_DESbarbe=	phraseSPACE(INITPERSO::initTEXTE_V(1.,"visage","barbe","DESF","*","*"));
	   
	}

	else
	{
	    m_DESbarbe.clear();
	}
	
}


void VISAGE::initautres()
{

	m_bouche=	INITPERSO::initTEXTE_S(1.,"visage","dentition","BOUCHE","*","*");
	m_menton=	INITPERSO::initTEXTE_S(1.,"visage","tete","MENTON","*","*");
	m_visageforme=	INITPERSO::initTEXTE_S(1.,"visage","tete","FORME","*","*");
	m_front=	INITPERSO::initTEXTE_S(1.,"visage","tete","FRONT","*","*");
	m_teint=	INITPERSO::initTEXTE_S(1.,"visage","tete","TEINT","*","*");
	
	
	if(DENTS())
	 {
		m_Stdentition=INITPERSO::initState(50);
		
		if(m_Stdentition==1) m_dentition=INITPERSO::initTEXTE_S(1.,"visage","dentition","SAINE","*","*");
		else m_dentition=INITPERSO::initTEXTE_S(1.,"visage","dentition","ALTERE","*","*");
	 }
	
	else
	{
	   m_dentition=INITPERSO::initTEXTE_S(1.,"visage","dentition","MISSING","DENTS","*");
	}
	
	
	if(LANGUE())
	 {
		m_Stlangue=INITPERSO::initState(90);
	
		if(m_Stlangue==2) m_langue=INITPERSO::initTEXTE_S(1.,"visage","dentition","LANGUE_PERCEE","*","*");
		else m_langue.clear();
	}
	else
	{
	   m_langue=INITPERSO::initTEXTE_S(1.,"visage","dentition","MISSING","LANGUE","*");
	}
	
	//cout<<m_langue<<endl;
}


void VISAGE::emptyall()
{
m_couleurYeux=m_couleurCheveux=m_DEScheveux=m_DESbarbe=m_formeNez=m_tailleYeux=m_formeYeux=m_dentition=m_menton=m_langue=m_front=m_teint=m_physionomie=m_tailleOreilles=m_positionOreilles=m_formeLunettes=m_bouche=m_sourcils="";
}



void VISAGE::printVisage_haut()
{
	

	
}
//Nez,bouche,dent,langue,menton,barbe
void VISAGE::printVisage_bas()
{

	
	cout<<m_formeNez<<endl;
	cout<<m_RES_nez<<endl;
	//m_apparatNez=
	
	
}

void VISAGE::printVisage_general()
{
	printVisage_haut();
	printVisage_bas();
}

