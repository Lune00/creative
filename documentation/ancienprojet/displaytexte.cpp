#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "displaytexte.h"
#include "arithmetique.h"
#include "datalist.h"
#include "name-generator.h"

using namespace std;


TEXTE::TEXTE() : m_data(),m_maths(),m_namegen()
{

}


TEXTE::~TEXTE()
{
	
}

void TEXTE::clearall()
{
	m_path.clear();
	m_des.clear();
	m_ids.clear();
	m_options.clear();
	m_list.clear();
	m_phrase.clear();
}

//SEPARE TOUS LES MOTS PAR DES ESPACES,VIRGULES:
std::string TEXTE::phraseSPACE(std::vector<std::string> list)
{
	
	std::string phrase;
	
	
	if(list.size()==3)
	{
	   phrase+=list[0];
	   phrase+=" ";
	   phrase+=list[1];
	   phrase+=", ";
	   phrase+=list[2];
	}
	
	else
	{
	
	   phrase+=list[0];
	   phrase+=" ";
	   
	   for(std::vector<std::string>::const_iterator run=list.begin()+1;run!=list.end();++run)
		{
			phrase+=*run+" ";
		}  
	   phrase=phrase.substr(0,phrase.size()-1);
	}
	
	
	
	return phrase;
	
}
//SEPARE TOUS LES MOTS PAR DES ET (POUR DEUX MOTS),ESPACES POUR DIFFERENTES TAILLES (A POUSSER)
std::string TEXTE::phraseET(std::vector<std::string> list)
{
	std::string phrase;
	std::string liaison=" et ";
	
	
	if(list.size()==1)
	 {
		phrase+=list[0];
	 }
	
	else if(list.size()==2)
	{
	   phrase+=list[0];
	   phrase+=" et ";  
	   phrase+=list[1];
	}
	
	
	else if(list.size()>=3)
	 {
	
		phrase+=list[0];
		phrase+=" ";
	
		for(std::vector<std::string>::const_iterator run=list.begin()+1;run!=list.end();++run)
		 {
			phrase+=*run+liaison;
		 }  
	
		
		phrase=phrase.substr(0,phrase.size()-liaison.size());	
				
	}
	
	
	return phrase;
	
}



//VISAGE:
void TEXTE::printyeux(std::string& color,std::string& taille,std::string& forme,std::string& autre,std::string& sourcils)
{

	if(autre.size()!=0)
	 {
		cout<<"Il "<<autre<<".";
	 }


	else
	{
	
	cout<<"Sous des sourcils "<<sourcils<<" ";
	
	cout<<"se trouvent des "; 
	
	if(taille.size()!=0)
	{
	   
	   cout<<taille<<" ";
	}
	
	cout<<"yeux ";
	
	if(forme.size()!=0)
	{
	   cout<<forme<<", ";
	}
	
	cout<<color<<"";//<<endl;
	cout<<".";
	
	}
	
	cout<<endl;
	
	
}


void TEXTE::printoreilles(std::string& taille,std::string& position,std::string& DESoreille,std::string& apparatOreilles)
{
	
	
	if(DESoreille.size()!=0)
	{
	   cout<<"Il "<<DESoreille<<".";
	   cout<<" ";
	}
	
	else
	{
		if(taille.size()!=0 && position.size()!=0) cout<<"Ses oreilles sont "<<taille<<" et "<<position<<".";
		else if(taille.size()==0 && position.size()!=0) cout<<"Ses oreilles sont "<<position<<" et";
		else if(taille.size()!=0 && position.size()==0) cout<<"Il a de "<<taille<<" oreilles";
		else cout<<"";
		
	   if(apparatOreilles.size()!=0)
		{
		   cout<<" "<<apparatOreilles<<".";
		}
		
	}
	
	
	
	if(taille.size()!=0 | position.size()!=0 | DESoreille.size()!=0 | apparatOreilles.size()!=0 ) cout<<endl;
	
}

//rajouter des booleens pouur mettre de la subtitlité sur les descriptions

