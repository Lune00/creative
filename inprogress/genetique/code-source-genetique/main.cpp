#include "individu.h"

//TEST du code source

using namespace std;

int main(){

  //
  const int n = Geneticien::nbre_genes() ;
  const vector<Gene> population_genes = Geneticien::population_genes() ;

  //Creation de 2 individus de sexe opposés
  Individu individu1(0, n, population_genes );
  individu1.affiche_identite_complete();

  return 0;
}
