#include<iostream>
#include<string>
#include<vector>
#include<random>

//---------------------------  BUT DU PROGRAMME --------------------------------
//Heritage de traits personnels encodés par des genes
//Un couple de personnages donnera naissance a des enfants
//qui heriteront de leurs genes
//Pour definir les traits on utilisera le modele OCEAN (5 traits de personalité) => 5 genes
//https://fr.wikipedia.org/wiki/Modèle_des_Big_Five_(psychologie)
//Chaque trait a une valeur comprise entre -1 et +1
//La transmission se fait comme un processus de meyose ordinaire
//---------------------------  BUT DU PROGRAMME --------------------------------

//Modele 0: l'ensemble des genes sera sur un seul chromosome
//          Un meme gene (par exemple O) peut exister sous la forme dominat ou recessif

//Modele 1: introduire des mutations

//Modele 2: mettre les genes sur differents chromosomes pour enrichir le brassage

//1: Generer des couples homme/femme avec chacun : un nom,un prenom, un chromosome avec genes aleatoires (voir dans le dossier data)

using namespace std;


class RandomGenerator{
  public:
    RandomGenerator();
    double unifRand(int,int);
    int unifRandInt(int,int);
  private:
  std::default_random_engine generator_;

};

RandomGenerator::RandomGenerator(): generator_((std::random_device())()) 
{}

double RandomGenerator::unifRand(int a, int b){
  std::uniform_real_distribution<double> distribution(a,b);
  return distribution(generator_);
}
int RandomGenerator::unifRandInt(int a, int b){
  std::uniform_int_distribution<int> distribution(a,b);
  return distribution(generator_);
}

//--------------



class Gene{

  friend class RandomGenerator;
  enum Expression { dominant, recessif};
  //Le caractere est defini seulement par la position dans genes_ du Chromosome
  //donc nous n'avons pas besoin de l'explicité seulement de faire une correspondance
  //               0  1  2  3  4
  enum Caractere { O, C, E, A, N } ;

  public:

  Gene();
  ~Gene();
  private:
  Expression expression_;
  Caractere caractere_;
  double trait_;
  //tmp solution
  RandomGenerator rng_;

};

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Gene::Gene(): rng_() {

  expression_ =  Expression( rng_.unifRandInt(0,1) ) ;
  trait_ = rng_.unifRand(-1.,1.);
  //Caracter -> implicite -> la position dans le chromosome

}

Gene::~Gene(){
}


class Chromosome{

  public:
    Chromosome();
    ~Chromosome();

  private:
    std::vector<Gene> genes_;

};

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Chromosome::Chromosome(){
  for(unsigned int i = 0 ; i < 5 ; i++){
    Gene gene;
    genes_.push_back(gene);
  }
}

Chromosome::~Chromosome(){
  genes_.clear();
}

class Individu{

  enum Sexe { masculin , feminin };

  struct Parents {
    Individu * pere ;
    Individu * mere ;
  };

  struct Chromosome_pair {
    Chromosome chromosome_pere;
    Chromosome chromosome_mere;
  };

  public:
  Individu();
  Individu(Parents&);

  //acces au donnees externes:
  std::string recevoir_nom_au_hasard(Sexe);
  std::string recevoir_prenom_au_hasard(Sexe);

  private:
  RandomGenerator rng_;
  string nom_ ;
  string prenom_;
  Sexe sexe_;
  Parents parents_;
  Chromosome_pair chromosome_pair_;
};


std::string Individu::recevoir_nom_au_hasard(Sexe s){


  return string();

}

std::string Individu::recevoir_prenom_au_hasard(Sexe s){


  return string();

}

//Constructeur par defaut, appelé uniquement a la premiere generation : appel constructeur par defaut de Gene et Chromosome
Individu::Individu(): rng_()
{

  //Assigne un sexe:
  sexe_ = Sexe ( rng_.unifRandInt(0,1) ) ;

  //Assigne un prenom et un nom si pas de parent
  nom_ = recevoir_nom_au_hasard(sexe_);
  prenom_ = recevoir_prenom_au_hasard(sexe_);

}




Individu::Individu(Parents& parents) : rng_()
{

  // Met un pointeur sur le pere et la mere

  //Assigne un sexe au hasard

  //Prends le nom du pere et assigne un nouveau prenom en fonction de son sexe

}



int main(){

  cout<<"Genetique."<<endl;
  Chromosome chromosome;

  return 0;
}
