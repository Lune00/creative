#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "name-generator.h"
#include "arithmetique.h"
#include "datalist.h"

using namespace std;

const int NAMEGEN::EXnbr3V;
const int NAMEGEN::EXnbr3C;

const float NAMEGEN::m_voy_priority[6]={0.95,1.,0.3,0.3,0.3,0.1};
const float NAMEGEN::m_con_priority[20]={0.3,1.,1.,0.9,0.3,0.8,0.9,1.,0.9,0.9,0.7,0.4,0.8,0.8,0.5,0.2,0.8,0.6,0.8,0.6};
const std::string NAMEGEN::m_min_voyelles="aeiouy";
const std::string NAMEGEN::m_min_consonnes="zrtpqsdfghjklmwxcvbn";
const std::string NAMEGEN::allowed3V[EXnbr3V]={"eau","iou","oua","iau","yau","you","aeu","ayu","uya","oui","iou","iae","oie","oeu"}; 
const std::string NAMEGEN::allowed3C[EXnbr3C]={"phr","sch","trh","phl","frh","ssh","chr","chl","cht","cht","chm","pht",}; 

NAMEGEN::NAMEGEN() : m_data(),m_maths()
{
	initparameters();
	initconsonnerules();
}


NAMEGEN::~NAMEGEN()
{
	
}


//PARAMETERS OF NAMEGENERATION:

//Occurence de deux consonnes:
void NAMEGEN::initconsonnerules()
{
	p_ll=0.5;
    p_ph=0.5;
    p_tr=0.8;
	p_ss=0.9;
	p_fr=0.4;
	p_th=0.8;
	p_qu=0.2;
	p_gu=0.9;
	p_dj=0.9;
	p_xc=0.7;
	p_cc=0.3;
	p_ch=0.9;	
	
}

//PARAMETRES GLOBAUX:
void NAMEGEN::initparameters()
{

	m_MAXSYLLABE=4;
	m_MINSYLLABE=2;
	
	p_CoV=0.8;
	p_modifylong=0.8;
	p_terminology=0.5;
	p_addsyll=0.7;
}




/*
 *************************
 NAMES GENERATOR FUNCTIONS:
 *************************
 */


//Renvoie une voyelle aléatoire pondérée par une priorité
char NAMEGEN::randomVoyelle()
{
	char a;
	bool accepted=false;
	float test;
	int pickup;
	test=m_maths.unifRand();
	
	do
	 {
		pickup = ( rand() % m_min_voyelles.size());
		
		if(test < m_voy_priority[pickup]) accepted=true;
		else accepted=false;
		
	 }while(not accepted);
	
	
	a=m_min_voyelles[pickup];
	return a;
	
}

//Renvoie une consonne aléatoire, minormaj:  true min, false MAJ
char NAMEGEN::randomConsonne() 
{
	char a;
	bool accepted=false;
	float test;
	int pickup;
	test=m_maths.unifRand();
	do
	 {
	    pickup = ( rand() % m_min_consonnes.size());
		if(test < m_con_priority[pickup]) accepted=true;
		else accepted=false;
	 }while(not accepted);
	
	a=m_min_consonnes[pickup];
	
	return a;
}


// affiche une chaine de caractere
void NAMEGEN::printName(const std::string& Name,const std::string& prenom)
{
	cout<<prenom<<" "<<Name<<endl;//". Comment allez vous?"<<endl;
}

// Renvoie une lettre aléatoire: probabilite p de sortir une lettre voyelle et 1-p consomne
char NAMEGEN::probabilityCV(double p)
{
	char c;
	if(m_maths.unifRand()<p) c=randomVoyelle();
	else c=randomConsonne();
	
	return c;
}

// Renvoie le type d'une lettre(généré aléatoirement), Renvoie vrai si c'est une voyelle, faux si c'est une consonne

bool NAMEGEN::letterType(char c)
{
	
	for(unsigned int t=0;t<m_min_consonnes.size();t++)
     {
		if (c==m_min_consonnes[t])
		 {
			return false;
			break;
		 }
     }
	
	for(unsigned int t=0;t<m_min_voyelles.size();t++)
     {
		if (c==m_min_voyelles[t])
		 {
			return true;
			break;
		 }
     }
	
	return 0;
}


