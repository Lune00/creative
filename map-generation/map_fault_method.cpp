#include<iostream>
#include<fstream>
#include<string>
#include<math.h>

using namespace std;


//On va generer des cartes en utilisant la méthode "fault", ou on utilise des courbes qui traversent
//le plan et au dessus on ajoute +a et en dessous on ajoute -a, et on itere en prenant au hasard
//les parametres de la courbe. On va essayer des droites mais aussi des polynomes, des cosinus etc..
//et voir ce que ca donne. L'effet est pas mal déjà avec des droites

//Tenter avec alternance doite/x^2 ou sinus/cosinus,exponentielle

//Franchement c'est pas mal avec l'alternance, et bcp d'iteration!!

//Parametres cools: maxiter 800 , a -2:2, increment uniforme, noisemax 5

double returnrandom(double a, double b){
  return (b-a)*( static_cast<double> (rand()) / static_cast<double> (RAND_MAX))+a;
}   

int main(){

  cout<<"Hello map."<<endl;

  //Parametre initialisation:
  int seed = 1;
  int maxiter = 1800;
  double noisemax = 3. ;
  double ds0 = 1.;
  const int taille = 300;

  double a,b,theta;
  double theta_rad;
  double carte[taille][taille] = {0.};

  //Initialisation generateur:
  srand(time(NULL));

  //Initialisation des sorties:
  ofstream filemap("carte.txt");

  //Generation courbe:
  for(unsigned int iteration = 0 ; iteration != maxiter; iteration++){

    //Rotation de la courbe en degres:
    theta=returnrandom(0.,360.);
    theta_rad = theta * M_PI/180.;

    //a = returnrandom(-0.05,0.05);
    a = returnrandom(-2.,2.);

    //Position de la courbe (origine):

    //double xc = 0.;
    //double yc = 0.;

    //Au centre:
    //double xc = (double) taille * 0.5 ;
    //double yc = (double) taille * 0.5 ;

    //Au hasard:
    double xc = returnrandom(0.,(double)taille);
    double yc = returnrandom(0.,(double)taille);

    //Tourne l'origine de la courbe dans le nouveau referentiel:
    xc = xc * cos(theta_rad) + yc * sin(theta_rad);
    yc = yc * cos(theta_rad) - xc * sin(theta_rad);

    //Increment:

    double signe;
    //Definit l'interieur de l'exterieur
    if(a<0) signe=-1;
    else signe=1.;

    //Uniforme:
    //double ds = ds0 * signe;
    //Expontiel decroissant avec nb iteration:
    double relax = 0.3 * (double)iteration / (double) maxiter; 
    double ds = ds0 * signe * exp(-relax);

    if(iteration % 20 == 0) cout<<"Iteration: "<<iteration<<" - Increment:"<<fabs(ds)<<endl;

    for(unsigned int i=0; i != taille; i++){
      for(unsigned int j=0; j != taille; j++){

	//Calcul position point / courbe:
	double xi = (double) i;
	double yi = (double) j;

	//On tourne la courbe d'un angle theta:
	xi = xi * cos(theta_rad) + yi * sin(theta_rad);
	yi = yi * cos(theta_rad) - xi * sin(theta_rad);

	//Placer le centre de la courbe 

	//double y = a * (xi-xc) * (xi-xc) + yc ;

	//COURBE:
	//On rajoute un petit bruit sur la courbe

	// x * x 
	double y;

	//double y = a * (xi-xc) * (xi-xc) + yc +returnrandom(0.,5.);

	// x
	//double y = a *(xi-xc) + yc +returnrandom(0.,5.);

	// Paire : x * x Impaire : x
	if( iteration % 2 == 0 ) y = a * (xi-xc) * (xi-xc) + yc +returnrandom(0.,noisemax);
	else y = a *(xi-xc) + yc +returnrandom(0.,noisemax);

	//Action:
	if(yi < y){
	  carte[i][j]+=ds;
	}
	else
	{
	  carte[i][j]-=ds;
	}

      }
    }
  }

  for(unsigned int i=0; i != taille; i++){
    for(unsigned int j=0; j != taille; j++){
      //Sortie:
      filemap<<i<<" "<<j<<" "<<carte[i][j]<<endl;
    }
  }

  filemap.close();

  return 0;

}
