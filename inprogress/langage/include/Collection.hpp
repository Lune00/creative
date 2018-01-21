#ifndef H_categorie_H
#define H_categorie_H

#include<string>
#include<vector>

#include "Mot.hpp"
#include "Verbe.hpp"
#include "NomC.hpp"
#include "Adjectif.hpp"

//Collection est un conteneur repere par un nom(nom de la categorie) et possedant un conteneur de mots
//Ex: par theme, par mode

//On ne se servirait pas de ca plutot pour faire les vecteurs d'adjectifs, verbes, noms? Y reflechir par l'usage...

class Collection{
  private:
    std::string nom_ ;
    vector<Mot*> mots_;
  public:
    Collection(){nom_ = std::string();}
    Collection(std::string nom) : nom_(nom) {};
    ~Collection(){};
    int size () const { return mots_.size(); }
    std::string name() const { return nom_;}
    void addWord(Mot *);
};


#endif
