#include "initperso.h"
#include "datalist.h"
#include "arithmetique.h"
#include<iostream>

using namespace std;

//static initialisation:

CALCULUS INITPERSO::m_maths;
DATA INITPERSO::m_data;

//Parametres et probilités d'initialiation:
statistic INITPERSO::m_sens_MOYENNE=50.;
statistic INITPERSO::m_sens_VARIANCE=8.;
statistic INITPERSO::m_particulier=0.5;


INITPERSO::INITPERSO()
{
	
}


INITPERSO::~INITPERSO()
{
		
}


bool INITPERSO::initSexe()
{
	float seuil=50.;
	if(m_maths.unifRand(0,100)<seuil) return true;
	else return false;	
}


int INITPERSO::initSens()
{
	return m_maths.gaussianINT(m_sens_MOYENNE,m_sens_VARIANCE);
}


bool INITPERSO::initPresence(int a,int b,int c)
{
   return (m_maths.unifRand(a,b)) < c ;	
}


int INITPERSO::initState(int seuil)
{
	if(m_maths.unifRand(0,100)<seuil) return 1;
	else return 2;
}

int INITPERSO::initInt(int min,int max)
{
	return m_maths.unifRandInt(min,max);
}

//renvoie un string, contenant plusieurs mots (dépend de prob)  pour la description,couche texte:
//Prob: probabilité d'avoir des mots appelés dans la description: mot principal sûr + mot appelés 
std::string INITPERSO::initTEXTE_S(float prob,std::string subdir,std::string famille,std::string ID,std::string options,std::string DES)
{
	std::string path;
	path=m_data.makepath(m_data.get_index_DIR(),subdir,famille);
	return m_data.appelString(prob,path,ID,options,DES);
}

//renvoie un vecteur de mots
std::vector<std::string> INITPERSO::initTEXTE_V(float prob,std::string subdir,std::string famille,std::string ID,std::string options,std::string DES)
{
	std::string path;
	path=m_data.makepath(m_data.get_index_DIR(),subdir,famille);
	return m_data.appelVector(prob,path,ID,options,DES);
}

std::string INITPERSO::initTAT(std::string subdir,std::string famille,std::string ID,std::string options,std::string DES)
{
	std::string path;
	path=m_data.makepath(m_data.get_index_DIR(),subdir,famille);
	return m_data.getTAT(path,ID,options,DES);
}
	


//renvoie vrai si trait particulier:
bool INITPERSO::randomize()
{
	return (m_maths.unifRand() < m_particulier) ;
}

//ajoute un bonus a un score
int INITPERSO::addbonus(int valActu,int valmax,int minbonus,int maxbonus)
{
	int val;
	val=valActu+m_maths.unifRand(minbonus,maxbonus);
	if(val > valmax) return valmax;
	else return val;
}















//Compare deux string deux a deux tirés dans le meme fichier(meme famille), regarde s'il existe une balise REFUSE.S'il en existe une, compare les deux mots et regardent s'ils sont mutuellement exclusifs,sinon renvoie automatiquement faux. S'ils le sont renvoie vrai, sinon faux.


//1° FAIRE UNE LISTE DES REFUSES DANS UNE FAMILLE
//2° ASSOCIE LES DEUX MOTS AVEC UNE VIRGULE ET COMPARER DIRECTEMENT LES DEUX CHAINES DE CARACTERES (FAIRE L ASSOCIATION DES DEUX MOTS DANS LES DEUX SENS
//3 RENVOYER VRAI SI ON LA TROUVE DANS LISTE REFUSES,FAUX SINON
bool INITPERSO::makeREFUSE(std::string subdir,std::string famille,std::string mot1,std::string mot2)
{
	std::string path;
	std::vector<std::string> ID,OPTIONS,list;
	std:: string DES;
	std::string combine1,combine2;
	combine1=mot1+"+"+mot2;
	combine2=mot2+"+"+mot1;
	
	
	
	ID.push_back("REFUSE");
	OPTIONS.push_back("*");
	DES="*";
	path=m_data.makepath(m_data.get_index_DIR(),subdir,famille);
	
	//cout<<combine1<<" "<<combine2<<" "<<path<<endl;
	
	list=m_data.getData(path,ID,OPTIONS,DES);
	
	for(std::vector<std::string>::const_iterator run=list.begin();run!=list.end();++run)
	 {
	 	if ( (combine1==*run) | (combine2==*run) ) return true;
	 }
	
	return false;
}







