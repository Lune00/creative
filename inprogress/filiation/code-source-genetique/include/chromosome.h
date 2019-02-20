#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome{

  public:
    Chromosome(int nbre_genes,const vector<Gene>& population);
    ~Chromosome();
    Gene lire_gene(unsigned int i) const { return genes_[i]; } 
    void afficheContenu() const;

  private:
    std::vector<Gene> genes_;
  //tmp solution
  RandomGenerator rng_;

};

#endif // CHROMOSOME_H
