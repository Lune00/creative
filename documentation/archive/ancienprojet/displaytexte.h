#ifndef H_DISPLAYTEXTE_H
#define H_DISPLAYTEXTE_H


#include<string>
#include<vector>
#include"datalist.h"
#include"arithmetique.h"
#include"name-generator.h"

class TEXTE
{
        
private:

DATA m_data;
CALCULUS m_maths;
NAMEGEN m_namegen;


std::string m_path;
std::string m_des;
std::vector<std::string> m_ids;
std::vector<std::string> m_options;
std::vector<std::string> m_list;
std::string m_phrase;

public:

TEXTE();
~TEXTE();	
//Vide toutes les donnees membres;
void clearall();
std::string exp_description();
std::string exp_hasard();
std::string get_expression(std::string subdir,std::string famille,std::string ID,std::string OPTION,std::string DES);
//construit une phrase a partir d'un vecteur de mots
std::string phraseSPACE(std::vector<std::string>);
std::string phraseET(std::vector<std::string>);

//renvoie vrai si le mot est au pluriel, faux sinon;
//Le pluriel est repéré par une terminaison en s ou en x
//eventuellement des exceptions se présenteront
bool plurielfinder(std::string& mot) const;


//Noms:
void print_Name();

//VISAGE:

//essais:
void printSens(int vue,int odorat,int gout,int ouie);
void printyeux(std::string& color,std::string& taille,std::string& forme,std::string& autre,std::string& m_sourcils);
void printcheveux(std::string& m_couleurCheveux,std::string& m_DEScheveux,std::string& m_front,bool m_cheveuxlongs);
void print_regard1(std::string& m_regard1);
void printbarbe(std::string& m_DESbarbe);
void printoreilles(std::string& m_tailleOreilles,std::string& m_positionOreilles,std::string& DESoreilles,std::string& m_apparatOreilles);
void printnez(std::string& m_formeNez,std::string& m_apparatNez,std::string& m_RES_nez);  
void printvisage(std::string& m_visageforme,std::string& m_teint);
void printbouche(std::string& m_bouche,std::string& m_dentition,std::string& m_langue,bool isLangue,bool dentscassees);
void printmenton(std::string& m_menton);      


//Nouvelle approche: (donne plus de souplesse)


//Aspect général:
void printVisage_general(std::string& m_visageforme,std::string& m_phyisionomie,std::string& m_teint);
//Cheveux,front,sourcils,yeux,oreilles
void printVisage_haut(std::string& m_couleurCheveux,std::string& m_DEScheveux,std::string& m_front,bool m_cheveuxlongs,std::string& color,std::string& taille,std::string& forme,std::string& autre,std::string& m_sourcils,std::string& m_tailleOreilles,std::string& m_positionOreilles,std::string& DESoreilles,std::string& m_apparatOreilles);
//Nez,bouche,dent,langue,menton,barbe
void printVisage_bas(std::string& m_formeNez,std::string& m_apparatNez,std::string& m_RES_nez,std::string& m_bouche,std::string& m_dentition,std::string& m_langue,bool isLangue,bool dentscassees,std::string& m_menton,std::string& m_DESbarbe);

};

 

#endif