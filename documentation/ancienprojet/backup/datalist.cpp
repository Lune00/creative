#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<algorithm>
#include<cstring>

#include "datalist.h"
#include "arithmetique.h"

#ifndef WIN32
#include <sys/types.h>
#endif

using namespace std;
 
// F FEMINNI
// M MASCULIN
// P PLURIEL
// S SINGULIER
// i INFINITIF
// pP PRESENT FORME POSITIVE
// pN PRESENT FORME NEGATIVE
// FP FEMININ PLURIEL
// MP MASCULIN PLURIEL
// FS FEMININ SINGULIER
// MS MASCULIN SINGULIER
// * AUCUN(UNE SEULE COLONNE DANS DATA)
// ! MEME QUE MOT PRINCIPAL SI EXISTE

const std::string DATA::m_descripteurs[13]={"F","M","i","pP","pN","*","P","S","FP","MP","FS","MS","!"};

//CONSTRUCTEUR PAR DEFAUT
DATA::DATA(): m_maths()
{
  m_DIR="data";
  make_allPATHS();
  call_init_separateur();
  call_init_noms();
}

DATA::~DATA()
{
  
}




//INITIALISATION DES INDEXS
//RAJOUTER ICI DE NOUVEAUX INDEXS


// Permet de savoir si ent pointe sur un repertoire ou un fichier
// HYPOTHESE: PRESENCE D'UN . indique un fichier
// renvoie 1 si c'est un repertoire, 0 si c'est un fichier
int DATA::isSubdir(struct dirent* ent) 
{
  if( (strchr(ent->d_name,'.'))==NULL)
         return 1;
  else 
    return 0; //c 'est un fichier
}



//Construit l'arborescence des fichiers de data(A FAIRE ARBORESCENCE SI BESOIN,REFLECHIR)
//Initialise les INDEX (données membres de DATA);
void DATA::make_allPATHS()
{
  std::vector<std::string> SUBDIR_TEMP;
  std::vector<std::string> FAMILLE_TEMP;
  
  const std::string str_MAINDIR="data";  
  const char* MAINDIR = str_MAINDIR.c_str();
  
  DIR* rep= NULL; // pointeur sur un repertoire
  // DIR* subdir=NULL; //pointeur sur un sous repertoire
  
  struct dirent* replu= NULL; // pointeur sur la structure dirent
  
  rep=opendir(MAINDIR);
  
  //existence de data
  if(rep==NULL)
    {
      cout<<"@acces au dossier data"<<endl;
      perror("");
      cout<<"Lancer le programme dans le dossier où se trouve le dossier data"<<endl;
      exit(0);
    }
  
  //LISTE TOUS LES SUBDIRS:
  
  while( (replu=readdir(rep)) !=NULL)
    {  
      //ENLEVE . et ..
      if(strcmp(replu->d_name,".") != 0 && strcmp(replu->d_name,"..") != 0)
        {	
	  //EST CE UN SOUS repertoire?
	  if(isSubdir(replu)==1)
	    {
	      // printf("'%s':\n",replu->d_name);
              
	      SUBDIR_TEMP.push_back(replu->d_name);
              
              //OUI? on regarde dedans: ???
              
	      std::string str_LP=str_MAINDIR+"/"+replu->d_name;
	      const char* LP = str_LP.c_str();
              
	      DIR* subrep=NULL;
	      subrep=opendir(LP);
              
	      if(subrep==NULL)
                {
                  perror("");
                  exit(0);       
                }
	      
	      //LISTE TOUS LES FICHIERS (FAMILLE)
              
	      while( (replu=readdir(subrep)) !=NULL)
		{ 
		  if(strcmp(replu->d_name,".") != 0 && strcmp(replu->d_name,"..") != 0)
		    {
		      if(isSubdir(replu)==0)   
			{//printf("\t%s\n",replu->d_name);
			  //ENLEVER L'EXTENSION:
			  std::string word=replu->d_name;
                          
			  int lastindex = word.find_last_of("."); 
			  std::string rawname = word.substr(0, lastindex);
			  word=rawname;
                          
			  FAMILLE_TEMP.push_back(word);
			}
		    }
		}
              
              
	      closedir(subrep);
	    }         
	  
	  else
	    continue;
	  
	}
      else
	continue;
      
    }  
  
  
  //Initialisation des indexs:
  init_index_SUBDIR(SUBDIR_TEMP);
  init_index_FAMILLE(FAMILLE_TEMP);
  
}


