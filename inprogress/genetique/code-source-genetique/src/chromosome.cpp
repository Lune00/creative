#include "chromosome.h"
#include "gene.h"
#include "geneticien.h"
#include<string>
#include<iostream>

Gene Chromosome::lire_gene(unsigned int i ) const
{
  return genes_[i];
}

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Chromosome::Chromosome(unsigned int nbre_genes,const std::vector<Gene>& population): rng_()
{
  for(unsigned int i = 0 ; i < nbre_genes ; i++){
    //Pour chaque gene on donne une allele au hasard issue de la population: 
    unsigned int random_index = rng_.unifRandInt(0,population.size()-1);
    Gene gene = population[random_index] ;
    genes_.push_back(gene);
  }
}

Chromosome::~Chromosome(){
  genes_.clear();
}

void Chromosome::afficheContenu() const{
  for(std::vector<Gene>::const_iterator it = genes_.begin() ; it != genes_.end() ; it++){
    unsigned int position = it - genes_.begin() ;
    std::string nom_gene = Geneticien::nom_gene (position ) ;
    std::cout<<"Gene : "<< nom_gene<<" ";
    it->afficheContenu();
  }
}
