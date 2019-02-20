#include "chromosome.h"

using namespace std;

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Chromosome::Chromosome(int nbre_genes,const vector<Gene>& population): rng_()
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
  for(vector<Gene>::const_iterator it = genes_.begin() ; it != genes_.end() ; it++){
    int position = it - genes_.begin() ;
    string nom_gene = Geneticien::nom_gene (position ) ;
    cout<<"Gene : "<< nom_gene<<" ";
    it->afficheContenu();
  }
}
