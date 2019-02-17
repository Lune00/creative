#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<fstream>

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
  enum Expression { dominant, recessif};
  //Le caractere est defini seulement par la position dans genes_ du Chromosome
  //donc nous n'avons pas besoin de l'explicité seulement de faire une correspondance
  //               0  1  2  3  4
  enum Caractere { O, C, E, A, N } ;

  public:

  Gene();
  ~Gene();

  bool est_dominant() const { return  expression_ ; }
  //mutation

  private:
  Expression expression_;
  Caractere caractere_;
  double trait_;
  //tmp solution
  RandomGenerator rng_;

};

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Gene::Gene() : rng_()
{
  expression_ =  Expression( rng_.unifRandInt(0,1) ) ;
  trait_ = rng_.unifRand(-1.,1.);
  //Caractere -> implicite -> la position dans le chromosome
}

Gene::~Gene(){}

class Chromosome{

  public:
    Chromosome();
    ~Chromosome();
    //dupliquer
    Gene lire_gene(unsigned int i) const { return genes_[i]; } 

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


class Paire_chromosomes{

  public:
    Paire_chromosomes();
    ~Paire_chromosomes();

    void affiche_genome_exprime();

  private:
    //Chaque gene a une coordonée. ex: "O1" est le gene 0(le 1er) sur le chromosome 1(celui du pere)
    Chromosome chromosome_pere; // chromosome 1
    Chromosome chromosome_mere; // chromosome 2

};

Paire_chromosomes::Paire_chromosomes(){}
Paire_chromosomes::~Paire_chromosomes(){}


//Regles genetiques en lecture:

//Test dominant/recessif: plusieurs cas
//1) Un seul est dominant -> il donne sa valeur au caractere encodé
//2) Les deux sont dominants -> caractere est la moyenne de chaque caractere
//2) Les deux sont recessifs -> caractere est la moyenne de chaque caractere

//Verifier que ca fonctionne bien sur un exemple ou on affiche le geneome brut et le genome exprime
void Paire_chromosomes::affiche_genome_exprime(){

  for(unsigned int i = 0 ; i < 5 ; i++){

    //Recupere les 2 genes du meme caractere:
    Gene i1 = chromosome_pere.lire_gene(i);
    Gene i2 = chromosome_mere.lire_gene(i);

    if(i1.est_dominant() && !i2.est_dominant() ){

    }
    else if(!i1.est_dominant() && i2.est_dominant() ){

    }
    else{
      //i1 est recessif et i2 est recessif ou i1 est dominant et i2 est dominant
    }

  }

}

class Individu{

  enum Sexe { masculin , feminin };

  struct Parents {
    Individu * pere ;
    Individu * mere ;
  };

  public:
  Individu();
  Individu(Parents&);

  //acces au donnees externes:
  std::string recevoir_nom_au_hasard(Sexe);
  std::string recevoir_prenom_au_hasard(Sexe);

  void afficheIdentite() const { std::cout<<prenom_ <<" "<<nom_<<endl; }

  private:
  RandomGenerator rng_;
  string nom_ ;
  string prenom_;
  Sexe sexe_;
  Parents parents_;
  Paire_chromosomes paire_chromosomes;
  
  //Traits phénotypes pours lesquel codent les genes: O C E A N (calculé par l'expression des genes != potentiel genetique)
  double Ouverture_ ;         // -> expression des genes_[0]
  double Conscienciosité_ ;   // -> expression des genes_[1]
  double Extraversion_ ;      // -> expression des genes_[2]
  double Agréabilité_;        // -> expression des genes_[3]    
  double Neuroticisme_ ;      // -> expression des genes_[4]
};


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

//Constructeur par defaut, appelé uniquement a la premiere generation : appel constructeur par defaut de Gene et Chromosome
Individu::Individu(): rng_()
{

  //Assigne un sexe:
  sexe_ = Sexe ( rng_.unifRandInt(0,1) ) ;

  //Assigne un prenom et un nom si pas de parent
  nom_ = recevoir_nom_au_hasard(sexe_);
  prenom_ = recevoir_prenom_au_hasard(sexe_);

  //Initialise un genome par defaut (implicite)

}


Individu::Individu(Parents& parents) : rng_()
{

  // Met un pointeur sur le pere et la mere

  //Assigne un sexe au hasard

  //Prends le nom du pere et assigne un nouveau prenom en fonction de son sexe

}

int main(){

  cout<<"Genetique."<<endl;
  Individu individu;
  individu.afficheIdentite();

  return 0;
}
