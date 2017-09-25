#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

#define mylibrary "mylibrary.txt"

//Les doublons sont gérés (normalement) par la librairie elle-meme.
//Inutile donc en pratique de devoir traiter le cas des doublons ici.

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
    string grammar_;
    string infover_;
    string genre_;
    string accord_;
    int nsyll_;

    std::vector<string> registre_;
    std::vector<string> syn_;
    std::vector<string> ass_;
    std::vector<string> themes_;

  public:
    Mot();
    Mot(string);
    ~Mot();
    string getmot() {return mot_;}
};

Mot::Mot(){};


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
  grammar_ = tokens[3];
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
  registre_ = parsestring(tokens[8],delimiter);
  syn_ = parsestring(tokens[9],delimiter);
  ass_ = parsestring(tokens[10],delimiter);
  themes_ = parsestring(tokens[11],delimiter);
};

Mot::~Mot(){};

//class Librairie{
//  private:
//    std::vector<Mot> noms_;
//    std::vector<Mot> adjectifs_;
//    std::vector<Mot> verbes_;
//  public:
//    Librairie();
//    ~Librairie();
//};
//
//Librairie::Librairie(){};
//Librairie::~Librairie(){};


// MAIN

int main(){

  cout<<"Bonjour poésie."<<endl;
  std::vector<Mot> corpus;
  ifstream mylib(mylibrary);

  while(true){
    string entree;
    getline(mylib,entree);
    if (mylib.eof() ) break;
    //Chaque entree (entree) de la librairie est contenue dans entree
    //Il faut maintenant la splitter pour en faire un mot, constructeur mot
    Mot mot = Mot(entree);
    corpus.push_back(mot);
  };
  cout<<"Corpus: "<<corpus.size()<<" mots."<<endl;
  for(vector<Mot>::iterator it = corpus.begin() ; it != corpus.end() ; it++ ){
    cout<<it->getmot()<<endl;
  }
}