void DATA::call_init_noms()
{ 
  m_NOMS.push_back("SUBDIR");
  m_NOMS.push_back("FAMILLE");
}


void DATA::call_init_separateur()
{
  m_separateur="\n***************\n";
}


//initialise les données membres

void DATA::init_index_SUBDIR(std::vector<std::string> m_SUBDIR_temp)
{
  m_SUBDIR=m_SUBDIR_temp; 
}

void DATA::init_index_FAMILLE(std::vector<std::string> m_FAMILLE_temp)
{
  m_FAMILLE=m_FAMILLE_temp; 
}



//renvoie les données membres
const std::string DATA::get_index_DIR()
{
  return m_DIR; 
}

const std::vector<std::string> DATA::get_index_SUBDIR()
{
  return m_SUBDIR; 
}

const std::vector<std::string> DATA::get_index_FAMILLE()
{
  return m_FAMILLE; 
}



//affiche un index en particulier a l'ecran
void DATA::print_index(std::string INDEX_NAME)
{
  if( INDEX_NAME=="DIR")
    {
      cout<<"MAIN DIR:"<<m_DIR<<endl;
    }
  
  else if (INDEX_NAME=="SUBDIR")
    {
      cout<<m_separateur;
      cout<<"Liste SUBDIR:";
      cout<<m_separateur;
      for(std::vector<std::string>::const_iterator run=m_SUBDIR.begin();run!=m_SUBDIR.end();++run)
	{
	  cout<<"\t"<<*run<<endl;
	}
      
    }
  
  else if (INDEX_NAME=="FAMILLE")
    {
      cout<<m_separateur;
      cout<<"Liste FAMILLE:";
      cout<<m_separateur;
      for(std::vector<std::string>::const_iterator run=m_FAMILLE.begin();run!=m_FAMILLE.end();++run)
	{
	  cout<<"\t"<<*run<<endl;
	}
      
    }
  
  else
    
    {
      cout<<"@index introuvable,stop"<<endl;
      exit(0);
    }
  
}

//affiche tous les index disponibles a l'ecran
void DATA::print_all_index()
{
  for(std::vector<std::string>::const_iterator run=m_NOMS.begin();run!=m_NOMS.end();++run)
    {
      print_index(*run);
    }  
}

//check si DIR demandé existe,renvoie vrai si oui, shutdown sinon
bool DATA::existDir(std::string dir)
{
  
  if ( dir== m_DIR )
    {
      return true;
      
    }
  
  else
    {
      cout<<"@index "<<dir<<" introuvable,stop"<<endl;
      exit(0);
    }
  
  
  return 0;
}

//check si SUBDIR demandé existe,renvoie vrai si oui, shutdown sinon
bool DATA::existSubdir(std::string subdir)
{
  
  std::vector<std::string>::const_iterator run;
  
  run=find(m_SUBDIR.begin(),m_SUBDIR.end(),subdir);
  
  if ( run !=m_SUBDIR.end() )
    {
      return true;
      
    }
  
  else
    {
      cout<<"@index "<<subdir<<" introuvable,stop"<<endl;
      exit(0);
    }
  
  
  return 0;
}

//check si FAMILLE demandé existe,renvoie vrai si oui, shutdown sinon
bool DATA::existFamille(std::string famille)
{
  
  std::vector<std::string>::const_iterator run;
  run=find(m_FAMILLE.begin(),m_FAMILLE.end(),famille);
  
  if ( run !=m_FAMILLE.end() )
    {
      return true;
    }
  
  else
    {
      cout<<"@index "<<famille<<" introuvable,stop"<<endl;
      exit(0);
    }
  
  
  return 0;
}