// Donne la lettre suivant la consonne c selon certaines hypotheses, firstOne : vrai si c'est la première lettre du nom (ou d'une partie du nom)
char NAMEGEN::consonnesRules(char c,bool firstOne)
{
	
    char nextletter;
    float random=m_maths.unifRand();
	
    switch(c)
 {
		
	 case 'C':
	 case 'c':
		if( (random<p_cc) && (not firstOne) ) nextletter='c';
		else if( (random>p_cc) && (random<p_ch) ) nextletter='h';
		else nextletter=probabilityCV(p_CoV);
		break;
		
		
	 case 'L':
	 case 'l':
		if(random<p_ll) nextletter='l';
		else nextletter=probabilityCV(p_CoV);
		break;
		
	 case 'P':
	 case 'p':
		if(random<p_ph) nextletter='h';
		else nextletter=probabilityCV(p_CoV);
		break;
		
	 case 'T':
	 case 't':
		if(random<p_tr) nextletter='r';
		else if(m_maths.unifRand()<p_th) nextletter='h';
		else nextletter=probabilityCV(p_CoV);
		break;
		
	 case 'S':
	 case 's':
		if(not firstOne)
		 {
			if(random<p_ss) nextletter='s';
			else nextletter=probabilityCV(p_CoV);
		 }
		else nextletter=probabilityCV(p_CoV);
		break;
		
	 case 'H':
	 case 'h':
		if(firstOne) nextletter=probabilityCV(1.); // renvoie automatiquement une voyelle apres
		else nextletter=probabilityCV(p_CoV);
		break;
		
	 case 'D':
	 case 'd':
		if(random<p_dj) nextletter='j';
		else nextletter=probabilityCV(p_CoV);
		break;
		
		
	 case 'X':
	 case 'x':
		if(random<p_xc) nextletter='c';
		else nextletter=probabilityCV(p_CoV);
		break;
		
		
		
	 default:
		nextletter=probabilityCV(p_CoV);
		
 }
	
    return nextletter;
	
	
}




// Donne la voyelle suivant l'a lettre c selon certaines hypotheses, firstOne : vrai si c est la première lettre du nom (ou d une partie du nom)

char NAMEGEN::voyellesRules(char c,bool firstOne)
{
	
	
	char nextletter;
	typedef double probability;
	probability p_CoV=0.3;//unifRand();
	int randint=m_maths.unifRandInt(1,6);
	
	switch (c)
 {
	 case 'A':
	 case 'a':
		
		switch(randint)
  {
	  case 1:
		 nextletter='u';
		 break;
		 
	  case 2:
		 nextletter='i';
		 break;
		 
	  case 3:
		 nextletter='n';
		 break;
		 
	  case 4:
		 nextletter='r';
		 break;
		 
	  default:
		 nextletter=probabilityCV(p_CoV);
  }
		
		break;
		
	 case 'I':
	 case 'i':
		switch(randint)
  {
	  case 1:
		 nextletter='v';
		 break;
		 
	  case 2:
		 nextletter='n';
		 break;
		 
	  case 3:
		 nextletter='k';
		 break;
	  default:
		 nextletter=probabilityCV(p_CoV);
  }
		
		break;
		
	 case 'O':
	 case 'o':
		switch(randint)
  {
	  case 1:
		 nextletter='u';
		 break;
		 
	  case 2:
		 nextletter='i';
		 break;
		 
	  case 3:
		 nextletter='n';
		 break;
		 
	  case 4:
		 nextletter='k';
		 break;
		 
	  default:
		 nextletter=probabilityCV(p_CoV);
  }
		
		break;
		
	 case 'U':
	 case 'u':
		switch(randint)
  {
	  case 1:
		 nextletter='n';
		 break;
		 
	  default:
		 nextletter=probabilityCV(p_CoV);
  }
		
		break;
		
		
	 case 'Y':
	 case 'y':
		switch(randint)
  {
	  case 1:
		 nextletter='a';
		 break;
		 
	  case 2:
		 nextletter='e';
		 
	  case 3:
		 nextletter='r';
		 break;
		 
	  case 4:
		 nextletter='n';
		 break;
		 
	  default:
		 nextletter=probabilityCV(p_CoV);
  }
		
		break;
		
		
	 default:
		nextletter=probabilityCV(p_CoV);
		
		
 }
	
	return nextletter;
}


//Renvoie vrai si les deux lettres peuvent se suivre suivant les regles etablies (RULES) et faux sinon.
// Cela permet denlever les dédoublements interdits

