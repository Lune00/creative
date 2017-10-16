#include<iostream>


using namespace std;


int main(){

  cout<<"*Reaction diffusion 1D."<<endl;

  //Parametres discretisation temps et espace:
  const double T = 100 ;
  const int steps = 100 ;
  const double dt = T /(double)steps;
  //Spatial:
  unsigned int const N = 128;
  const double L = 1.;
  const double dx = L/(double)N;
  //Parametres:
  const double Du = 1.;
  const double DV = 1.;
  //Champs a l'instant t:
  double u[N];
  double v[N];
  //Champs a l'instant t+1:(calcul) (pas in-place)
  double u_new[N];
  double v_new[N];
  //CL and CI:

  double time = 0.;
  //Temporal loop:
  for(unsigned int i = 0 ; i != steps ; i++){
    //Spatial loop:
    time+=dt;
    for(unsigned int j = 0 ; j!= N ; j++){
      //Faire attention aux bords: cas j = 0 et j = N-1
      u_new[j] = u[j] + ( Du * ( u[i+1] - 2 * u[i] + u[i-1] ) / ( dx * dx ) + u[i]*(1-u[i]) ) * dt ;
    }
    //Updates champs u = u_new 
  }

  return 0;

}
