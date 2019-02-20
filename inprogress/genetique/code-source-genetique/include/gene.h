#ifndef GENE_H
#define _GENE_H

class RandomGenerator;

class Gene{
  public:
  //Constructeur par copie ( a partir de la base du Geneticien)
  Gene(const Gene&);
  ~Gene();
  //Pour l'instant chaque gene a les memes alleles (le caractere est automatiquement assigné?)
  Gene( char allele , double trait);

  char allele() const { return allele_ ;}
  double trait() const { return trait_;}
  void afficheContenu() const;

  private:
  //attribue un entier (coordonne dans table de codominance) et une valeur flottante au trait_
  char allele_;
  double trait_;

  //tmp solution : mettre static TODO
  RandomGenerator rng_;

};

#endif // GENE_H