bool NAMEGEN::followingLetters(char a,char b)
{
	if (a !=b) 
     {
		if(a=='f' && b=='m') return false;
		else if (a=='f' && b=='v') return false;
		else if (a=='v' && b=='f') return false;
		else if (a=='h' && b=='f') return false;
		else if (a=='f' && b=='v') return false;
		else if (a=='c' && b=='j') return false;
		else if (a=='j' && b=='c') return false;
		else if (a=='h' && b=='d') return false;
		else if (a=='c' && b=='j') return false;
		else if (a=='m' && b=='n') return false;
		else if (a=='n' && b=='m') return false;
		else if (a=='c' && b=='g') return false;
		else if (a=='g' && b=='c') return false;
		else if (a=='f' && b=='b') return false;
		else if (a=='j' && b=='n') return false;
		else if (a=='j' && b=='p') return false;
		else if (a=='g' && b=='p') return false;
		else if (a=='p' && b=='g') return false;
		else if (a=='g' && b=='t') return false;
		else if (a=='j' && b=='g') return false;
		else if (a=='g' && b=='j') return false;
		else if (a=='h' && b=='c') return false;
		else if (a=='k' && b=='d') return false;
		else if (a=='b' && b=='t') return false;
		else if (a=='t' && b=='b') return false;
		else if (a=='t' && b=='p') return false;
		else if (a=='t' && b=='d') return false;
		else if (a=='p' && b=='f') return false;
		else if (a=='b' && b=='f') return false;
		else if (a=='b' && b=='p') return false;
		else if (a=='n' && b=='d') return false;
		else if (a=='n' && b=='f') return false;
		else if (a=='n' && b=='j') return false;
		else if (a=='d' && b=='p') return false;
		else if (a=='d' && b=='g') return false;
		else if (a=='j' && b=='f') return false;
		else if (a=='f' && b=='g') return false;
		else if (a=='j' && b=='q') return false;
		else if (a=='p' && b=='b') return false;
		else if (a=='c' && b=='v') return false;
		else if (a=='k' && b=='q') return false;
		else if (a=='q' && b=='k') return false;
		else if (a=='d' && b=='p') return false;
		else if (a=='h' && b=='f') return false;
		else if (a=='p' && b=='b') return false;
		else if (a=='x' && b=='p') return false;
		else if (a=='p' && b=='x') return false;
		else if (a=='m' && b=='q') return false;
		else if (a=='c' && b=='x') return false;
		else if (a=='x' && b=='c') return false;
		else if (a=='m' && b=='d') return false;
		else if (a=='t' && b=='d') return false;
		else if (a=='m' && b=='f') return false;
		else if (a=='v' && b=='p') return false;
		else if (a=='g' && b=='k') return false;
		else if (a=='g' && b=='v') return false;
		else if (a=='v' && b=='b') return false;
		else if (a=='j' && b=='f') return false;
		else if (a=='g' && b=='k') return false;
		else if (a=='v' && b=='x') return false;
		else if (a=='p' && b=='q') return false;
		else if (a=='j' && b=='x') return false;
		else if (a=='j' && b=='g') return false;
		else if (a=='d' && b=='n') return false;
		else if (a=='d' && b=='g') return false;
		else if (a=='f' && b=='g') return false;
		else if (a=='c' && b=='m') return false;
		else if (a=='c' && b=='v') return false;
		else if (a=='j' && b=='v') return false;
		else if (a=='b' && b=='q') return false;
		else if (a=='c' && b=='q') return false;
		else if (a=='x' && b=='k') return false;
		else if (a=='m' && b=='r') return false;
		else if (a=='e' && b=='a') return false;
		else if (a=='g' && b=='q') return false;
		else if (a=='q' && b=='d') return false;
		
		else return true;
		
	 }
	
	else 
	 {
		//Doubles Consonnes:
		if(a=='v') return false;
		else if(a=='w') return false;
		else if(a=='x') return false;
		else if(a=='h') return false;
		else if(a=='q') return false;
		else if(a=='g') return false;
		else if(a=='d') return false;
		else if(a=='b') return false;
		else if(a=='j') return false;
		
		//Doubles voyelles:
		else if(a=='y') return false;
		else if(a=='u') return false;
		else if(a=='i') return false;
		else if(a=='a') return false;
		else if(a=='u') return false;
		else if(a=='o') return false;
		else if(a=='e') return false;
		
		else return true;
	 }
	
}

