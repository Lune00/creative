#ifndef GENE_H
#define GENE_H

#include<string>
#include<vector>

class Trait;

class Gene{

  public:

  private:
    std::string name_;
    int baseNucleique_[20];
    //Trait pour lequel il code
    Trait * trait_ ;
};

#endif // GENE_H
