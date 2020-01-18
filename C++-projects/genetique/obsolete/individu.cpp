#include "individu.h"
#include "gene.h"
#include "geneticien.h"

#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::ifstream;

void Individu::affiche_phenotype() const {
  cout<<"Ouverture : "<<Ouverture_<<endl;
  cout<<"Conscienciosité : "<<Conscienciosité_<<endl;
  cout<<"Extraversion : "<<Extraversion_<<endl;
  cout<<"Agréabilité : "<<Agreabilité_<<endl;
  cout<<"Neuroticisme : "<<Neuroticisme_<<endl;
}

void Individu::affiche_genome() const 
{ 
  cout<<"----------------------"<<endl;
  cout<<"Chromosome A : "<<endl ;
  chromosome_A_.afficheContenu() ;
  cout<<"Chromosome B : "<<endl ;
  chromosome_B_.afficheContenu() ;
  cout<<"----------------------"<<endl;
}

void Individu::affiche_etat_civil() const {
  std::cout<<"Nom: "<<prenom_<<" "<<nom_<<std::endl ;
}

void Individu::affiche_genome_schema() const
{
  for(int i = 0 ; i < 5 ; i++){
    cout<<chromosome_A_.lire_gene(i).allele()<<" - "<<chromosome_B_.lire_gene(i).allele()<<endl;
  }
}

std::string Individu::recevoir_nom_au_hasard(Sexe s){

  ifstream myfile;
  if (s == masculin ) myfile.open("data/noms/noms_homme.txt");
  else  myfile.open("data/noms/noms_femme.txt");

  std::string line;
  std::vector<std::string> lines;

  if(myfile){
    while(getline(myfile,line)){
      lines.push_back(line);
    }
    myfile.close();
  }

  int random_index = rng_.unifRandInt(0,lines.size()-1);
  return lines[random_index];
}

std::string Individu::recevoir_prenom_au_hasard(Sexe s){

  ifstream myfile;
  if (s == masculin ) myfile.open("data/prenoms/prenoms_homme.txt");
  else  myfile.open("data/prenoms/prenoms_femme.txt");

  std::string line;
  std::vector<std::string> lines;

  if(myfile){
    while(getline(myfile,line)){
      lines.push_back(line);
    }
    myfile.close();
  }

  int random_index = rng_.unifRandInt(0,lines.size()-1);
  return lines[random_index];
}

void Individu::initialisation_phenotype(){
  std::vector<double> traits;
  for(unsigned int i = 0 ; i < Geneticien::nbre_genes() ; i++){
    //Recupere les 2 genes du meme caractere:
    Gene i1 = lire_chromosome_A().lire_gene(i);
    Gene i2 = lire_chromosome_B().lire_gene(i);
    double c = Geneticien::coefficient_codominance( i1.allele(), i2.allele() );
    //cout<<i1.allele()<<" "<<i2.allele()<<" coeff: "<<c<<endl;
    double trait = ( 1. - c ) * i1.trait() + c * i2.trait() ;
    traits.push_back(trait);
  }
  //Eventuellement mettre les traits sous la forme d'un vecteur comme les genes pour une correspondance implicite
  Ouverture_ = traits[0] ;
  Conscienciosité_ = traits[1] ;
  Extraversion_ = traits[2] ;
  Agreabilité_ = traits[3] ;
  Neuroticisme_ = traits[4] ; 
}

//Constructeur par defaut, appelé uniquement a la premiere generation :
Individu::Individu(int nbre_genes, const std::vector<Gene>& population): rng_(), chromosome_A_(nbre_genes, population), chromosome_B_(nbre_genes, population)
{
  //Assigne un sexe:
  sexe_ = Sexe ( rng_.unifRandInt(0,1) ) ;
  //Assigne un prenom et un nom si pas de parent
  nom_ = recevoir_nom_au_hasard(sexe_);
  prenom_ = recevoir_prenom_au_hasard(sexe_);
  //Calcule l'expression de son genome et initialise son phénotype:
  initialisation_phenotype() ;
  //Individu défini. Pret a transmettre son genome.
  return ;
}

//tmp, Constructeur par defaut, appelé uniquement a la premiere generation :
Individu::Individu(int s, int nbre_genes, const std::vector<Gene>& population): rng_(), chromosome_A_(nbre_genes, population), chromosome_B_(nbre_genes, population)
{
  //Assigne un sexe:
  sexe_ = Sexe ( s ) ;
  //Assigne un prenom et un nom si pas de parent
  nom_ = recevoir_nom_au_hasard(sexe_);
  prenom_ = recevoir_prenom_au_hasard(sexe_);
  //Calcule l'expression de son genome et initialise son phénotype:
  initialisation_phenotype() ;
  //Individu défini. Pret a transmettre son genome.
  return ;
}