// renvoie faux si forme interdite pour le debut du nom
bool NAMEGEN::followingLettersBEG(char a,char b)
{
	
	if (a !=b) 
     {
		if(a=='f' && b=='m') return false;
		else if (a=='r' && b=='t') return false;
		else if (a=='f' && b=='v') return false;
		else if (a=='v' && b=='f') return false;
		else if (a=='n' && b=='t') return false;
		else if (a=='h' && b=='f') return false;
		else if (a=='f' && b=='v') return false;
		else if (a=='c' && b=='j') return false;
		else if (a=='j' && b=='c') return false;
		else if (a=='h' && b=='d') return false;
		else if (a=='c' && b=='j') return false;
		else if (a=='m' && b=='n') return false;
		else if (a=='n' && b=='m') return false;
		else if (a=='c' && b=='g') return false;
		else if (a=='g' && b=='c') return false;
		else if (a=='f' && b=='b') return false;
		else if (a=='j' && b=='n') return false;
		else if (a=='j' && b=='p') return false;
		else if (a=='g' && b=='p') return false;
		else if (a=='p' && b=='g') return false;
		else if (a=='g' && b=='t') return false;
		else if (a=='j' && b=='g') return false;
		else if (a=='g' && b=='j') return false;
		else if (a=='h' && b=='c') return false;
		else if (a=='k' && b=='d') return false;
		else if (a=='b' && b=='t') return false;
		else if (a=='t' && b=='b') return false;
		else if (a=='t' && b=='p') return false;
		else if (a=='t' && b=='d') return false;
		else if (a=='p' && b=='f') return false;
		else if (a=='b' && b=='f') return false;
		else if (a=='b' && b=='p') return false;
		else if (a=='n' && b=='d') return false;
		else if (a=='n' && b=='f') return false;
		else if (a=='n' && b=='j') return false;
		else if (a=='d' && b=='p') return false;
		else if (a=='d' && b=='g') return false;
		else if (a=='j' && b=='f') return false;
		else if (a=='f' && b=='g') return false;
		else if (a=='j' && b=='q') return false;
		else if (a=='p' && b=='b') return false;
		else if (a=='c' && b=='v') return false;
		else if (a=='k' && b=='q') return false;
		else if (a=='q' && b=='k') return false;
		else if (a=='d' && b=='p') return false;
		else if (a=='h' && b=='f') return false;
		else if (a=='p' && b=='b') return false;
		else if (a=='x' && b=='p') return false;
		else if (a=='p' && b=='x') return false;
		else if (a=='m' && b=='q') return false;
		else if (a=='c' && b=='x') return false;
		else if (a=='x' && b=='c') return false;
		else if (a=='m' && b=='d') return false;
		else if (a=='t' && b=='d') return false;
		else if (a=='m' && b=='f') return false;
		else if (a=='v' && b=='p') return false;
		else if (a=='g' && b=='k') return false;
		else if (a=='g' && b=='v') return false;
		else if (a=='v' && b=='b') return false;
		else if (a=='j' && b=='f') return false;
		else if (a=='g' && b=='k') return false;
		else if (a=='v' && b=='x') return false;
		else if (a=='p' && b=='q') return false;
		else if (a=='j' && b=='x') return false;
		else if (a=='j' && b=='g') return false;
		else if (a=='d' && b=='n') return false;
		else if (a=='d' && b=='g') return false;
		else if (a=='r' && b=='g') return false;
		else if (a=='l' && b=='m') return false;
		else if (a=='e' && b=='a') return false;
		else if (a=='d' && b=='c') return false;
		else if (a=='r' && b=='x') return false;
		else if (a=='w' && b=='t') return false;
		else if (a=='l' && b=='d') return false;
		else if (a=='k' && b=='p') return false;
		else if (a=='m' && b=='g') return false;
		else if (a=='r' && b=='d') return false;
		else if (a=='r' && b=='m') return false;
		else if (a=='l' && b=='c') return false;
		else if (a=='m' && b=='g') return false;
		else if (a=='v' && b=='g') return false;
		else if (a=='d' && b=='k') return false;
		else if (a=='j' && b=='d') return false;
		else if (a=='v' && b=='n') return false;
		else if (a=='f' && b=='t') return false;
		else if (a=='j' && b=='s') return false;
		else if (a=='j' && b=='t') return false;
		else if (a=='k' && b=='t') return false;
		else if (a=='n' && b=='t') return false;
		else if (a=='j' && b=='m') return false;
		else if (a=='n' && b=='t') return false;
		else if (a=='b' && b=='c') return false;
		else if (a=='f' && b=='c') return false;
		else if (a=='l' && b=='j') return false;
		else if (a=='m' && b=='t') return false;
		else if (a=='m' && b=='s') return false;
		else if (a=='m' && b=='v') return false;
		else if (a=='c' && b=='n') return false;
		else if (a=='b' && b=='m') return false;
		else if (a=='l' && b=='f') return false;
		else if (a=='p' && b=='d') return false;
		else if (a=='r' && b=='p') return false;
		else if (a=='k' && b=='c') return false;
		else if (a=='r' && b=='c') return false;
		else if (a=='r' && b=='b') return false;
		else if (a=='d' && b=='t') return false;
		else if (a=='l' && b=='k') return false;
		else if (a=='r' && b=='f') return false;
		else if (a=='k' && b=='v') return false;
		else if (a=='b' && b=='n') return false;
		else if (a=='b' && b=='k') return false;
		else if (a=='b' && b=='t') return false;
		else if (a=='b' && b=='v') return false;
		else if (a=='d' && b=='v') return false;
		else if (a=='d' && b=='k') return false;
		else if (a=='f' && b=='k') return false;
		else if (a=='t' && b=='c') return false;
		else if (a=='d' && b=='m') return false;
		else if (a=='p' && b=='t') return false;
		else if (a=='w' && b=='g') return false;
		else if (a=='w' && b=='x') return false;
		else if (a=='w' && b=='d') return false;
		else if (a=='w' && b=='z') return false;
		else if (a=='r' && b=='k') return false;
		else if (a=='w' && b=='m') return false;
		else if (a=='l' && b=='t') return false;
		else if (a=='n' && b=='l') return false;
		else if (a=='c' && b=='f') return false;
		else if (a=='m' && b=='r') return false;
		else if (a=='r' && b=='l') return false;
		else if (a=='d' && b=='f') return false;
		else if (a=='l' && b=='q') return false;
		else if (a=='d' && b=='b') return false;
		else if (a=='v' && b=='n') return false;
		else if (a=='d' && b=='b') return false;
		else return true;
		
	 }
	// interdit toutes les doubles lettres pour le debut
	else 
	 {
		return false;
	 }
	
}

