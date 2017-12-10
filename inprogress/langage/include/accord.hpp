#ifndef NomC_H
#define NomC_H

#include<map>
#include<string>

using namespace std;

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

#endif
