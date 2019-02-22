#include "gene.h"
#include<iostream>

//Un gene ne peut etre construit que par copie (transmission du gene), une copie de la base du Geneticien.
Gene::Gene(const Gene& gene)
{
  version_ = gene.version_ ;
  expression_ = gene.expression_ ;
}

Gene::Gene( std::string allele, double trait)
{
  version_ = allele;
  expression_ = trait ;
}

void Gene::affiche_sortie_standard() const{
  std::cout<<" version : "<<version_<<" valeur d'expression : "<<expression_<<std::endl;
}

Gene::~Gene(){}