//--------------------
//FONCTION PRINCIPALE
//--------------------

// Renvoie un nom généré procéduralement, MAXSYLLABE ET MINSYLLABE définissent le nombre de syllabes qui composent le nom
void NAMEGEN::randomName(int MINSYLLABE,int MAXSYLLABE)
{
	
	MINSYLLABE=m_MINSYLLABE;
	MAXSYLLABE=m_MAXSYLLABE;	
	int nbreSyllabe,nbreFIN;
	std::string Name;
	std::string syll,syllADD;
	char firstLetter;
	char nextLetter,temp;
	int count=0;
	bool bool2,bool3,redo,boolcheck,boolgrammar,boolgrammarsplit;
	bool partBok;
	float randomize;
	
	nbreSyllabe = m_maths.unifRandInt(MINSYLLABE,MAXSYLLABE);
	
	do
     {
		nbreFIN=0;
		Name.clear();
		
		for (int t=0;t<nbreSyllabe;t++)
		 {
			
			randomize=m_maths.unifRand();
			
			//Si premiere syllabe:
			if(t==0)
			 {
				
				if(m_maths.unifRand() < 0.5)
				 { 
					 
					 firstLetter=randomConsonne();
					 
					 do
					  {
						 nextLetter=consonnesRules(firstLetter,true);
					  }while(not followingLettersBEG(firstLetter,nextLetter));	      
				 }
				
				else 
				 {
					
					firstLetter=randomVoyelle();
					
					do
					 {
						nextLetter=voyellesRules(firstLetter,true);
					 }while(not followingLettersBEG(firstLetter,nextLetter));
				 }
				
			 }
			//sinon, autre syllabe    
			else
			 {
				
				if(m_maths.unifRand() < 0.5)
				 { 
					 //Continuite entre voyelles
					 do{
						 firstLetter=randomConsonne();
					 }while(not followingLetters(firstLetter,temp));
					 
					 do
					  {
						 nextLetter=consonnesRules(firstLetter,false);
						 //creer une syllabe a partir first letter
						 //tester si firstletter et premiere lettre syllabe respecte regle
						 
					  }while(not followingLetters(firstLetter,nextLetter));	      
				 }
				
				else 
				 {
					do{
						firstLetter=randomVoyelle();
					}while(not followingLetters(firstLetter,temp));
					
					
					do
					 {
						nextLetter=voyellesRules(firstLetter,false);
					 }while(not followingLetters(firstLetter,nextLetter));
				 }
				
				
				
			 }
			//Fin syllabes construction
			
			ostringstream os;
			os<<firstLetter<<nextLetter;
			syll=os.str();
			temp=nextLetter;
			
			if( (m_maths.unifRand()<p_addsyll) && (t!=0) && (t!=nbreSyllabe-1))
			 {
				
				syll= syll.substr(0,syll.length()-1);
				syllADD=giveSyllabe(nextLetter);
				Name+=syll; 
				Name+=syllADD;
				temp=returnlast(syllADD);
				nbreFIN++;
			 }
			else if ( (m_maths.unifRand()<p_terminology) && (t==nbreSyllabe-1))
				
			 {
				syll= syll.substr(0,syll.length()-1);
				syllADD=giveTerminaison(nextLetter);
				Name+=syll; 
				Name+=syllADD;
				temp=returnlast(syllADD);
				nbreFIN++;
			 }
			else
			 {
				Name+=syll;
			 }
			
			
			count++;
			//test=threeConsecutives(Name);
		 }//Fin for loop
		
		
		//Check validite nom selon regles imposees
		
		bool3=threeConsecutives(Name);
		bool2=checktwoletters(Name);
		boolcheck=checkAny(Name);
		/*
		 cout<<" "<<endl;
		 cout<<"Nom:"<<Name<<endl;
		 cout<<"2 letters:"<<bool2<<endl;
		 cout<<"3 cons:"<<bool3<<endl;
		 cout<<"check:"<<boolcheck<<endl;
		 cout<<" "<<endl;
		 */
		
		//si on modifie apres le nom, verifier que les parties repsectent les regles de debut!!
		//nbreFIN+=nbreSyllabe;
		
		
		nbreFIN=int(Name.size())/2+1;
		
		if( (randomize<p_modifylong) && (nbreFIN>4) )
		 {
			
			std::size_t pos = int(Name.size()/2);
			std::string::iterator it=Name.begin();      
			
			std::string partA(it,it+pos);
			std::string partB(it+pos,Name.end());
			
			//On rajoute une condition de plus si mon modifie pour accetpter le nom
			//partA est deja checke car debut du mot
			//juste checker partB
			
			if (checktwoletters(partB) ) partBok=true;
			else partBok=false;
			
			if( bool3 && bool2 ) boolgrammar=true;
			else boolgrammar=false;
			
			if(boolgrammar && partBok) boolgrammarsplit=true;
			else boolgrammarsplit=false;
			
			if(boolgrammarsplit && boolcheck) redo=false;
			else redo=true;	   
		 }
		
		else
		 {
			if(bool3 && bool2) boolgrammar=true;
			else boolgrammar=false;
			
			if(boolgrammar && boolcheck) redo=false;
			else redo=true;
		 }
		
     }while(redo);
	
	
	//Nom composé si plus de 5 syllabes:
	// soit tirets, soit particules, soit laisse long
	
	
	// Si assez de syllabes et random: on coupe en deux
	if( ( (randomize<p_modifylong) && (nbreFIN>4)) | (nbreFIN>=6)    ) 
     {
		//cout<<"On modifie le nom "<<Name<<" nbre:"<<nbreFIN<<endl;
		const int NBREPARTC_V=14;
		const int NBREPARTC_C=18;
		
		const std::string particulesV[NBREPARTC_V]={"D'","Van ","Dos ","Von ","Mc ","Mac ","Zum ","Zur ","Im ","Den ","Vom ","Am ","L'","Zuk"};
		const std::string particulesC[NBREPARTC_C]={"De ","Le ","Dos ","Van ","Di ","Von ","Mc","Mac ","O'","Das ","Zum ","Zur ","Im ","Den ","Da ","Lo ","Della ","Des "};
		//coupe au milieu
		std::string liant,liant2;
		
		std::size_t pos = int(Name.size()/2);
		std::string::iterator it=Name.begin();      
		std::string partA(it,it+pos);
		std::string partB(it+pos,Name.end());
		
		std::string minA,minB; 
		minA=partA;
		minB=partB;
		
		
		
		
		
		//Trait d'union, nom composé juste pour les grands noms
		if( nbreFIN>=6) 
		 {
			liant="-";
			partA=CapitalFirst(partA);
			partB=CapitalFirst(partB);
			Name=partA+liant+partB;
		 }
		
		//Nom a particule: plusieurs variantes
		//Soit au debut, soit au milieu, soit les deux
		//depend de la premiere lettre de partA et/ou de partB
		
		
		//debut particule, si nom est compris entre deux tailles
		else if(nbreFIN<6)
		 {
			
			float random=m_maths.unifRand();
			//Au debut
			
			if(random<0.7)
			 {
			 
			 	partA=CapitalFirst(partA);
			 
				char first;
				first=letterType(minA[0]);
				//Si voyelle:
				if(first)
				 {
				 	
				 
					int alea=rand()%NBREPARTC_V;
					liant=particulesV[alea];
					Name=liant+partA+partB;
				 }
				
				else
				 {
					int alea=rand()%NBREPARTC_C;
					liant=particulesC[alea];
					Name=liant+partA+partB;
					
					
				 }
			 }
			
			//Au milieu
			else if( (random<0.9) && (random>0.7))
			 {
				
				char first;
				first=letterType(minB[0]);
				//Si voyelle:
				if(first)
				 {
				 	partA=CapitalFirst(partA);
				 	partB=CapitalFirst(partB);
				 
					int alea=rand()%NBREPARTC_V;
					liant=particulesV[alea];
					Name=partA+" "+liant+partB;
				 }
				
				else
				 {
					int alea=rand()%NBREPARTC_C;
					liant=particulesC[alea];
					Name=partA+" "+liant+partB;
					
					
				 }
				
			 }
			
			//Les deux:
			else
				
			 {
				partA=CapitalFirst(partA);
				partB=CapitalFirst(partB);
				
				
				char first;
				first=letterType(minA[0]);
				//Si voyelle:
				if(first)
				 {
					int alea=rand()%NBREPARTC_V;
					liant=particulesV[alea];
				 }
				
				else
				 {
					int alea=rand()%NBREPARTC_C;
					liant=particulesC[alea];	     	   
				 }
				
				
				first=letterType(minB[0]);
				//Si voyelle:
				if(first)
				 {
					int alea=rand()%NBREPARTC_V;
					liant2=particulesV[alea];
					
				 }
				
				else
				 {
					int alea=rand()%NBREPARTC_C;
					liant2=particulesC[alea];	     
					
				 }
				 
				 Name=liant+partA+" "+liant2+partB;	
			 }  
			
			
		 }//Fin particules
		
		// cout<<"Nom modifié:"<<Name<<endl;
		m_nom=Name;
		
		
     }//fin if modidy
	
	//Sinon laisser intact!
	else
     {
		
		// cout<<"Nom non modifié: "<<Name<<endl;     
		
		Name=CapitalFirst(Name);
		m_nom=Name;
     }
	
}