void TEXTE::printcheveux(std::string& couleurCheveux,std::string& DEScheveux,std::string& front,bool cheveuxlongs)
{
		if(couleurCheveux.size()!=0)
		{
		
			if(cheveuxlongs) 
			{
		cout<<"Il a des cheveux "<<couleurCheveux<<", "<<exp_hasard()<<" "<<DEScheveux<<" "<<get_expression("visage","cheveu","EXPRESSION","aaa","*")<< " un front "<<front;
			}
			
			else
			{
		cout<<"Il a des cheveux "<<couleurCheveux<<", "<<exp_hasard()<<" "<<DEScheveux<<" "<<get_expression("visage","cheveu","EXPRESSION","bbb","*")<< " un front "<<front;
			}
			
			//cout<<"Il a les cheveux "<<couleurCheveux<<", "<<exp_hasard()<<" "<<DEScheveux<<".";
		   // cout<<"Il est "<<couleurCheveux<<". Ses cheveux sont " <<DEScheveux<<".";
		}
		
		else
		{
		   cout<<DEScheveux;
		}
		
	   cout<<".";
	   cout<<endl;
}


void TEXTE::printbarbe(std::string& barbe)
{
	if(barbe.size()!=0)
	{
	   cout<<"Il porte "<<barbe<<".";
	   cout<<endl; 
	}
}




void TEXTE::print_regard1(std::string& m_regard1)
{
	cout<<"Quand on le regarde droit dans les yeux "<<exp_description()<< " "<<m_regard1<<".";
	cout<<endl;
}


void TEXTE::print_Name()
{

	m_phrase=m_namegen.completeName();
	if(m_maths.unifRand()<0.3) cout<<"Il se nomme "<<m_phrase<<"."<<endl;
	else if (m_maths.unifRand()>0.3 && m_maths.unifRand()<0.6 ) cout<<"Il s'appelle "<<m_phrase<<"."<<endl;
	else if (m_maths.unifRand()>0.6 && m_maths.unifRand()<0.9 ) cout<<"On l'appelle "<<m_phrase<<"."<<endl;
	else cout<<"Tout le monde l'appelle "<<m_phrase<<"."<<endl;

}





void TEXTE::printnez(std::string& formeNez,std::string& apparatNez,std::string& missing)
{
	if(missing.size()!=0) cout<<missing<<".";
	
	else
	{
	   
	  cout<<"Il a "<<formeNez; 
	  if(apparatNez.size()!=0) cout<<", "<<apparatNez;
	}
	cout<<".";
	cout<<endl;
	
}


void TEXTE::printvisage(std::string& visageforme,std::string& teint)
{
	cout<<"Il a le teint "<<teint<<", et le visage "<<exp_hasard()<<" "<<visageforme<<". ";
	//cout<<"Il a un visage "<<exp_hasard()<<" "<<visageforme<<" mais "<<phyisionomie<<" et le teint "<<teint<<". ";
	cout<<endl;
}



std::string TEXTE::exp_description()
{	std::string path;
	path=m_data.makepath(m_data.get_index_DIR(),"mots","expression");
	return phraseET(m_data.appelVector(1.,path,"DESCRIPTION","*","*"));
}

std::string TEXTE::exp_hasard()
{	std::string path;
	path=m_data.makepath(m_data.get_index_DIR(),"mots","expression");
	return phraseET(m_data.appelVector(1.,path,"ATTENUEMENT","*","*"));
}

std::string TEXTE::get_expression(std::string subdir,std::string famille,std::string ID,std::string OPTION,std::string DES)
{	std::string path;
	path=m_data.makepath(m_data.get_index_DIR(),subdir,famille);
	return m_data.appelString(1.,path,ID,OPTION,DES);
}


void TEXTE::printbouche(std::string& bouche,std::string& dentition,std::string& langue,bool islangue, bool dentscassees)
{
		cout<<"Il a "<<bouche;

	   if(langue.empty()) 
	   {
		  if(dentscassees)
		  {
			 cout<<" mais il a  "<<dentition;
		  }
		  
		  else
		  {
		  if(plurielfinder(bouche)) cout<<" qui "<<get_expression("visage","dentition","EXPRESSION","bbb","*")<<" "<<dentition;
		  else cout<<" qui "<<get_expression("visage","dentition","EXPRESSION","aaa","*")<<" "<<dentition;
		  }
	   }
	   
	   else 
	   {
	   
		  if(dentscassees && islangue )
		   {
			 cout<<" mais il  "<<dentition<<". ";
			 cout<<" D'autre part, il "<<langue;
		   } 

		  else if(dentscassees && !islangue) 
		  {
			 cout<<" mais il "<<dentition<<". ";
			 cout<<"Ajouté à cela, il "<<langue;
		  }
		  
		  else if(!dentscassees && !islangue) 
		   {
			  if(plurielfinder(bouche)) cout<<" qui "<<get_expression("visage","dentition","EXPRESSION","bbb","*")<<" "<<dentition;
			  else cout<<" qui "<<get_expression("visage","dentition","EXPRESSION","aaa","*")<<" "<<dentition;
			  cout<<". ";
			  cout<<"Cependant, il "<<langue;
		   }
		  
		  else if (!dentscassees && islangue)
		  {
			 cout<<" mais il a  "<<dentition<<". ";
			 cout<<"D'autre part, il "<<langue;
		  } 
		  
	   }
	
		cout<<".";
		cout<<endl;
	
	
}
void TEXTE::printmenton(std::string& menton)
{
	cout<<"Il a le menton "<<menton;
	cout<<".";
	cout<<endl;
	
	
}




