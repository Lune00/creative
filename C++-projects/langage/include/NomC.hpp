#ifndef NomC_H
#define NomC_H

#include<map>
#include<string>
#include"Mot.hpp"


//Classe de nom communs (herite de Mot)
class NomC: public Mot{
  private:
    char genre_;
    char nombre_;
  public:
    NomC(std::string,std::string,int,char,char);
    ~NomC();
    std::string accorder(std::string article); // renvoie le bon accord avec l'aricle determinant
    virtual int nature() const { return NOMC_ ; }

};

//Exceptions des Noms Communs (NC): forme plurielle (NCP)
//A completer
struct Exception_NC{

  static std::map<std::string,std::string> makeNPC(){
    std::cout<<"Liste exceptions noms communs..."<<std::endl;
    std::map<std::string,std::string> m;
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
  static const std::map<std::string,std::string> NCP;
}; 

#endif
