#ifndef GENETICIEN_H
#define GENETICIEN_H

#include<vector>
#include<string>

//Classe statique qui contient: - la banque d'alleles pour chaque gene a introduire dans la population
//                              - les tables de dominance entre alleles
//                              - le calcul de l'expression du phenotype

class Gene ;

class Geneticien{

  public:
    static unsigned int nbre_genes() {return nbre_genes_ ; }
    static std::vector<Gene> population_genes() { return population_genes_ ; }
    static std::vector<Gene> creer_population();

    //Renvoie le nom du gene en fonction de sa position sur le genome (pour l'utilisateur humain)
    static std::string nom_gene(int);
    static double coefficient_codominance(std::string alleleA, std::string alleleB);

  private:
    static const unsigned int nbre_genes_;
    static const std::vector<Gene> population_genes_; 
    //Table de codominance entre les elements de la population, tmp

};



#endif //GENETICIEN_H
