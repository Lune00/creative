#ifndef GENETICIEN_H
#define GENETICIEN_H

//Classe statique qui contient: - la banque d'alleles pour chaque gene a introduire dans la population
//                              - les tables de dominance entre alleles
//                              - le calcul de l'expression du phenotype

class Geneticien{

  public:
    static int nbre_genes() {return nbre_genes_ ; }
    static vector<Gene> population_genes() { return population_genes_ ; }
    static vector<Gene> creer_population();

    //Renvoie le nom du gene en fonction de sa position sur le genome (pour l'utilisateur humain)
    static string nom_gene(int);
    static double coefficient_codominance(char alleleA, char alleleB);

  private:
    static const int nbre_genes_;
    static const vector<Gene> population_genes_; 
    //Table de codominance entre les elements de la population, tmp

};



#endif //GENETICIEN_H
