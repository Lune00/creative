#ifndef H_DATALIST_H
#define H_DATALIST_H

#include<vector>
#include<string>
#include<dirent.h>



class DATA
{

private: 
  
//INDEX:
std::string m_separateur;
std::string m_DIR;
std::vector<std::string> m_NOMS;
std::vector<std::string> m_SUBDIR;
std::vector<std::string> m_FAMILLE;
static const std::string m_descripteurs[11];


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



//Repere les balises dans un fichier (path) et renvoie un vecteur de string contenant tous les mots autorises par display
//MOTS CLEFS DANS LES BALISE : IDENTITE (EN FAIRE UNE BASE)
//LANCER UNE SONDE QUI FAIT LA LISTE DES BALISES AVANT?VERIFIE CELLES PRESENTES ET DIT QUE C EST MORT AVANT DE TOUT PARCOURIR
//POUR RIEN
//FAIRE UN TABLEAU DE L ARBORESCENCE,DES ID DANS CHAQUE FICHIER ET DES OPTIONS ASSOCIEES A CHAQUE ID


//BALISE ACCEPTEE + OPTIONS +DESCRITPEURS, ACCES PAR NOM
std::vector<std::string> getData(const std::string& path,std::vector<std::string> ID, \
                                     std::vector<std::string> OPTIONS,std::string DESCRITPEURS);
//BALISE ACCEPTE+ OPTIONS+DESCRITPEURS, ACCES PAR NUMERO
std::vector<std::string> getData(const std::string& path,std::vector<int> ID,std::vector<int> OPTIONS); 



//PRENDS UN MOT DANS LA LISTE, PREND LES MOTS EN PARAMETRES, WORDSLIST RETOURNEE PAR GETDATA
// APPEL RECURSIF,SI OPTIONS ON RAPELLE GET-DATA ET pickup_word
std::string pickup_word(std::vector<std::string> wordslist,int colonne);

//TRADUIT LE CODE DES PARAMETRES(ID+OPTIONS DANS FICHIER TEXTE) ET APPEL get_DATA pour prendre les mots determines par les parametres
void get_parameter(std::string word,std::string parameter);
//renvoie la bonne colonne definit par descripteur pour chaque (ID,OPTION)
int get_colonne(std::string line,std::string DESCRITPEURS);
    

};




#endif