//creer le path pour acceder au fichier demander par display
std::string DATA::makepath(std::string dir,std::string subdir,std::string famille)
{
  std::string path,whichDIR,whichSUBDIR,whichFAMILLE;
  std::string extension;
  std::vector<std::string>::const_iterator run;
  path.clear();
  extension=".txt";
  
  
  if(existDir(dir))
    {
      whichDIR=m_DIR;
    }
  
  if(existSubdir(subdir))
    {
      run=find(m_SUBDIR.begin(),m_SUBDIR.end(),subdir);
      whichSUBDIR=*run;
    }
  
  if(existFamille(famille))
    {
      run=find(m_FAMILLE.begin(),m_FAMILLE.end(),famille);
      whichFAMILLE=*run;
    }
  
  
  path = whichDIR + "/" + whichSUBDIR + "/" + whichFAMILLE + extension;
  
  if(checkpath(path)) return path;
  else
    {
      cout<<"@makepath: "<<path<<" introuvable! Verifier le path -stop."<<endl;
      //afficher l'arborescence en guise de rappel
      exit(0);
    }
  
}


//Check l'existence du fichier path
bool DATA::checkpath(const std::string& path)
{
  std::ifstream in(path.c_str()); 
  return !in.fail();
}




std::vector<std::string> DATA::getData(const std::string& path, std::vector<std::string> ID,std::vector<std::string> OPTIONS,std::string DESCRITPEUR)
{
  
  if(!checkpath(path))
    {
      cout<<"@get Data ne peut acceder a "<<path<<",attention -stop"<<endl;
      exit(0);
      
    }
  
  std::ifstream read(path.c_str());
  std::string line_code,data;
  std::vector<std::string> wordslist,finaldata;
  std::size_t POS_DES;
  
  int i=0;
  
  while(std::getline(read,line_code))
    {
	
	  cout<<"ligne en cours:"<<line_code<<endl;
	
      std::size_t POS_START = line_code.find("@START");
	  
      if(POS_START!=std::string::npos)
	{
	  
	  for(std::vector<std::string>::const_iterator run=ID.begin();run!=ID.end();++run)
	    {
		cout<<"dans id: "<<*run<<endl;
	      //On trouve une ID, alors on s'arrête,on regarde les options, et on stocke
	      std::size_t POS_ID=line_code.find(*run);
		  
	      if( (POS_ID!=std::string::npos) | (*run=="*") )
		{
		  //ON REGARDE SI ON TROUVE DES OPTIONS,SI OPTIONS EST VIDE("*") ON PREND
		  for(std::vector<std::string>::const_iterator runOPT=OPTIONS.begin();runOPT!=OPTIONS.end();++runOPT)
		    {
			cout<<"dans options"<<*runOPT<<endl;
		    //cout<<*run<<" "<<*runOPT<<" "<<line_code<<endl;
			
			
			
			
			
			
			
		      std::size_t POS_OPT=line_code.find(*runOPT);
			  
		   // ID OK ET UNE OPTION OK,ou pas d'option on prend
		      if( (POS_OPT!=std::string::npos) | (*runOPT=="*") )
			{
			  	POS_DES=line_code.find("#");
			  i++;
			  
			  if(POS_DES!=std::string::npos)
			    {
					
			  cout<<i<<endl;
				
			//Renvoie quelle colonne prendre (descripteur donné) parmi la liste descripteurs possibles(parmi les colonnes)
				cout<<"Id: "<<*run<<endl;
				cout<<"Option: "<<*runOPT<<endl;

				m_colonne=get_colonne(line_code,DESCRITPEUR);
				 
				cout<<"getcolone ok"<<endl;
				 
			    }
			  
			  else
			    {
				
				cout<<i<<endl;
				  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			      cout<<"@pas de balise descripteur #!"<<endl;
			      cout<<"path:"<<path<<endl;
			      cout<<"ligne:"<<line_code<<endl;
				  cout<<"m_colonne="<<m_colonne<<endl;
				  cout<<"ID="<<*run<<endl;
				  cout<<"OPTION="<<*runOPT<<endl;
				  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			      exit(0);
			    }
			  
			 
			  std::size_t POS_END;
			  
			  int i=0;
			  
			  do
			    {
			      i++;
			      std::getline(read,line_code);
			      POS_END = line_code.find("@END");
			      if(POS_END==std::string::npos)
				{
				  wordslist.push_back(line_code);
				}
			      
				  if(i>1e9) 
				  {
					 cout<<"@getData: impossible de trouver la fin de la liste '@END'!"<<endl;
					 exit(0);
				  }
				  
				  
				  
			    }while(POS_END==std::string::npos);
			  
			  
			   
			  
			}
		      
		      //Si les options match pas, on ne prend pas,si options n'est pas vide
		      else
			{
			 
			  continue;
			  
			}
		      
		    }
		  
		  
		} // fin ID loop
	      
	      else // on regarde l'ID SUIVANTE
		
		{ 
		 cout<<"id "<<*run<<" pas trouvé option"<<endl;
		  continue;
		}
	      
	      
	    }
	  
	  
	}
      
    }
  
  
  if(wordslist.size()==0)
  {
	 cout<<"@getData -> Impossible de trouver ID ou OPTIONS dans le path "<<path<<endl;
	 exit(0);
  }
  
  
  
  return wordslist;
  
}


