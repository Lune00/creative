#include "individu.h"

using namespace std;

int main(){

  const int n = Geneticien::nbre_genes() ;
  const vector<Gene> population = Geneticien::population_genes() ;

  //Creation de 2 individus de sexe opposés
  Individu individu1(0, n, population );
  Individu individu2(1, n, population );

  //Reflechir a generer des descendances et filiations (parents/enfants)
  individu1.affiche_identite_complete();
  individu2.affiche_identite_complete();

  return 0;
}
