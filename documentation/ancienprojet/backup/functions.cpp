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
//-------------------Fonctions sur char et string : 


//Renvoie une voyelle aléatoire pondérée par une priorité
char randomVoyelle()
{
  std::string min_voyelles="aeiouy";
  double priority[6]={1.,1.,0.3,0.3,0.3,0.1};
  char a;
  bool accepted=false;
  float test;
  int pickup;
  test=unifRand();

      do
	{
	   pickup = ( rand() % min_voyelles.size());
	  
	  if(test < priority[pickup]) accepted=true;
	  else accepted=false;
	  
	}while(not accepted);


      a=min_voyelles[pickup];
      return a;
 
}


//Renvoie une consonne aléatoire, minormaj:  true min, false MAJ
char randomConsonne() 
 {
   std::string min_consonnes="zrtpqsdfghjklmwxcvbn";
   //std::string maj_consonnes="ZRTPQSDFGHJKLMWXCVBN";
   //table de priorité de chaque consonne
   float priority[20]={0.1,1.,1.,0.9,0.1,0.8,0.9,1.,0.9,0.9,0.7,0.3,0.8,0.8,0.5,0.1,0.8,0.6,0.7,0.9};
   char a;
   bool accepted=false;
   float test;
   int pickup;
   test=unifRand();
       do
	 {
	    pickup = ( rand() % min_consonnes.size());
	   if(test < priority[pickup]) accepted=true;
	   else accepted=false;
	 }while(not accepted);

       a=min_consonnes[pickup];
  
   return a;
 }

 // affiche une chaine de caractere
 void printName(const std::string& Name)
 {
   cout<<"Mr. "<<Name<<endl;
 }


 // Renvoie une lettre aléatoire: probabilite p de sortir une lettre voyelle et 1-p consomne
                  //NECESSITE RANDOMVOYELLE ET RANDOMCONSOLLE
 char probabilityCV(double p)
 {
   char c;
   if(unifRand()<p) c=randomVoyelle();
   else c=randomConsonne();

   return c;
 }

 // Renvoie le type d'une lettre(généré aléatoirement), Renvoie vrai si c'est une voyelle, faux si c'est une consonne

 bool letterType(char c)
 {

   std::string const min_consonnes="zrtpqsdfghjklmwxcvbn";
   std::string const min_voyelles="aeiouy";

   for(unsigned int t=0;t<min_consonnes.size();t++)
     {
       if (c==min_consonnes[t])
	 {
	   return false;
	   break;
	 }
     }

   for(unsigned int t=0;t<min_voyelles.size();t++)
     {
       if (c==min_voyelles[t])
	 {
	   return true;
	   break;
	 }
     }

   return 0;

 }


// renvoie vrai si c est une minuscule, faux sinon
bool MajOrmin(char c)
{
  std::string min_consonnes="zrtpqsdfghjklmwxcvbn";
  std::string maj_consonnes="ZRTPQSDFGHJKLMWXCVBN";
  std::string min_voyelles="aeiouy";
  std::string maj_voyelles="AEIOUY";


  for(unsigned int t=0;t<min_consonnes.size();t++)
    {
      if (c==min_consonnes[t])
	{
	  return true;
	  break;
	}
    }

  for(unsigned int t=0;t<min_voyelles.size();t++)
    {
      if (c==min_voyelles[t])
	{
	  return true;
	  break;
	}
    }

  for(unsigned int t=0;t<maj_consonnes.size();t++)
    {
      if (c==maj_consonnes[t])
	{
	  return false;
	  break;
	}
    }


  for(unsigned int t=0;t<maj_voyelles.size();t++)
    {
      if (c==maj_voyelles[t])
	{
	  return false;
	  break;
	}
    }

  return 0;
}

// renvoie position de c dans l'alphabet, en sorte, determine la lettre c;
int charLabel(char c)
{

  int label;

  std::string min_consonnes="zrtpqsdfghjklmwxcvbn";
  // std::string maj_consonnes="ZRTPQSDFGHJKLMWXCVBN";
  std::string const min_voyelles="aeiouy";
  //std::string const maj_voyelles="AEIOUY";


      //voyelle
  if(not letterType(c))
    {
      for(unsigned int t=0;t<min_consonnes.size();t++)
	{
	  if (c==min_consonnes[t])
	    {
	      label=t;
	      return label;
	    }
	}
    }
  //consonne
  else
    {
      for(unsigned int t=0;t<min_voyelles.size();t++)
	{
	  if (c==min_voyelles[t])
	    {
	      label=t;
	      return label;
	    }
	}
    }
  return 0;

}

// renvoie vrai si il y'a au moins une consonne ou une voyelle dans le nom
bool checkAny(std::string name)
{
  int nbreVoyelles=0;
  int nbreConsonnes=0;

 for(unsigned int j=0;j<name.size();j++)
    {
      if(letterType(name[j])) nbreVoyelles++;
      else nbreConsonnes++;
     
    }

 if( nbreVoyelles != 0 && nbreConsonnes != 0 ) return true;
 else return false;


}


//Tourne en MAJUSCULE la premiere lettre du string
std::string CapitalFirst(std::string name)
{
  int labelFirst;
  bool voyelle;

  std::string min_consonnes="zrtpqsdfghjklmwxcvbn";
  std::string maj_consonnes="ZRTPQSDFGHJKLMWXCVBN";
  std::string const min_voyelles="aeiouy";
  std::string const maj_voyelles="AEIOUY";

  labelFirst=charLabel(name[0]);
  voyelle=letterType(name[0]);

  if(voyelle) 
    {
      name[0]=maj_voyelles[labelFirst]; 
    } 

  else
    {
      name[0]=maj_consonnes[labelFirst]; 

    }

  return name;

}


//renvoie derniere lettre d'un string
char returnlast(std::string name)
{
  char last;
  int sizeName;
  sizeName=name.size();
  
  last=name[sizeName-1];

  return last;
}

//lit un fichier et stocke chaque phrase dans un vecteur

vector<std::string> read(istream& is)  
{
  std::string prenom;
  vector<std::string> prenoms;
  while(getline(is,prenom))
    {
      prenoms.push_back(prenom);
    }

  return prenoms;

}
    





