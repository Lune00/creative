#include<list>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>

#include"verbe.hpp"


//A remplacer par des enum

//Pronoms:
//#define il 0
//#define elle 1
//#define nous 2
//#define vous 3
//#define ils 4
//#define elles 5



using namespace std;

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
    NomC(){mot_ =""; g_='m';}
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

int main()
{

  Verbe mot("hair");
  Verbe mot2("mourir");
  Verbe mot3("s'envoler");

  cerr<<"On conjuguer le verbe : "<<mot.getInfinitif()<<endl;
  cerr<<"Il "<<mot.conjuguer("il",present)<<endl;
  cerr<<"Il "<<mot.conjuguer("il",futur)<<endl;
  cerr<<"On conjugue le verbe : "<<mot2.getInfinitif()<<endl;
  cerr<<"Il "<<mot2.conjuguer("il",present)<<endl;

  NomC nc("bijou",'m');
  NomC nc1("eau",'f');
  NomC nc2("cheval",'m');
  NomC nc3("vis",'f');
  NomC nc4("ciel",'m');
  NomC nc5("festival",'m');
  NomC nc6("oiseau",'m');

  cerr<<"Des "<<nc1.accorder("des")<<endl;
  cerr<<"Des "<<nc3.accorder("des")<<endl;
  cerr<<"Des "<<nc6.accorder("des")<<" "<<mot3.conjuguer("ils",futur)<<" dans les "<<nc4.accorder("les")<<"."<<endl;
  cerr<<"Ils nous "<<mot.conjuguer("ils",present)<<"."<<endl;

  return 0;
}
