#ifndef H_NAMEGENERATOR_H
#define H_NAMEGENERATOR_H

#include<string>
#include<vector>
#include "datalist.h"
#include "arithmetique.h"


class NAMEGEN
{


typedef double proba;


private:
	
DATA m_data;
CALCULUS m_maths;


std::string m_prenom;
std::string m_nom;


static const float m_voy_priority[6];	
static const float m_con_priority[20];	
static const std::string m_min_voyelles;
static const std::string m_min_consonnes;

static const int EXnbr3V=14;
static const int EXnbr3C=12;

static const std::string allowed3V[EXnbr3V];
static const std::string allowed3C[EXnbr3C];

//Probabilités d'occurence pour deux consonnes(cons Rules):

proba p_ll,p_ph,p_tr,p_ss,p_fr,p_th,p_qu,p_gu,p_dj,p_xc,p_cc,p_ch;
	  

/*Probabilités, parametres macros sur generation:

p_modifylong: modifier long, plus de 5 syllabes (couper,ajouter particule...)

p_terminology: ajouter syll préprogrammée a la fin

p_addsyll: ajouter syllabe préconcue quelquepart dans le nom

p_CoV: proba de prendre une voyelle apres consonne et vice versa, gere l'alternance

*/
proba p_modifylong,p_terminology,p_addsyll,p_CoV;


//RANGE [MIN,MAX] syllabe composant le nom
int m_MAXSYLLABE;
int m_MINSYLLABE;


public:

NAMEGEN();
~NAMEGEN();


//initialisation des parametres:
void initconsonnerules();
void initparameters();

void printName(const std::string& Name,const std::string& prenom);	
int charLabel(char c);

char randomConsonne();
char randomVoyelle(); 
char consonnesRules(char c,bool firstOne); 
char voyellesRules(char c,bool firstOne);
char getFirstLetterSyll(std::string syll);
char returnlast(std::string name);
char probabilityCV(double p);
	
bool checktwoletters(std::string name);
bool checkAny(std::string name);
bool threeConsecutives(std::string name);
bool allowthreeV(char a,char b,char c);
bool allowthreeC(char a,char b,char c);
bool MajOrmin(char c);
bool letterType(char c);
bool followingLetters(char a,char b);
bool followingLettersBEG(char a,char b);
	
//Fonction principale:
void randomName(int MAXSYLLABE,int MINSYLLABE);
std::string giveSyllabe(char c);
std::string giveTerminaison(char c);
std::string CapitalFirst(std::string Name);	


std::string completeName();
void pickprenomM();
void pickprenomF();
void clearall();
		
};








#endif