std::vector<std::string> DATA::makeList(std::string word,std::vector<std::string> wordparametres)
{
	std::vector<std::string> finalWORDSLIST;
		
	finalWORDSLIST.push_back(word);
	//Construction liste finale : premier mot appelé + mots parameteres definis
		for(std::vector<std::string>::const_iterator run=wordparametres.begin();run!=wordparametres.end();++run)
		 {
			finalWORDSLIST.push_back(*run);
		 }
	return finalWORDSLIST;
}


std::string DATA::appelString(float Prob,const std::string& path,std::string ID,std::string OPTIONS,std::string DESCRITPEURS)
{
	//cout<<"APPEL"<<endl;
	bool isParam;
	
	checkProb(Prob);
	std::vector<std::string> phrase,callword,VEC_ID,VEC_OPTIONS;
	std::string OneWord;
	
	VEC_ID.push_back(ID);
	VEC_OPTIONS.push_back(OPTIONS);
	
	
	std::string words,first,line,parametre,finalword;
	std::vector<std::string> wordslist,parameters,all,ALL;
	
	finalword.clear();
	
	//1er appel,liste faite des mots appelés:
	wordslist=getData(path,VEC_ID,VEC_OPTIONS,DESCRITPEURS);
	//Prends un mot dans la liste:

	//Prends un au hasard
	line=pickInlist(wordslist);
	//	cout<<"LINE appel:"<<line<<endl;
	//Prends le mot dans la bonne colonne(appell takeDes)
	first=takeFirst(line);
	
	//cout<<"Premier mot:"<<first<<endl;
	//Ajoute
	all.push_back(first);

	//cout<<"Before boucle"<<endl;

	do
	{
	//cout<<++i<<endl;
	//cout<<"in boucle"<<endl;
	
	
	cout<<line<<endl;
	
	//Check si y'a des parametres:
	isParam=isParameters(line);
	
	if(isParam)
	{
	   
	   if(checkParameters(line))
	   {
	   
	   
	   		line=takeLine(line);
	   
		  //fait liste des mots a appeler
		  parameters=makeParametersList(line);
		  
		  for(std::vector<std::string>::const_iterator run=parameters.begin();run!=parameters.end();++run)
		   {
		   //	
		   			//Liste des mots appelés(appel de get data et maj de m_colonne):
					
					cout<<"forParam"<<endl;
					cout<<"parameter:"<<*run<<endl;
					cout<<"alo"<<endl;
		   			wordslist=readParameters(*run);
					cout<<"alo"<<endl;
			  		line=pickInlist(wordslist);
					
					cout<<"line:"<<line<<endl;
					
			  		//Prends le mot dans la bonne colonne:
			  		first=takeFirst(line);
					//cout<<"mot ajouté:"<<first<<endl;
					all.push_back(first);
					
					isParam=isParameters(line);
					cout<<"isP?"<<isParam<<endl;

		   }
		  
	   }
	   
	   
	}
	
	
	
	
	}while(isParam);
	
	ALL.push_back(all[0]);
	
	
	//faire attention, car ici le deuxiement mot appelé peut etre refusé et le troisieme accepté etc...
	for(std::vector<std::string>::const_iterator run=all.begin()+1;run!=all.end();++run)
	 {
	 	
	 	if(m_maths.unifRand()<Prob) 
		 {
			ALL.push_back(*run);
		 }
	 	
		else
		{
		   break;
		}
	 }
	
	//cout<<makeAstring(ALL)<<endl;
	
	if(ALL.size()==0) 
	{
	   cout<<"@erreur,retour ALL vide!"<<endl;
	   exit(0);
	}
	
	return makeAstring(ALL);
	
}

// A surcharger en appel, pour faire des appels avec des vecteurs de Id et options