// renvoie vrai si c est une minuscule, faux sinon
bool NAMEGEN::MajOrmin(char c)
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
int NAMEGEN::charLabel(char c)
{
	
	int label;
	
	
	//voyelle
	if(not letterType(c))
	 {
		 for(unsigned int t=0;t<m_min_consonnes.size();t++)
		 {
			if (c==m_min_consonnes[t])
			 {
				label=t;
				return label;
			 }
		 }
	 }
	//consonne
	else
	 {
		 for(unsigned int t=0;t<m_min_voyelles.size();t++)
		 {
			if (c==m_min_voyelles[t])
			 {
				label=t;
				return label;
			 }
		 }
	 }
	
	return 0;
}



std::string NAMEGEN::giveSyllabe(char c)
{
	string callLetter;
	callLetter.push_back(c);
	return  m_data.appelString(1.,"data/noms/middlesyl.txt",callLetter,"*","*");
}

std::string NAMEGEN::giveTerminaison(char c)
{
	
	string callLetter;
	callLetter.push_back(c);
	return  m_data.appelString(1.,"data/noms/endsyll.txt",callLetter,"*","*");
	
}


//Verifie le nom final en comporant deux a deux les lettres pour determiner si elles respectent toutes les regles:
bool NAMEGEN::checktwoletters(std::string name)
{
	
	int erreurs=0;
	
	for(unsigned int j=0;j<name.size()-1;j++)
	 {
		
		if( j==0)
		 {
			if( not followingLettersBEG(name[j],name[j+1])) erreurs++;
		 }
		
		else
		 {
			if( not followingLetters(name[j],name[j+1])) erreurs++;
		 }
	 }
	
	if(erreurs==0) return true;
	else return false;
	
	
}

