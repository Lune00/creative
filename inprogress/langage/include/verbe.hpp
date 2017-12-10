#ifndef H_Verbe_H
#define H_Verbe_H

#include<string>
#include<list>
#include<map>
#include<iostream>

//Temps:
#define present 0
#define passe 1
#define futur 2

//Groupe:
#define premier 0
#define deuxieme 1
#define troisieme 2

using namespace std;

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
    string conjuguertroisieme(string,int);
    string troisiemepresent(string,string);
};

//Liste des verbes irreguliers (troisieme groupe)
struct ListeIrr{
  static list<string> makeliste()
  {
    list<string> l;
    l.push_back("partir");
    l.push_back("courir");
    l.push_back("mourir");
    return l;
  }
  static const list<string> irreguliers;
};

//Stocke les conjugaisons des verbes du troisieme groupe( quand regles)
struct ConjTroisieme{
  //Verbes finissant en -dre , -tre, -cre
  static map<string,string> makePresent_credretre(){
    map<string,string> m;
    m["je"] = "s";
    m["tu"] = "s";
    m["il"] = "";
    m["elle"] = "";
    m["nous"] = "ons";
    m["vous"] = "ez";
    m["ils"] = "ent";
    m["elles"] = "ent";
    return m;
  }
  static map<string,string> makePresent_defaut(){
    map<string,string> m;
    m["je"] = "s";
    m["tu"] = "s";
    m["il"] = "t";
    m["elle"] = "t";
    m["nous"] = "ons";
    m["vous"] = "ez";
    m["ils"] = "ent";
    m["elles"] = "ent";
    return m;
  }
  const static map<string,string> present_credretre;
  const static map<string,string> present_defaut;
};

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

//Stocke les conjugaisons des verbes du deuxieme groupe
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
#endif
