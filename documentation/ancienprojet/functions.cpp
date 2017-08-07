#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "functions.h"
#include "arithmetique.h"

using namespace std;



std::string MoF(bool m_sexe)
{
	
	if(m_sexe) return "il ";
	else return "elle ";
}



//SEPARE TOUS LES MOTS PAR DES ESPACES,VIRGULES:
std::string phraseSPACE(std::vector<std::string> list)
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
std::string phraseET(std::vector<std::string> list)
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











































