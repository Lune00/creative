#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

void afficher(double * tab, int size){
  for(unsigned int i=0; i!=size; i++){
    cout<<tab[i]<<" ";
  }
  cout<<endl;
}

void ecrire(double * tab, int size,int pas, ofstream& of){
  for(unsigned int i=0; i!=size; i++){
    of<<pas<<" "<<i<<" "<<tab[i]<<endl;
  }
}

void ecrirePoint(double * tab, int point,int pas, ofstream& of){
    if( pas % 2 == 0 )of<<pas<<" "<<tab[point]<<" "<<tab[point+1]<<endl;
}

int main(){

  const int N = 21 ;
  double G[N] = {0.};
  double temp[N] ={0.};
  int const nmax = 1000;
  double const G0 = 200.;
  //CI

  G[N/2]=G0;
  temp[N/2]= G0;

  ofstream all("grilleT.txt");
  ofstream one("grillePoint.txt");

  //Boucle sur le temps:
  for(unsigned int n = 0 ; n != nmax ; n++){

    //afficher(G,N);
    ecrire(G,N,n,all);
    ecrirePoint(G,N/2,n,one);

    //Diffusion: je donne la moitie a chaque cote
    for(unsigned int i = 0; i != N ; i++){

      //Quantitié a distribuer:
      double s = G[i];
      temp[i] -= s ;

      if( i == 0 ) {
	temp[N-1] += 0.5 * s;
	temp[i+1] += 0.5 * s;
      }
      else if ( i == N-1 ) {
	temp[i-1] += 0.5 * s;
	temp[0] += 0.5 * s;
      }
      else{
	temp[i-1] += 0.5 * s;
	temp[i+1] += 0.5 * s;
      }

    }
    //Update:
    for(unsigned int i = 0; i != N ; i++){
      G[i] = temp[i];
    }

  }

}
