#ifndef GENE_H
#define GENE_H

#include<string>

class Gene{

  public:
  //Constructeur par copie ( a partir de la base du Geneticien)
  Gene( const Gene& );
  ~Gene();
  Gene( std::string version , double expression );

  std::string version() const { return version_ ; }
  double expression() const { return expression_; }

  //Debug:
  void affiche_sortie_standard() const;

  private:
  //La version == allele
  //L'expression => contribution a la valeur du trait selon regle de codominance
  std::string version_;
  double expression_;
  //tmp : expression est calculée a partir d'une base nucleique binaire (0 et 1) de 20 éléments irreductibles apportant 0.1
  std::vector<int> base_nucleique_;
};

#endif // GENE_H
