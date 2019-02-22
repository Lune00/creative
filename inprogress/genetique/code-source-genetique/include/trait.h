#ifndef TRAIT_H
#define TRAIT_H

#include<string>
#include<vector>

class Gene;

class Trait{

  public:
    Trait();
    ~Trait();

    std::string nom() const { return nom_ ; }
    double valeur() const { return valeur_ ; }

  private:
    //Label du trait
    std::string nom_;
    //Valeur codée par des genes
    double valeur_;
    //Pointeur sur chaque gene qui code pour lui
    std::vector<Gene*> genes_codant_;
};


#endif // TRAIT_H
