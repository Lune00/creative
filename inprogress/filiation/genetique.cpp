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

//Modele 0: l'ensemble des genes sera sur un seul chromosome. Relation de dominance entre alelles

// Modele 0.a: un meme trait phénotypique (O) peut etre codé par 3 genes (avec chacun leur allele) : Oa(allele Oa1 Oa2...) Ob Oc
// Trait = (1-coeffDominance)*effet allele A(gene1) + coeffDImance*effet allele B(gene1)  
//       + (1-coeffDominance)*effet allele A(gene2) + coeffDImance*effet allele B(gene2)
//       / par nombre de genes impliques
// -> Approche de distribution + continue

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
  // Il faut que chaque allele ait un effet fixe (rapport de domination avec l'autre)
  // Attribuer a chaque allele un coefficient de dominance vis a vis d'un autre (allele C1 face a C2 peut se comporter autrement)
  // L'expression d'un gene ne serait plus "dominant" ou "recessif" (un booleen) mais une valeur flottante comprise entre [0:1]
  // Si un trait est codé par un gene et 
  // une relation de dominance entre allele A et B : Trait(valeur) = (1 -coeff dominance)* Effet allele A + (Coeff dominance)* Effet allele B
  // Faire une table de coeff dominance. Ex gene C: allele C1 C2 C3 CoeffDominance(C1,C2)=0 -> C1 domine C2 completement. CoeffDominance(C1,C3)=1 -> C3 domine C1 completement



class Gene{
  //Le caractere est defini seulement par la position dans le vecteur de genes "genes_" de l'objet Chromosome
  //donc nous n'avons pas besoin de l'explicité seulement de faire une correspondance
  //               0  1  2  3  4
  enum Caractere { O, C, E, A, N } ;
  enum Allele { a , b , c };

  public:

  Gene(int);
  ~Gene();

  //debug: affiche juste un entier
  Caractere lire_caractere() const { return caractere_ ; }

  private:
  //Version du gene
  Caractere caractere_;
  Allele allele_;
  //Valeur du trait pour lequel le gene code
  double trait_;

  //tmp solution
  RandomGenerator rng_;

};

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Gene::Gene(int i) : rng_()
{
  //expression_ =  Expression( rng_.unifRandInt(0,1) ) ;
  trait_ = rng_.unifRand(-1.,1.);
  //Caractere -> implicite -> la position dans le chromosome/ On l'appuie en initialisant avec la position i du gene dans le chromosome
  caractere_ = Caractere ( i ) ;
}

Gene::~Gene(){}

class Chromosome{

  public:
    Chromosome(int);
    ~Chromosome();
    //dupliquer
    Gene lire_gene(unsigned int i) const { return genes_[i]; } 
    void afficheContenu() const;

  private:
    std::vector<Gene> genes_;

};

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Chromosome::Chromosome(int nbre_genes){
  for(unsigned int i = 0 ; i < nbre_genes ; i++){
    Gene gene(i);
    genes_.push_back(gene);
  }
}

Chromosome::~Chromosome(){
  genes_.clear();
}

void Chromosome::afficheContenu() const{
  for(vector<Gene>::const_iterator it = genes_.begin() ; it != genes_.end() ; it++){
    cout<<it->lire_caractere()<<endl;
  }
}

class Individu{

  struct Parents {
    Individu * pere ;
    Individu * mere ;
  };

  enum Sexe { masculin , feminin };

  public:
  Individu(int nbre_genes);
  //Individu(Parents&);

  //acces au donnees externes:
  std::string recevoir_nom_au_hasard(Sexe);
  std::string recevoir_prenom_au_hasard(Sexe);

  Chromosome lire_chromosome_A() const { return chromosome_A_ ; } 
  Chromosome lire_chromosome_B() const { return chromosome_B_ ; } 
  void afficheIdentite() const { std::cout<<prenom_ <<" "<<nom_<<endl; }

  private:
  //tmp
  RandomGenerator rng_;

  string nom_ ;
  string prenom_;
  Sexe sexe_;

  Parents parents_;
  //Genome: pour l'instant diploide
  Chromosome chromosome_A_ ;
  Chromosome chromosome_B_ ;

  //Traits phénotypes pours lesquel codent les genes, la paire de chromosomes: O C E A N (calculé par l'expression des genes != potentiel genetique)
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
Individu::Individu(int nbre_genes): rng_(), chromosome_A_(nbre_genes), chromosome_B_(nbre_genes)
{

  //Assigne un sexe:
  sexe_ = Sexe ( rng_.unifRandInt(0,1) ) ;

  //Assigne un prenom et un nom si pas de parent
  nom_ = recevoir_nom_au_hasard(sexe_);
  prenom_ = recevoir_prenom_au_hasard(sexe_);

  //Initialise un genome par defaut (implicite)

  //Calcule l'expression de son genome et initialise son phénotype (arguments passés par reference pour etre modifié directement)

  //Individu défini. Pret a transmettre son genome.
  return ;
}

//Constructeur pour generation ayant des parents (toutes sauf la premiere lors de l'initialisation de la population)
//Individu::Individu(Parents& parents) : rng_()
//{
//
//  // Met un pointeur sur le pere et la mere
//
//  //Assigne un sexe au hasard
//
//  //Prends le nom du pere et assigne un nouveau prenom en fonction de son sexe
//
//}

//class INTERFACE
//Classe statique qui contient: la banque d'alleles pour chaque gene a introduire dans la population
//                              les tables de dominance entre alleles
//                              le calcul de l'expression du phenotype
class Geneticien{

  public:
    //Calcul l'expression du genome et le phenotype resultant associé
    //Arguments? Retourne quoi? Interface avec Individu?
    void traduction_genome_en_phenotype(Individu&);
    static int nbre_genes() {return nbre_genes_ ; }
  private:
    static const int nbre_genes_;;

};

const int Geneticien::nbre_genes_  = 5 ;

//Verifier que ca fonctionne bien sur un exemple ou on affiche le geneome brut et le genome exprime
void Geneticien::traduction_genome_en_phenotype(Individu& individu){

  for(unsigned int i = 0 ; i < 5 ; i++){
    //Recupere les 2 genes du meme caractere:
    Gene i1 = individu.lire_chromosome_A().lire_gene(i);
    Gene i2 = individu.lire_chromosome_B().lire_gene(i);

  }

}

int main(){

  const int n = Geneticien::nbre_genes() ;

  cout<<"Genetique."<<endl;
  Individu individu(n);
  individu.afficheIdentite();

  Chromosome chromosome(n);
  chromosome.afficheContenu();

  return 0;
}