// renvoie vrai si il y'a au moins une consonne ou une voyelle dans le nom
bool NAMEGEN::checkAny(std::string name)
{
	int nbreVoyelles=0;
	int nbreConsonnes=0;
	
	for(unsigned int j=0;j<name.size();j++)
	 {
		if(letterType(name[j])) nbreVoyelles++;
		else nbreConsonnes++;
		
	 }
	
	if( (nbreVoyelles != 0) && (nbreConsonnes != 0) ) return true;
	else return false;
	
	
}



// renvoie faux si il existe trois consonnes consecutives dans un nom
bool NAMEGEN::threeConsecutives(std::string name)
{
	
	int a,b,c;
	int forbid=0;
	bool isa,isb,isc; // prend valeur vrai si voyelle, faux si consonne
	
	// if (name.size()-3 >= 0 ) 
	// cout<<name.size()<<endl;
	for(unsigned int j=0;j<name.size()-2;j++)
	 { 
		 //	  cout<<j<<" "<<j+1<<" "<<j+2<<" "<<name.size()<<endl; 
		 isa=letterType(name[j]);
		 a=charLabel(name[j]);
		 
		 isb=letterType(name[j+1]);
		 b=charLabel(name[j+1]);
		 
		 isc=letterType(name[j+2]);
		 c=charLabel(name[j+2]);
		 
		 
		 //Si trois lettres de meme type consecutives:
		 if( (isa && isb && isc) | (not isa && not isb && not isc) ) 
		  { 
			  //Si trois voyelles:
			  if(isa && isb && isc)
			   {
				  //cout<<min_voyelles[a]<<min_voyelles[b]<<min_voyelles[c]<<endl;
				  // SI toutes identiques:
				  if( ( (a == b) && (b==c) ) | (not allowthreeV(m_min_voyelles[a],m_min_voyelles[b],m_min_voyelles[c])) )
				   {
					  //cout<<"3 voyelles successives interdites"<<endl;
					  forbid++;
				   }
				  
			   }
			  
			  //Si trois consonnes:
			  else
				  
			   {
				  //cout<<"3 consonnes"<<endl;
				  
				  // SI toutes identiques ou pas autorisees:
				  if( ( (a == b) && (b==c) ) | (not allowthreeC(m_min_consonnes[a],m_min_consonnes[b],m_min_consonnes[c])) )
				   {
					  //cout<<"Forbid"<<endl;
					  forbid++;
				   }
				  
			   }
		  }
	 }
	//cout<<"forbid:"<<forbid<<endl;
	if(forbid ==0) return true;
	else return false;
}