void TEXTE::printSens(int vue, int gout,int ouie, int odorat)
{
	if(vue<10) cout<<"Il est complètement aveugle. ";
	else if(vue>10 && vue <40) cout<<"Il a une très mauvaise vue. ";
	else if(vue>40 && vue <60) cout<<"";
	else if(vue>60 && vue <80) cout<<"Il a une très bonne vue. ";
	else if(vue>80 && vue <90) cout<<"Il a une excellente vue. ";
	else cout<<"Il a une vue exceptionnelle. ";
	
	if(gout<10) cout<<"Son sens du goût est complètement inexistant. ";
	else if(gout>10 && gout <40) cout<<"Il a un sens du goût peu développé. ";
	else if(gout>40 && gout <60) cout<<"";
	else if(gout>60 && gout <80) cout<<"Il a un très bon sens du gôut. ";
	else if(gout>80 && gout <90) cout<<"Il a un sens du goût remarquable. ";
	else cout<<"Il a un sens du goût exceptionnel. ";
	
	
	if(ouie<10) cout<<"Il est complètement sourd. ";
	else if(ouie>10 && ouie <40) cout<<"Il est presque sourd. ";
	else if(ouie>40 && ouie <60) cout<<"";
	else if(ouie>60 && ouie <80) cout<<"Il a l'ouïe fine. ";
	else if(ouie>80 && ouie <90) cout<<"Il a l'ouïe très fine. ";
	else cout<<"Il a une ouïe exceptionnelle. ";
	
	if(odorat<10) cout<<"Il n'a aucun sens de l'odorat. ";
	else if(odorat>10 && odorat <40) cout<<"Il a un très mauvais sens de l'odorat. ";
	else if(odorat>40 && odorat <60) cout<<"";
	else if(odorat>60 && odorat <80) cout<<"Il a un très bon odorat. ";
	else if(odorat>80 && odorat <90) cout<<"Il a un sens de l'odorat remarquable. ";
	else cout<<"Il a un sens de l'odorat exceptionnel. ";
	
	
	cout<<endl;
	
}

bool TEXTE::plurielfinder(std::string& mot) const
{
	if(!mot.empty())
	{
	if (mot[mot.length()-1]=='s' | mot[mot.length()-1]=='x') return true;
	else return false;
	}
	
	else
	{
	   cout<<"@plurielfinder erreur,mot vide.";
	   exit(0);
	}
	
}


//Aspect général:
void TEXTE::printVisage_general(std::string& m_visageforme,std::string& m_phyisionomie,std::string& m_teint)
{
	
	
	
	
	
}
//Cheveux,front,sourcils,yeux,oreilles
void TEXTE::printVisage_haut(std::string& m_couleurCheveux,std::string& m_DEScheveux,std::string& m_front,bool m_cheveuxlongs,std::string& color,std::string& taille,std::string& forme,std::string& autre,std::string& m_sourcils,std::string& m_tailleOreilles,std::string& m_positionOreilles,std::string& DESoreilles,std::string& m_apparatOreilles)
{
	
	
	
	
	
	
}
//Nez,bouche,dent,langue,menton,barbe
void TEXTE::printVisage_bas(std::string& m_formeNez,std::string& m_apparatNez,std::string& m_RES_nez,std::string& m_bouche,std::string& m_dentition,std::string& m_langue,bool isLangue,bool dentscassees,std::string& m_menton,std::string& m_DESbarbe)
{
	
	
	
	
	
	
	
	
	
}








