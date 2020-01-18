#include<fstream>
#include<iostream>
#include<math.h>


//Le but de ce programme est d'essayer de generer des heightmaps
//avec des random walks successifs
//Chaque 'walker' parcourt la grille depuis une origine et quand il passe sur une case qu'il n'a pas visité il ajoute 1.
//On fait partir plusieurs walkrs, et on somme a la fin chaque contribution

//Pour le moment ils portent tous du centre carte
//La taille du pas est fixee a 1.


//La distance parcourue attendue par le walker est sqrt(Npas)
//Il faut que le nombre de pas Npas < N(taille grille)/2 pour pas qu'il explore tout. A etudier l'interet de l'influence de ce parametre

//Le nomre de walker donne l'altitude max

//D'autres regles pourront être imaginées par la suite (quand il repasse sur une case deja visité on fait quoi? Longueur pas variable, ajout d'une quantité de height variable, etc...)

//Parametres: origine walker, taille pas, nombre de pas, ajout de dh, nombre walker (iteration)

//En choisissant un increment dh aleatoire uniforme(gaussienne) a faire c'est pas mal

//Il faut ensuite peut etre convolue (adoucir avec un noyau gaussien)

//Appliquer d'autres methodes: fault, erosion par l'eau pour riviere


//Rescaler (multiplier par un facteur n la map originale pour avoir de l'espace) pui Terracer pour rendre jouable en transformant l'altitude finale en entier.


// L'erosion pour les rivieres peut etre réalisée en faisant se balader un walker  marche aleatoire biaisée (direction favorisée) on peut regarder les pentes autour de soi, et avoir une probabilité de suivre une des quatres pentes proportionelle a l'intensite de la pente. Sur son passage le walker retire de la matiere et va la deposer plus loin (a determiner). Par ex, plus la pente est elevee plus on peut arracher de la matiere:dc qtité arrachee prop a pente. Plus on arrache matiere, plus le liquide se sature et perd de la vitesse. Il arrache prop pente et depose prop a l'inverse de la pente


using namespace std;

double returnrandom(double a, double b){
  return (b-a)*( static_cast<double> (rand()) / static_cast<double> (RAND_MAX))+a;
}   


//1/2 d'aller vers + ou d'aller vers -
int returnrandomwalk(){
  double p = returnrandom(0.,1.);
  if( p < 0.5 ) return -1;
  else return 1;
}

//1/3 d'aller vers + ou d'aller vers -, 1/3 de rester sur place
int returnrandomwalk2(){
  double p = returnrandom(0.,1.);
  if( p < 0.33 ) return -1;
  if( p > 0.33 && p < 0.66 ) return 1;
  else return 0;
}

//Renvoie vrai si x,y appartient a la grille de taille N
bool dansgrille(int x, int y, int N){
  if ( x < N && y < N ) return true;
  else return false;
}


//Parametres interessants:
// N=100 , Npas=1000, Nw=10, regles de base

int main(){

  cout<<"Hello Random Walk Layering (RWL)"<<endl;
  const int N = 100 ;
  const int Npas = 1000;
  double carte[N][N] = {0};
  //Nombre walkers:
  const int Nw = 20;

  srand(time(NULL));
  //srand(1);

  //Plusieurs walkers:

  for(unsigned int k= 0; k != Nw; k++){ 
    //Origine du walker
    int x = N/2;
    int y = N/2;

    for(unsigned int i=0;i!=Npas;i++){

      //Random walk selon x et y, origine walker (deterministe/aleatoire/centree sur une zone)
      int dx = returnrandomwalk2();
      int dy = returnrandomwalk2();
      //Increment a ajouter:
      //Increment diminue avec le nombre de pas (simule un depot)
      double relaxation = 1.;//  (1. - (double)i/(double)Npas);
      double dh = returnrandom(0.,1.) * relaxation;

      int newX = x + dx;
      int newY = y + dy;

      //On se déplace sur la grille a partir origine
      //Si v[x0+dx][x0+dy] case deja visite, on ajoute rien
      //Sinon on ajoute dh;
      //Test si on est toujours sur la grille
      if( dansgrille(newX,newY,N) ) {

	//Update carte:
	if( carte[newX][newY] <= k) carte[newX][newY]+=dh;

	//Update position walker:
	x = newX;
	y = newY;

      }
      else{
	//On arrete le walker s'il atteint le bord
	break;

      }
    }
  }

  //Ecriture de la carte:
  ofstream filemap("walker_carte.txt");
  for(unsigned int i=0; i != N; i++){
    for(unsigned int j=0; j != N; j++){
      //Sortie:
      filemap<<i<<" "<<j<<" "<<carte[i][j]<<endl;
    }
  }

  filemap.close();

  return 0;

}
