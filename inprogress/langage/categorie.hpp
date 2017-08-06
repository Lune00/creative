#ifndef H_categorie_H
#define H_categorie_H

#include<string>
#include<vector>
#include "verbe.hpp"
#include "accord.hpp"
#include "adjectif.hpp"

using namespace std;
//Conteneur repere par un nom(nom de la categorie) et possedant un conteneur de Verbes, d' Accords...
//Ex feu : on pourrait avoir une categorie Feu qui contient les verbes, les adjectifs, les noms propres etc...
//Ex deplacement : sous categorie discret, rapide. Où placer sous categorie?
class Categorie{
  private:
  string nom_ ;
  vector<Verbe> verbes_;
  vector<NomC> nomsC_;
  public:
  Categorie(){nom_ =" ";}
  Categorie(string nom) : nom_(nom) {};
  ~Categorie(){};
};




#endif
