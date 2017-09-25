#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

#define mylibrary "mylibrary.txt"

//Les doublons sont gérés (normalement) par la librairie elle-meme.
//Inutile donc en pratique de devoir traiter le cas des doublons ici.

//TODO
//Fonction qui renvoie un mot terminant par la phonetique souhaitee
//Fonction qui renvoie les mots par classe grammaticale

using namespace std;


// Global functions
vector<std::string> parsestring(string, string);


vector<std::string> parsestring(string stringtoparse, string delimiter)
{
  vector<std::string> tokens;
  size_t pos = 0 ;
  string token;
  while( (pos = stringtoparse.find(delimiter)) != std::string::npos)
  {
    token = stringtoparse.substr(0, pos);
    stringtoparse.erase(0, pos + delimiter.length());
    tokens.push_back(token);
  }
  //On rajoute la derniere entree (ce qu'il reste)
  tokens.push_back(stringtoparse);
  
  //On retire les caracteres vides (dus au formatage en bash)
  //On place tous les caracteres vides a la fin de string et on se place au premier caractere vide
  //puis on supprime jusqu'a la fin (algorithm)
  for(vector<std::string>::iterator it = tokens.begin() ; it != tokens.end() ; it++ ){
    it->erase(std::remove_if(it->begin(), it->end(), ::isspace), it->end());
  }

  return tokens;
}


// Class / Templates

class Mot{

  private:

    string mot_;
    string lemme_;
    string phon_;
    string infover_;
    string genre_;
    string accord_;
    int nsyll_;

    std::vector<string> grammar_;
    std::vector<string> registre_;
    std::vector<string> syn_;
    std::vector<string> ass_;
    std::vector<string> themes_;

    static const string phon_table[];

  public:
    Mot();
    Mot(string);
    ~Mot();
    string getmot() {return mot_;}
    string getgrammar();
    string getlastphoneme() {char last = phon_.back(); string last_s(1,last); return last_s;}
};


const string Mot::phon_table[]={
"a","i","y","u","o","O","e","E","°","2","9","5","1","@","§","3","j","8","w","p","b","t","d","k","g","f","v","s","z","Z","m","n","N","I","R","x","G","S","l"};


Mot::Mot(){};

string Mot::getgrammar(){
  string gram;
  for (vector<std::string>::iterator it = grammar_.begin() ; it != grammar_.end(); it++)
  {
    gram += *it;
    gram +=" ";
    }  
  return gram;
} 


//Constructeur d'un mot avec une entree de la bibliotheque
//L'ordre des champs est donne par le formatage de la librairie (libconfig.sh)
//Il doit y avoir 12 champs!
Mot::Mot(string entree)
{
  vector<string> tokens = parsestring(entree,"\t");
  vector<string>::iterator it = tokens.begin();

  if( tokens.size() < 12 ) {
    cerr<<"Entrée ne contient pas 12 champs!"<<endl;
    return;
  }

  mot_  = tokens[0];
  lemme_= tokens[1];
  phon_ = tokens[2];
  infover_ = tokens[4];
  genre_ = tokens[5];
  accord_= tokens[6];

  if(tokens[7].length() == 0 ) 
  {
    nsyll_ = 0 ; //WTF, ca ne devrait pas etre autorise dans librairie!
  }
  else
  {
    nsyll_ = stoi(tokens[7]);
  }
  //Vecteur et split
  string delimiter = ";";
  grammar_ = parsestring(tokens[3],",");
  registre_ = parsestring(tokens[8],delimiter);
  syn_ = parsestring(tokens[9],delimiter);
  ass_ = parsestring(tokens[10],delimiter);
  themes_ = parsestring(tokens[11],delimiter);
};

Mot::~Mot(){};

//Fonction qui renvoie un vecteur de mots qui se terminent par la phoneme phoneme
vector<Mot> return_last_phon_liste(vector<Mot>& corpus, string phoneme)
{
  //Checker dans table phonemes... todo
  vector<Mot> liste;
  for(vector<Mot>::iterator it = corpus.begin(); it != corpus.end() ; it++){
    if( it->getlastphoneme() == phoneme) liste.push_back(*it);
  }
  return liste;
}

// MAIN

int main(){

  cout<<"Bonjour poésie."<<endl;
  std::vector<Mot> corpus;
  ifstream mylib(mylibrary);

  //Lecture de la librairie
  while(true){
    string entree;
    getline(mylib,entree);
    if (mylib.eof() ) break;
    //Chaque entree (entree) de la librairie est contenue dans entree
    //Il faut maintenant la splitter pour en faire un mot, constructeur mot
    Mot mot = Mot(entree);
    corpus.push_back(mot);
  };


  vector<Mot> liste = return_last_phon_liste(corpus,"n");
  //Operations:
  for(vector<Mot>::iterator it = liste.begin() ; it != liste.end() ; it++ ){
    cout<<it->getmot()<<endl;
  }
}
