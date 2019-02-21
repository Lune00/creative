#include "gene.h"
#include<iostream>

//Un gene ne peut etre construit que par copie (transmission du gene), une copie de la base du Geneticien.
Gene::Gene(const Gene& gene) : rng_()
{
  allele_ = gene.allele_ ;
  trait_ = gene.trait_ ;
}

Gene::Gene( char allele, double trait)
{
  allele_ = allele;
  trait_ = trait ;
}

void Gene::afficheContenu() const{
  std::cout<<"Allele : "<<allele_<<" Trait : "<<trait_<<std::endl;
}

Gene::~Gene(){}