std::vector<std::string> DATA::appelVector(float Prob,const std::string& path,std::string ID,std::string OPTIONS,std::string DESCRITPEURS)
{
	//cout<<"APPEL"<<endl;
	bool isParam;
	
	checkProb(Prob);
	
	std::vector<std::string> phrase,callword,VEC_ID,VEC_OPTIONS;
	std::string OneWord;
	
	VEC_ID.push_back(ID);
	VEC_OPTIONS.push_back(OPTIONS);
	
	
	std::string words,first,line,parametre,finalword;
	std::vector<std::string> wordslist,parameters,all,ALL;
	
	finalword.clear();
	
	//1er appel,liste faite des mots appelés:
	wordslist=getData(path,VEC_ID,VEC_OPTIONS,DESCRITPEURS);
	//Prends un mot dans la liste:
	
	//Prends un au hasard
	line=pickInlist(wordslist);
	//	cout<<"LINE appel:"<<line<<endl;
	//Prends le mot dans la bonne colonne(appell takeDes)
	first=takeFirst(line);
	
	//cout<<"Premier mot:"<<first<<endl;
	//Ajoute
	all.push_back(first);
	
	//cout<<"Before boucle"<<endl;
	
	do
	 {
		//cout<<++i<<endl;
		//cout<<"in boucle"<<endl;
		
		//Check si y'a des parametres:
		isParam=isParameters(line);
	
		cout<<line<<endl;
		if(isParam)
		 {
			
			if(checkParameters(line))
			 {
			 
			 	//Prendre la sous ligne (séparée par point-virgule) qui correspond a la bonne colonne pour lire que ces parametres:
				
				line=takeLine(line);
			 
			 //	cout<<"line:"<<line<<endl;
			 
				//fait liste des mots a appeler
				parameters=makeParametersList(line);
				
				for(std::vector<std::string>::const_iterator run=parameters.begin();run!=parameters.end();++run)
				 {
					//cout<<"parameter:"<<*run<<endl;
		   			//Liste des mots appelés(appel de get data et maj de m_colonne):
		   			wordslist=readParameters(*run);
					
			  		line=pickInlist(wordslist);
					
			  		//Prends le mot dans la bonne colonne:
			  		first=takeFirst(line);
					//cout<<"mot ajouté:"<<first<<endl;
					all.push_back(first);
					
					isParam=isParameters(line);
					cout<<"isP?"<<isParam<<endl;
				 }
				
			 }
			
			
		 }
		
		
	 }while(isParam);
	
	ALL.push_back(all[0]);
	
	if(m_maths.unifRand()<Prob) 
	{
	
	for(std::vector<std::string>::const_iterator run=all.begin()+1;run!=all.end();++run)
	 {
			ALL.push_back(*run);
	 }
	 
	 }
	 
	
	
	if(ALL.size()==0) 
	 {
		cout<<"@erreur,retour ALL vide!"<<endl;
		exit(0);
	 }
	 
	//cout<<"resultat="<<makeAstring(all)<<endl;
	
	return ALL;
	
}


//renvoie la liste des parametres sur une ligne dans l'ordre d'appel:

std::vector<std::string> DATA::makeParametersList(std::string word)
{
  std::vector<std::string> parameters;
  std::size_t POS_FIRST;
  std::size_t POS_LAST;

  
 	 //Construit la liste parametres pour appels:
      do
		{ 
	  	POS_FIRST=word.find("[");     
	  	POS_LAST=word.find("]");  
	  
	  	if(POS_FIRST!=std::string::npos)  
	    	{
	      	if(POS_LAST!=std::string::npos)
				{
		  			int parameterlength = POS_LAST-(POS_FIRST+1);
					  parameters.push_back(word.substr(POS_FIRST+1,parameterlength));
				//DEPLACER POS FIRST JUSTE APRES LA FERMETURE POUR VOIR SI AUTRE OPTION
					  word=word.substr(POS_LAST+1);
				}
	    	} 
	  
	  	
	  
		}while(POS_FIRST!=std::string::npos);  
		
  return parameters;
  
}


