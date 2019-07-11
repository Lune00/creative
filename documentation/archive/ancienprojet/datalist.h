#ifndef H_DATALIST_H
#define H_DATALIST_H

#include "arithmetique.h"
#include<vector>
#include<string>
#include<dirent.h>



class DATA
{

private: 

CALCULUS m_maths;

std::string m_separateur;
std::string m_DIR;
std::vector<std::string> m_NOMS;
std::vector<std::string> m_SUBDIR;
std::vector<std::string> m_FAMILLE;
static const std::string m_descripteurs[13];
int m_colonne;

std::string m_recursifString;
bool m_recursif;

public:

//constructeur,initialision
DATA();
~DATA();

//Creation Bibliotheque de data, dans le dossier data/!
void make_allPATHS();
int isSubdir(struct dirent* ent);


//INITIALISATION DES INDEXS:

void init_index_SUBDIR(const std::vector<std::string> m_SUBDIR);
void init_index_FAMILLE(const std::vector<std::string> m_FAMILLE);
void call_init_noms();
void call_init_separateur();


void make_dico();
void print_index(std::string INDEX);
void print_all_index();




//acces aux datas:
const std::string get_index_DIR();
const std::vector<std::string> get_index_SUBDIR();
const std::vector<std::string> get_index_FAMILLE();

bool existDir(std::string dir);
bool existSubdir(std::string subdir);
bool existFamille(std::string famille);


std::vector<std::string> read(std::istream& is);


//fonctions relatives au tri et a l'acces des donnes de data


//fonction appelée par display pour faire le path vers ce qu'elle desire avoir acces
//remarque pour plus tard: surcharger la fonction pour que dir soit optionel (car cela va etre redondant)
std::string makepath(std::string dir, std::string subdir, std::string famille); 
bool checkpath(const std::string& path);


//IDEES:
//MOTS CLEFS DANS LES BALISE : IDENTITE (EN FAIRE UNE BASE)
//LANCER UNE SONDE QUI FAIT LA LISTE DES BALISES AVANT?VERIFIE CELLES PRESENTES ET DIT QUE C EST MORT AVANT DE TOUT PARCOURIR
//POUR RIEN
//FAIRE UN TABLEAU DE L ARBORESCENCE,DES ID DANS CHAQUE FICHIER ET DES OPTIONS ASSOCIEES A CHAQUE ID


//FONCTIONS PRINCIPALES:

//Renvoie un vecteur de string qui contient le mot principal et tous les mots appelant
//Pappel : probabilité de se voir ajouter au retour les mots secondaires, si 1. tous les mots sont pris, si 0 seul le mot principal est renvoyé
std::string appelString(float Pappel,const std::string& path,std::string ID,std::string OPTIONS,std::string DESCRITPEURS);
std::vector<std::string> appelVector(float Pappel,const std::string& path,std::string ID,std::string OPTIONS,std::string DESCRITPEURS);

std::vector<std::string> getData(const std::string& path,std::vector<std::string> ID, \
                                     std::vector<std::string> OPTIONS,std::string DESCRITPEURS);

std::vector<std::string> makeParametersList(std::string line);

//tradui les parametres et appel getData pour faire une liste de tous les mots appelés par parameter
std::vector<std::string> readParameters(std::string parameter);
	
//Renvoie la bonne colonne definit par descripteur pour chaque (ID,OPTION) en modifiant m_colonne (appelée par getData())
int get_colonne(std::string line,std::string DESCRITPEURS);

//Prend le mot qui correspond au descripteur dans la ligne (appelée par pickupword() ),renvoie un string
std::string takeDes(std::string line);

//Prend le mot qui correspond au descripteur dans la ligne (appelée par pickupword() ),renvoie un string
std::string takeLine(std::string line);

//Fais une string simple de la liste des mots récupérés,permet de recuperer juste un string:
std::string makeAstring(std::vector<std::string> list);

//renvoie vrai s'il y a un mot appelé sur la ligne,faux sinon
bool isParameters(std::string line);

//verifie la syntaxe du parametre, renvoie vrai si syntaxe ok faux sinon
bool checkParameters(std::string word);

//renvoie le premier mot string, mot appelé de la bonne colonne(appel takeDes): 
std::string takeFirst(std::string word);

//prends un mot au hasard dans la liste de mots
std::string pickInlist(std::vector<std::string> list);


void checkProb(float Prob);

//renvoie une phrase texte a trou, avec des mots appelés par parametres au sein de la phrase. Pas d'appels récursifs dans ce cas ci, il ne peut y avoir qu'on mot par appel
std::string getTAT(const std::string& path,std::string ID,std::string OPTIONS,std::string DESCRITPEURS);
std::string completeTAT(std::string line);




};




#endif
