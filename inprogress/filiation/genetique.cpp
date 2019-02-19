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


//Variable global, tmp
//Le caractere est defini seulement par la position dans le vecteur de genes "genes_" de l'objet Chromosome
//               0  1  2  3  4
//Seul des genes de meme caractere peuvent etre mis en rapport (correspond a la position dans le chromosome)

//enum Caractere { O, C, E, A, N } ;

class Gene{
  public:
  //Constructeur par copie ( a partir de la base du Geneticien)
  Gene(const Gene&);
  ~Gene();
  //Pour l'instant chaque gene a les memes alleles (le caractere est automatiquement assigné?)
  Gene( char allele , double trait);

  char lire_allele() const { return allele_ ;}
  double lire_trait_() const { return trait_;}
  void afficheContenu() const;

  private:
  //attribue un entier (coordonne dans table de codominance) et une valeur flottante au trait_
  char allele_;
  double trait_;

  //tmp solution : mettre static TODO
  RandomGenerator rng_;

};

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
  cout<<"Allele : "<<allele_<<" Trait : "<<trait_<<endl;
}

Gene::~Gene(){}

class Chromosome{

  public:
    Chromosome(int nbre_genes,const vector<Gene>& population);
    ~Chromosome();
    Gene lire_gene(unsigned int i) const { return genes_[i]; } 
    void afficheContenu() const;

  private:
    std::vector<Gene> genes_;
  //tmp solution
  RandomGenerator rng_;

};

//Constructeur par defaut (seulement appelé a l'initiation de la premiere generation)
Chromosome::Chromosome(int nbre_genes,const vector<Gene>& population): rng_()
{

  for(unsigned int i = 0 ; i < nbre_genes ; i++){
    //Pour chaque gene on donne une allele au hasard issue de la population: 
    unsigned int random_index = rng_.unifRandInt(0,population.size()-1);
    Gene gene = population[random_index] ;
    genes_.push_back(gene);
  }
}

Chromosome::~Chromosome(){
  genes_.clear();
}


class Individu{

  struct Parents {
    Individu * pere ;
    Individu * mere ;
  };

  enum Sexe { masculin , feminin };

  public:
  Individu(int nbre_genes, const vector<Gene>& population);
  //Individu(Parents&);

  //acces au donnees externes:
  std::string recevoir_nom_au_hasard(Sexe);
  std::string recevoir_prenom_au_hasard(Sexe);

  Chromosome lire_chromosome_A() const { return chromosome_A_ ; } 
  Chromosome lire_chromosome_B() const { return chromosome_B_ ; } 

  //Affichage:
  void affiche_etat_civil() const { std::cout<<"Nom: "<<prenom_ <<" "<<nom_<<endl; }
  void affiche_genome() const ;
  void affiche_phenotype() const {} ;
  void affiche_identite_complete() const { affiche_etat_civil() ; affiche_genome() ; affiche_phenotype();}

  private:
  //tmp (a mettre en static)
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

void Individu::affiche_genome() const 
{ 
  cout<<"----------------------"<<endl;
  cout<<"Chromosome A : "<<endl ;
  chromosome_A_.afficheContenu() ;
  cout<<"Chromosome B : "<<endl ;
  chromosome_B_.afficheContenu() ;
  cout<<"----------------------"<<endl;
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
    static vector<Gene> population_genes() { return population_genes_ ; }
    static vector<Gene> creer_population();

    //Renvoie le nom du gene en fonction de sa position sur le genome (pour l'utilisateur humain)
    static string nom_gene(int);
 
  private:
    static const int nbre_genes_;
    static const vector<Gene> population_genes_; 
    //Table de codominance entre les elements de la population, tmp
    double coefficient_codominance(char alleleA, char alleleB);

};

const int Geneticien::nbre_genes_  = 5 ;

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

//Renvoie le coefficient de codominance (% expression chaque allele) entre 2 alleles
double Geneticien::coefficient_codominance(char alleleA, char alleleB){

  if( alleleA == alleleB ) return 1. ;
  else if ( (alleleA ==  'a' && alleleB == 'b') || (alleleA == 'b' && alleleB == 'a') ) return 0.3 ;
  else if ( (alleleA ==  'a' && alleleB == 'c') || (alleleA == 'c' && alleleB == 'a') ) return 1.0 ;
  else if ( (alleleA ==  'b' && alleleB == 'c') || (alleleA == 'c' && alleleB == 'b') ) return 0.5 ;
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

void Chromosome::afficheContenu() const{
  for(vector<Gene>::const_iterator it = genes_.begin() ; it != genes_.end() ; it++){
    int position = it - genes_.begin() ;
    string nom_gene = Geneticien::nom_gene (position ) ;
    cout<<"Gene : "<< nom_gene<<" ";
    it->afficheContenu();
  }
}

  //expression_ =  Expression( rng_.unifRandInt(0,1) ) ;
  //trait_ = rng_.unifRand( -1. , 1. );

const vector<Gene> Geneticien::population_genes_ = Geneticien::creer_population() ;

//Verifier que ca fonctionne bien sur un exemple ou on affiche le geneome brut et le genome exprime
void Geneticien::traduction_genome_en_phenotype(Individu& individu){

  for(unsigned int i = 0 ; i < nbre_genes_ ; i++){
    //Recupere les 2 genes du meme caractere:
    Gene i1 = individu.lire_chromosome_A().lire_gene(i);
    Gene i2 = individu.lire_chromosome_B().lire_gene(i);
    i1.afficheContenu();
  }

}

//Constructeur par defaut, appelé uniquement a la premiere generation :
Individu::Individu(int nbre_genes, const vector<Gene>& population): rng_(), chromosome_A_(nbre_genes, population), chromosome_B_(nbre_genes, population)
{
  //Assigne un sexe:
  sexe_ = Sexe ( rng_.unifRandInt(0,1) ) ;
  //Assigne un prenom et un nom si pas de parent
  nom_ = recevoir_nom_au_hasard(sexe_);
  prenom_ = recevoir_prenom_au_hasard(sexe_);
  //Calcule l'expression de son genome et initialise son phénotype:

  //Individu défini. Pret a transmettre son genome.
  return ;
}

int main(){

  cout<<"Genetique."<<endl;

  const int n = Geneticien::nbre_genes() ;
  const vector<Gene> population = Geneticien::population_genes() ;

  Individu individu( n, population );
  individu.affiche_identite_complete();

  return 0;
}
