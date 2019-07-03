#ifndef GENE_H
#define GENE_H

#include<string>
#include<vector>
#include"config.h"

class Trait;

class Gene{

  public:
    Gene() ;

  private:
    std::string name_;
    // Nucleic sequence ( size == geneticParameters::geneSize )
    int * nucleicSequence_ ;
    // Point to the feature for which it codes
    Trait * trait_ ;
};

#endif // GENE_H