//appelle get_data et renvoie la nouvelle liste de mots définies par les parametres
std::vector<std::string> DATA::readParameters(std::string parameter)
{
  
  std::vector<std::string> p_options;
  std::vector<std::string> p_id;
  std::vector<std::string> p_des;
  std::size_t POS_SEP,POS_SUM;
  
  std::string subdir;
  std::string famille;
  std::string path;
  std::string descripteur,copy;
  
  //RAJOUTER DECOUPAGE POUR UN NOMBRE DIFFERENTS D OPTIONS  OU D ID A SELECTIONNERx
  
  copy=parameter;
  
  //PRENDS LE PREMIER QUAND RECURSIF
  
  cout<<"Parameter:"<<parameter<<endl;
  
  
  POS_SEP=parameter.find(",");
  subdir=parameter.substr(0,POS_SEP);
  parameter=parameter.substr(POS_SEP+1);
  
  POS_SEP=parameter.find(",");
  famille=parameter.substr(0,POS_SEP);
  parameter=parameter.substr(POS_SEP+1);
  
 
  POS_SEP=parameter.find(",");
  
  std::string temp;
  
  //on travaille la dessus
  temp=parameter.substr(0,POS_SEP);
  
	do 
	 {
		POS_SUM=temp.find("/");
		
		if(POS_SUM!=std::string::npos)
		{
		    p_id.push_back(temp.substr(0,POS_SUM));
			temp=temp.substr(POS_SUM+1);
		}
		
		else
		
		{
			 p_id.push_back(temp.substr(0,POS_SUM));
		}
		
		
		
	 }while(POS_SUM!=std::string::npos);
	 
  
 //On repart sur parameter(rest chaine)
 
  parameter=parameter.substr(POS_SEP+1);
  POS_SEP=parameter.find(",");
  
	//on travaille la dessus
	temp=parameter.substr(0,POS_SEP);
	
	do 
	 {
		POS_SUM=temp.find("/");
		
		if(POS_SUM!=std::string::npos)
		 {
		    p_options.push_back(temp.substr(0,POS_SUM));
			temp=temp.substr(POS_SUM+1);
		 }
		
		else
			
		 {
			p_options.push_back(temp.substr(0,POS_SUM));
		 }
		
		
		
	 }while(POS_SUM!=std::string::npos);
  
  parameter=parameter.substr(POS_SEP+1);
  POS_SEP=parameter.find(",");
  
	temp=parameter.substr(0,POS_SEP);
  

  descripteur=parameter.substr(0,POS_SEP);
  
	do 
	 {
		POS_SUM=descripteur.find("/");
		
		if(POS_SUM!=std::string::npos)
		 {
		    p_des.push_back(descripteur.substr(0,POS_SUM));
			descripteur=descripteur.substr(POS_SUM+1);
		 }
		
		else
			
		 {
			p_des.push_back(descripteur.substr(0,POS_SUM));
		 }
		
		
	 }while(POS_SUM!=std::string::npos);
  
  
  //parameter=parameter.substr(POS_SEP+1);
  
  //Construit le patch et check:
  
  //check les tailles:
  
  path=makepath(m_DIR,subdir,famille);
  
  cout<<"path="<<path<<endl;
  
  if( (p_des.size()!= p_options.size()) | (p_des.size()!= p_id.size()) | (p_des.size()!= p_id.size()) )
  {
	 cout<<"@erreur pickupword, nombre de paramètres ne correspondent pas:"<<endl;
	 cout<<"path:"<<path<<" "<<copy<<endl;
	 cout<<"ID size:"<<p_id.size()<<endl;
	 cout<<"OPTIONS size:"<<p_options.size()<<endl;
	 cout<<"DES size:"<<p_des.size()<<endl;
	 exit(0);
	 
  }
  
	//Checkpath, est associatif avec la famille:
	
	if(!checkpath(path))
	 {
		cout<<"@get_parameter: impossible de trouver le path "<<path<<endl;
		exit(0);
	 }
	
	
	
  std::vector<std::string> all,ALL;
  
	for(std::vector<std::string>::const_iterator run=p_des.begin();run!=p_des.end();++run)
	 {
	 cout<<*run<<endl;
		cout<<"appel de getData"<<endl;
	all=getData(path,p_id,p_options,*run);
	
	
	cout<<"all done"<<endl;
	
	
		for(std::vector<std::string>::const_iterator run=all.begin();run!=all.end();++run)
		{
			cout<<*run<<endl;
		
		   ALL.push_back(*run);
		}
		

	 }
	 
	 return ALL;
	
  
}


