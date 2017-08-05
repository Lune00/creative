#include<cstdio>
#include<iomanip>
#include<cmath>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>


//Pronoms:
//#define il 0
//#define elle 1
//#define nous 2
//#define vous 3
//#define ils 4
//#define elles 5

//Temps:
#define present 0
#define passe 1
#define futur 2

//Groupe:
#define premier 0
#define deuxieme 1
#define troisieme 2


using namespace std;


//Un mot peut etre un : nom propre, un adjectif, un adverbe, un verbe (regarder Grevisse),preposition, article

//Il faut une structure qui contienne les tables de conjugaison pour chaque temps de tous les pronoms
//Stocke les terminaisons de conjugaison des verbes du premier groupe

struct ConjPremier{

  static map<string,string> makePresent()
  {
    map<string,string> m;
    m["je"] = "e";
    m["tu"] = "es";
    m["il"] = "e";
    m["elle"] = "e";
    m["nous"] = "ons";
    m["vous"] = "ez";
    m["ils"] = "ent";
    m["elles"] = "ent";
    return m;
  }

  static map<string,string> makeFutur()
  {
    map<string,string> m;
    m["je"] = "erai";
    m["tu"] = "eras";
    m["il"] = "era";
    m["elle"] = "era";
    m["nous"] = "erons";
    m["vous"] = "erez";
    m["ils"] = "eront";
    m["elles"] = "eront";
    return m;
  }
  static const map<string,string> present_;
  static const map<string,string> futur_;

};

const map<string,string> ConjPremier::present_ = ConjPremier::makePresent();
const map<string,string> ConjPremier::futur_ = ConjPremier::makeFutur();

//On peut lui donner un type. La forme infinitive stocke le mot, et conjuguer, accorder ne peut s'appliquer que si le mot est du bon groupe
//reflechir a ce point
//Reflechir aux accords, a la structure, pour le moment que verbe


//De l'héritage !!!!!! Verbe herite de mot, Adjectif herite de mot etc... Mais oui bien sur!!!!

class Mot{

  private:
    //Définit le groupe
    string infinitif_;

  public:
    Mot();
    Mot(string infinitif) : infinitif_(infinitif) {} ;
    ~Mot();
    const string& getInfinitif() const { return infinitif_;}

    //Conjugaison
    string getTerminaison();
    int groupe();
    string conjugue(string,int);
    string conjuguepremier(string,int);
};

Mot::Mot(){
  string infinitif_ = " ";
}

Mot::~Mot(){

}

//Recupere la terminaison (deux dernieres lettres) de l'infinitif 
string Mot::getTerminaison(){

  if( ! this->getInfinitif().empty() )
  {
    std::string::size_type size = this->getInfinitif().size();
    std::size_t pos = size - 2 ;
    return this->getInfinitif().substr(pos);

  }
  else
  {
    return string();
  }

}

//Fonction qui determine le groupe a partir de la forme infinitive (les deux dernieres lettres-
int Mot::groupe(){
  string terminaison = this->getTerminaison();
  if(terminaison == "er" ) return premier;
  else if(terminaison == "ir" ) return deuxieme;
  else return troisieme;
}

//Fonction qui en fonction du group (1er, 2e ou 3e) renvoies la conjugaison (pour le moment: passe, present, futur)
string Mot::conjugue(string pronom, int temps){
  //Test si conjuguable ici
  //Fonction groupe:
  if(this->groupe() == 0 ) return this->conjuguepremier(pronom,temps);
  //else if(this->groupe() == 1 ) this->conjuguedeuxieme(pronom,temps);
  //else if(this->groupe() == 2 ) this->conjuguetroisieme(pronom,temps);
  else return string();
}

//Gerer les exceptions (ex manger pour nous)
string Mot::conjuguepremier(string pronom,int temps){
  string mot = this->getInfinitif() ;
  std::string::size_type size = mot.size();
  std::size_t pos = size - 2 ;
  string c = mot.substr(0,pos);
  string term;
  switch(temps){
    case(0): term = ConjPremier::present_.find(pronom)->second;
	     break;
    case(2): term = ConjPremier::futur_.find(pronom)->second;
	     break;
    default : term = string();
	      break;
  }
  c += term ;
  return c;
}

int main()
{

  Mot mot("manger");
  Mot mot2("partir");

  cerr<<"On conjugue le verbe "<<mot.getInfinitif()<<endl;
  cerr<<"Il "<<mot.conjugue("il",present)<<endl;
  cerr<<"Il "<<mot.conjugue("il",futur)<<endl;


  return 0;
}