//Tourne en MAJUSCULE la premiere lettre du string
std::string NAMEGEN::CapitalFirst(std::string name)
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




bool NAMEGEN::allowthreeV(char a,char b,char c)
{
	
	std::string syll;
	ostringstream os;
	os<<a<<b<<c;
	syll=os.str();
	
	for(int j=0;j<EXnbr3V;j++)
     {
		if(syll==allowed3V[j]) return true;
     }
	
	return false;
	
}




bool NAMEGEN::allowthreeC(char a,char b,char c)
{
	
	std::string syll;	
	ostringstream os;
	os<<a<<b<<c;
	syll=os.str();
	
	for(int j=0;j<EXnbr3C;j++)
     {
		if(syll==allowed3C[j]) return true;
     }
	
	return false;
	
}


// renvoie dernier char d'un string
char NAMEGEN::returnlast(std::string name)
{
	char last;
	int sizeName;
	sizeName=name.size();
	
	last=name[sizeName-1];
	
	return last;
}



//appel getData pour recuperer un prenom masculin au hasard:
void NAMEGEN::pickprenomM()
{
	m_prenom=m_data.appelString(1.,"data/prenoms/homme.txt","PRENOM","*","*");	
}
//appel getData pour recuperer un prenom feminin au hasard:
void NAMEGEN::pickprenomF()
{
	m_prenom=m_data.appelString(1.,"data/prenoms/femme.txt","PRENOM","*","*");	
}

std::string NAMEGEN::completeName()
{
	clearall();
	randomName(m_MINSYLLABE,m_MAXSYLLABE);
	pickprenomM();
	return (m_prenom+" "+m_nom);
}


void NAMEGEN::clearall()
{
	m_nom.clear();
	m_prenom.clear();
}