//RENVOIE un entier qui est la colonne correspondant au descripteur demande s'il existe pour le couple (ID,OPTION),erreur sinon
int DATA::get_colonne(std::string line,std::string requestDES)
{
  int colonne;
  std::size_t POS_BEGIN,POS_END;
  std::string subline;
  std::vector<std::string> descripteurs;
  std::string test;
  subline=line;
  int t=0;
  //cout<<"request DES:"<<requestDES<<endl;
  //cout<<"line:"<<subline<<endl;
  do
    {
      //EXTRACTION DESCRIPEUR dans l'ordre, donc l'ordre des elements dans le vecteur donne l'ordre des colonnes et permet de recuperer la bonne colonne désirée
      POS_BEGIN=subline.find("/");
      subline=subline.substr(POS_BEGIN+1);
      POS_END=subline.find("/");
      descripteurs.push_back(subline.substr(0,POS_END));
      test=subline.substr(0,POS_END);
      subline=subline.substr(POS_END+1);
	  subline.insert(0,"/");
	  
	  
	  
    } while (POS_END!=std::string::npos);
  
  
  
  //CHECK DESCRIPTEUR
  for(std::vector<std::string>::const_iterator run=descripteurs.begin();run!=descripteurs.end();++run)
    {
      //BOUCLE SUR DESCRIPTEURS MEMBRES m_descripteurs,attention a la taille
      for(unsigned int i=0;i<13;i++)
        {
	  
	//  cout<<*run<<" "<<m_descripteurs[i]<<endl;
          
	  if(*run==m_descripteurs[i]) t++;
          
        }
      
    }
  
  //cout<<t<<" "<<descripteurs.size()<<endl;
  
  //Si chaque element lu n'a pas d'équivalent dans la base membre c'est qu'il y a une erreur:
  if(t!=descripteurs.size())
    {
      cout<<"@erreur descripteur format inconnu, sur la ligne "<<line<<endl;
      exit(0);
      
    }
  
  
  
  //LA FONCTION NE DIT PAS ENCORE SI LE DESCRIPTEUR DEMANDE CORRESPOND A UN DESCRIPTEUR DANS LA BALISE
  //IL FAUDRAIT COMPARER A LA BASE DE DONNEES
  
  //RENvoie la position (et donc la colonne) du descripteur desiré
  
  bool trouve=false;
  
 // cout<<"request des="<<requestDES<<endl;
  
  for(std::vector<std::string>::const_iterator run=descripteurs.begin();run!=descripteurs.end();++run)
    {
      if(*run==requestDES)
	{
	  
	  colonne=run-descripteurs.begin();
	  trouve=true;
          
          
	}
      
    }
  
  
  if(trouve)
    {
      return colonne+1;
    }
  
  else
    {
      cout<<"@erreur descripteur "<<requestDES<<" non existant sur la ligne"<<line<<endl;
      exit(0);
    }
  
  
}
std::string DATA::takeLine(std::string line)
{
	
	//cout<<"line:"<<line<<endl;
	
	std::string linetocut,linetocut2;
	std::size_t POS_FIRST;
	std::string word;
	
	int nbrecolonnes=1;
	int colonne=m_colonne;
	int count=0;
	linetocut=line;
	
	POS_FIRST=linetocut.find(";");
	
	//COMPTER LE NOMBRE DE COLONNES:(=nbre virgules +1)
	
	while (POS_FIRST!=std::string::npos)
		
	 {
		nbrecolonnes++;
		linetocut=linetocut.substr(POS_FIRST+1);
		POS_FIRST=linetocut.find(";");
	 }
	
	//S'assure qu'on trouve le mot parmi les colonnes existantes
	
	if( (colonne > nbrecolonnes) | (colonne< 0) )
	 {
		cout<<"@erreur pickupword, colonne demandée n'existe pas pour le mot: "<<word<<endl;
	 }
	
	
	linetocut=linetocut2=line;
	do
	 {
		POS_FIRST=linetocut2.find(";");
		linetocut=linetocut2.substr(0,POS_FIRST); //premier mot
		linetocut2=linetocut2.substr(POS_FIRST+1); //reste
		count++;
		
		
	 }
	while(colonne!=count);
	
	//PREMIER MOT APPELE:
	word=linetocut;
	
	return word;
	
}



