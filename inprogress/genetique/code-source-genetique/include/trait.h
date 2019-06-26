// Phenotype trait
#ifndef TRAIT_H
#define TRAIT_H
#include<string>
#include<vector>

class Trait{

  public:
  // D : Discrete (ex : color of the eyes) C : Continuous value of the trait (ex : height)
  enum Nature { D = 0 ; C = 1 } ;

  private:

    std::string name_;
    Nature nature_ ;
    //Raw phenotype value lies in the interval [-1:1]. Have to be rescaled my min/max to represents a quantity with a meaning and unit.
    double value_;
    //The value of the phenotype must lie in the interval [valueMin_:valueMax_]
    double valueMin_;
    double valueMax_;
    //Number of genes to code for the trait
    unsigned int nGenes_;
};


#endif // TRAIT_H
