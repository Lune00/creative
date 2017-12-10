#ifndef NomC_H
#define NomC_H

#include<map>
#include<string>
#include"Mot.hpp"

using namespace std;

//Classe de nom communs (herite de Mot)
class NomC: public Mot{
  private:
    char genre_;
    char nombre_;
  public:
    NomC(std::string,std::string,int,char,char);
    ~NomC();
    string accorder(string article); // renvoie le bon accord avec l'aricle determinant
};

//Exceptions des Noms Communs (NC): forme plurielle (NCP)
//A completer
struct Exception_NC{

  static map<string,string> makeNPC(){
    std::cout<<"Liste exceptions noms communs..."<<std::endl;
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
