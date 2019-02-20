#include "geneticien.h"

using namespace std;

const int Geneticien::nbre_genes_  = 5 ;
const vector<Gene> Geneticien::population_genes_ = Geneticien::creer_population() ;

//Creation de la base de genes initiaux:
vector<Gene> Geneticien::creer_population(){
  vector<Gene> population;

  //Chaque gene a les memes alleles pour le moment
  Gene gene1( 'a' , -1. );
  Gene gene2( 'b' , 0. );
  Gene gene3( 'c' , 1. );

  population.push_back(gene1);
  population.push_back(gene2);
  population.push_back(gene3);

  return population;
}

//A mettre dans un tableau pour gagner en compacité:
//Renvoie le coefficient de codominance (% expression chaque allele) entre 2 alleles
double Geneticien::coefficient_codominance(char alleleA, char alleleB){
  //Le coefficient de codominance est commutable => c(a,b)=c(b,a)
  double a_b = 0.3 ;
  double a_c = 1.0 ;
  double b_c = 0.5 ;
  if( alleleA == alleleB ) return 1. ;
  else if  (alleleA == 'a' && alleleB == 'b') return a_b ;
  else if  (alleleA == 'b' && alleleB == 'a') return ( 1. - a_b ) ;
  else if  (alleleA == 'a' && alleleB == 'c') return a_c ;
  else if  (alleleA == 'c' && alleleB == 'a') return ( 1. - a_c ) ;
  else if  (alleleA == 'b' && alleleB == 'c') return b_c ;
  else if  (alleleA == 'c' && alleleB == 'b') return ( 1. - b_c ) ;
  else return 0. ;
}

//Attribue un nom aux genes par rapport a leur position sur le chromosome (for human and readability)
string Geneticien::nom_gene(int position){
  switch(position){
    case 0 : return string("0");
	     break;
    case 1 : return string("C");
	     break;
    case 2 : return string("E");
	     break;
    case 3 : return string("A");
	     break;
    case 4 : return string("N");
	     break;
    default : return string("Error!"); 
  }
}


