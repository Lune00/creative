#include<list>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>


//A remplacer par des enum

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


//Liste des verbes irreguliers (troisieme groupe)
struct ListeIrr{
  static list<string> makeliste()
  {
    list<string> l;
    l.push_back("partir");
    return l;
  }
  static const list<string> irreguliers;
};

const list<string> ListeIrr::irreguliers = ListeIrr::makeliste();


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


struct ConjDeuxieme{
  static map<string,string> makePresent(){
    map<string,string> m;
    m["je"] = "s";
    m["tu"] = "s";
    m["il"] = "t";
    m["elle"] = "t";
    m["nous"] = "ssons";
    m["vous"] = "ssez";
    m["ils"] = "ssent";
    m["elles"] = "ssent";
    return m;
  }
  static map<string,string> makeFutur(){
    map<string,string> m;
    m["je"] = "ai";
    m["tu"] = "as";
    m["il"] = "a";
    m["elle"] = "a";
    m["nous"] = "ons";
    m["vous"] = "ez";
    m["ils"] = "ont";
    m["elles"] = "ont";
    return m;
  }

  static const map<string,string> present_;
  static const map<string,string> futur_;
};

const map<string,string> ConjDeuxieme::present_ = ConjDeuxieme::makePresent();
const map<string,string> ConjDeuxieme::futur_ = ConjDeuxieme::makeFutur();

//Exceptions des Noms Communs (NC): forme plurielle (NCP)
//A completer
struct Exception_NC{

  static map<string,string> makeNPC(){
    map<string,string> m;
    //En -al
    m["aval"] = "avals";
    m["bal"] = "bals";
    m["carnaval"] = "carnavals";
    m["festival"] = "festivals";
    m["récitals"] = "récitals";
    m["chacal"] = "chacals";
    m["cheval"] = "chevaux";
    //En -ail
    m["travail"] = "travaux";
    //En -ou
    m["bijou"] = "bijoux";
    m["genou"] = "genoux";
    m["caillou"] = "cailloux";

    //Cas particuliers:
    m["oeil"] = "yeux";
    m["ciel"] = "cieux";
    return m;
  }
  static const map<string,string> NCP;
}; 

const map<string,string> Exception_NC::NCP = Exception_NC::makeNPC();

//Mots qui s'accordent: adjectifs et noms communs
class NomC{
  private:
    string mot_;
    //Le genre (auto?)
    char g_;
  public:
    NomC(){};
    NomC(string mot,char g) : mot_(mot), g_(g) {} ;
    ~NomC(){};
    const string& getmot() const {return mot_;}
    string accorder(string article); // renvoie le bon accord avec l'aricle determinant
};


//Renvoie le nom propre avec le bon accord
string NomC::accorder(string article){

  string mot = this->mot_;
  string term ;

  //On regarde si l'article est au pluriel
  if(article.back() == 's') 
  {
    //Regarde si c'est un cas particulier
    std::map<string,string>::const_iterator it =  Exception_NC::NCP.find(mot);
    if(it != Exception_NC::NCP.end()) {
      return it->second;
    }

    //ex : des os
    if(mot.back() == 's' || mot.back() == 'z' || mot.back() == 'x' ) return mot;

    //Checker la taille
    if( mot.size() >= 3)
    {
      string last_one= mot.substr(mot.size()-2);
      string last_two= mot.substr(mot.size()-2);
      string last_three= mot.substr(mot.size()-3);

      //On rajoute un x
      if( last_two == "au" || last_two == "eu" || last_three == "eau") 
      {
	mot += "x";
	return mot;
      }
      //On enleve -al et on remplace par -aux
      else if (last_two == "al") 
      {
	mot = mot.substr(0,mot.size()-2);
	mot += "aux";
	return mot;
      }
      else
      {
	mot += "s";
	return mot;
      }

    }
    else
    {
      //On renvoie avec un s par défaut
      mot += "s";
      return mot;
    }

  }
  else
  {
    return this->mot_;
  }
}


//Mots qui se conjuguernt : verbes
class Verbe{
  private:
    string infinitif_;
  public:
    Verbe();
    Verbe(string infinitif) : infinitif_(infinitif) {} ;
    ~Verbe();
    const string& getInfinitif() const { return infinitif_;}
    string getTerminaison();
    int groupe();
    string conjuguer(string,int);
    string conjuguerpremier(string,int);
    string conjuguerdeuxieme(string,int);
};

Verbe::Verbe(){
  string infinitif_ = " ";
}

Verbe::~Verbe(){

}

//Recupere la terminaison (deux dernieres lettres) de l'infinitif 
string Verbe::getTerminaison(){

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
int Verbe::groupe(){
  //D'abord tester si irregulier (base), sinon tester terminaison
  string mot = this->getInfinitif();
  bool found = ( std::find(ListeIrr::irreguliers.begin(), ListeIrr::irreguliers.end(), mot) != ListeIrr::irreguliers.end());

  if(found){
    return troisieme;
  }
  else{
  string terminaison = this->getTerminaison();
  if(terminaison == "er" ) return premier;
  else if(terminaison == "ir" ) return deuxieme;
  else return 2;
  }
}

//Fonction qui en fonction du group (1er, 2e ou 3e) renvoies la conjugaison (pour le moment: passe, present, futur)
string Verbe::conjuguer(string pronom, int temps){
  //Test si conjuguable ici
  //Fonction groupe:
  if(this->groupe() == 0 ) return this->conjuguerpremier(pronom,temps);
  else if(this->groupe() == 1 ) return this->conjuguerdeuxieme(pronom,temps);
  //else if(this->groupe() == 2 ) this->conjuguertroisieme(pronom,temps);
  else return string();
}

//Gerer les exceptions (ex manger pour nous)
string Verbe::conjuguerpremier(string pronom,int temps){
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

string Verbe::conjuguerdeuxieme(string pronom,int temps){

  string mot = this->getInfinitif() ;

  string c , term;

  switch(temps){
    case(0): c = mot.substr(0,mot.size()-1);
             term = ConjDeuxieme::present_.find(pronom)->second;
	     break;
    case(2): c = mot ; 
	     term = ConjDeuxieme::futur_.find(pronom)->second;
	     break;
    default : term = string();
	      break;
  }
  c += term ;
  return c;
}

int main()
{

  Verbe mot("manger");
  Verbe mot2("partir");

  cerr<<"On conjuguer le verbe : "<<mot.getInfinitif()<<endl;
  cerr<<"Il "<<mot.conjuguer("il",present)<<endl;
  cerr<<"Il "<<mot.conjuguer("il",futur)<<endl;
  cerr<<"On conjugue le verbe : "<<mot2.getInfinitif()<<endl;
  cerr<<"Nous "<<mot2.conjuguer("nous",present)<<endl;
  cerr<<"Nous "<<mot2.conjuguer("nous",futur)<<endl;

  NomC nc("bijou",'m');
  NomC nc1("eau",'f');
  NomC nc2("cheval",'m');
  NomC nc3("vis",'f');
  NomC nc4("ciel",'m');
  NomC nc5("festival",'m');
  NomC nc6("oiseau",'m');

  cerr<<"Des "<<nc.accorder("des")<<endl;
  cerr<<"Des "<<nc1.accorder("des")<<endl;
  cerr<<"Des "<<nc3.accorder("des")<<endl;
  cerr<<"Des "<<nc4.accorder("des")<<endl;
  cerr<<"Des "<<nc5.accorder("des")<<endl;
  cerr<<"Des "<<nc6.accorder("des")<<endl;

  return 0;
}