std::string DATA::takeDes(std::string line)
{

	//cout<<"line:"<<line<<endl;

  std::string linetocut,linetocut2;
  std::size_t POS_FIRST;
  std::string word;
  
  int nbrecolonnes=1;
  int colonne=m_colonne;
  int count=0;
  linetocut=line;
  
  POS_FIRST=linetocut.find(",");
  
  //COMPTER LE NOMBRE DE COLONNES:(=nbre virgules +1)
  
  while (POS_FIRST!=std::string::npos)
    
    {
      nbrecolonnes++;
      linetocut=linetocut.substr(POS_FIRST+1);
      POS_FIRST=linetocut.find(",");
	  
	 
    }
  
  //S'assure qu'on trouve le mot parmi les colonnes existantes
  
  if( (colonne > nbrecolonnes) | (colonne< 0) )
    {
      cout<<"@erreur pickupword, colonne demandée n'existe pas pour le mot: "<<word<<endl;
    }
  
  
  linetocut=linetocut2=line;
  do
    {
      POS_FIRST=linetocut2.find(",");
      linetocut=linetocut2.substr(0,POS_FIRST); //premier mot
      linetocut2=linetocut2.substr(POS_FIRST+1); //reste
      count++;
	  
    }
  while(colonne!=count);
  
  //PREMIER MOT APPELE:
  word=linetocut;
  
  return word;
  
}

std::string DATA::makeAstring(std::vector<std::string> list)
{
	std::string phrase;
	phrase+=list[0];
	
	if(list.size()!=1)
	 {
		
		int i=0;
		
		for(std::vector<std::string>::const_iterator run=list.begin()+1;run!=list.end();++run)
		 {
		 	i++;
			if(i<2) phrase+=" "+*run;
		 	else phrase+=" "+*run;
		 }  
	 }
	
	//phrase=phrase.substr(0,phrase.size()-1);
	
	return phrase;
}


std::string DATA::takeFirst(std::string word)
{
	std::size_t POS_FIRST;
	POS_FIRST=word.find("[");
	word=takeLine(word);
	
	if(POS_FIRST!=std::string::npos)
	{
	   return word.substr(0,POS_FIRST);
	}
	else
	{
	   return word;
	}
}

bool DATA::checkParameters(std::string word)
{
	
	std::size_t POS_FIRST,POS_CHECK_LEFT,POS_CHECK_RIGHT;
	std::size_t POS_LAST;
	std::string wordcheck;
	wordcheck=word;
	
	if(isParameters(word))
	 {
		do
		 {
			POS_FIRST=wordcheck.find("["); 
			POS_LAST=wordcheck.find("]");
			
			if( (POS_FIRST!=std::string::npos) ^ (POS_LAST!=std::string::npos))
			 {
				cout<<"@pickup_word error, missing or extra [ or ] on the word "<<endl;
				cout<<"'"<<word<<"'"<<endl;
				exit(0);       
			 }
			
			std::string temp = wordcheck.substr(POS_FIRST+1,POS_LAST-(POS_FIRST+1));
			
			POS_CHECK_LEFT=temp.find("[");
			POS_CHECK_RIGHT=temp.find("]");
			if( (POS_CHECK_LEFT!=std::string::npos) |  (POS_CHECK_RIGHT!=std::string::npos) ) 
			 {
				cout<<"@pickup_word error, missing or extra [ or ] on the word "<<endl;
				cout<<"'"<<word<<"'"<<endl;
				exit(0);     
			 }
			
			wordcheck=wordcheck.substr(POS_LAST+1);
			

		 }while(( (POS_FIRST!=std::string::npos) | (POS_FIRST!=std::string::npos)));
		 
	
		 return true;
		 
	 }
	 
	 else
	 {
		return false;
	 }
}


bool DATA::isParameters(std::string line)
{
	std::size_t POS_FIRST;
	
	//TEST SI Y A APPELANTS SUR LE MOT CHOISI:
	POS_FIRST=line.find("[");
	
	if(POS_FIRST!=std::string::npos) return true;
	else return false;
	
}


std::string DATA::pickInlist(std::vector<std::string> wordslist)
{
	//Prendre un element au hasard
	int random = rand()%wordslist.size();
	return wordslist[random];	
}


void DATA::checkProb(float Prob)
{
	if (Prob < 0. | Prob>1. )
	{
	   cout<<"@Erreur, p="<<Prob<<" dans appel()"<<endl;
	   exit(0);
	}
}

