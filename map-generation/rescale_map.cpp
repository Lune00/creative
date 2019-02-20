#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;


int main(){

  cout<<"Hello World! Rescale it!"<<endl;

  //On lit une carte de taille N x N et on la rescale par nN x nN
  //n est le parametre de rescale: si N est impaire n doit etre impaires, si N est paire n est paire
  //On rescale aussi la valeur de la heightmap entre a et b

  //Parametre N donne par generateur de carte
  int const N = 100;
  int const n = 2;


  if( N % 2 == 0){
    if ( n % 2 != 0 ){
      cout<<"Le facteur de rescaling doit etre paire (N="<<N<<")."<<endl;
      return 0;
    }
  }
  else{
    if ( n % 2 == 0){
      cout<<"Le facteur de rescaling doit etre impaire (N="<<N<<")."<<endl;
      return 0;
    }
  }

  //Intervalle [a:b] Rescale l'altitude
  double const a = 0. ;
  double const b = 100.;

  //Carte et carte rescale
  double carte[N][N]={0.};
  double Rcarte[N*n][N*n];

  //Valeurs min et max de la carte originelle
  double hmin,hmax;

  hmin = carte[0][0];
  hmax = carte[0][0];

  ifstream inputcarte("walker_carte.txt");

  //Lecture carte et calcul de hmin et hmax
  int tr = 0 ;
  for(unsigned int i = 0 ; i != N; i++){
    for(unsigned int j = 0 ; j != N; j++){
      inputcarte >> tr >> tr >> carte[i][j];
      hmin =  hmin  > carte[i][j] ? carte[i][j] : hmin ;
      hmax =  hmax  < carte[i][j] ? carte[i][j] : hmax ;
    }
  }

  cout<<"min = "<<hmin<<endl;
  cout<<"max = "<<hmax<<endl;

  //Rescale:
  for(unsigned int i = 0 ; i != N; i++){
    for(unsigned int j = 0 ; j != N; j++){

      for(unsigned int k = n * i ; k != n * i + n ; k++){
	for(unsigned int l = n * j ; l != n * j + n; l++){
	  Rcarte[k][l] = carte[i][j];
	}
      }

    }
  }

  //On rescale la hauteur (valeur de la heightmap) entre a et b
  for(unsigned int i = 0 ; i != N * n; i++){
    for(unsigned int j = 0 ; j != N * n; j++){
      Rcarte[i][j] = (b-a) * (Rcarte[i][j] - hmin) / (hmax - hmin) + a ; 
    }
  }

  //Ecriture:
  ofstream rescale("rescaled_map.txt");
  for(unsigned int i = 0 ; i != N * n; i++){
    for(unsigned int j = 0 ; j != N * n; j++){
      rescale<<i<<" "<<j<<" "<<Rcarte[i][j]<<endl;
    }
  }

  rescale.close();

  return 0 ;
}
