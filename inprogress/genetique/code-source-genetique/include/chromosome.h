#ifndef CHROMOSOME_H
#define CHROMOSOME_H

//tmp
#include"rng.h"
#include<vector>

class Gene;

class Chromosome{

  public:
    Chromosome(unsigned int nbre_genes,const std::vector<Gene>& population);
    ~Chromosome();
    Gene lire_gene(unsigned int i) const ;
    void afficheContenu() const;

  private:
    std::vector<Gene> genes_;
  //tmp solution
  RandomGenerator rng_;

};

#endif // CHROMOSOME_H
