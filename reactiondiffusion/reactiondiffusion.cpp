#include<iostream>
#include<fstream>

using namespace std;


int main(){

  cout<<"*Reaction diffusion 1D."<<endl;
  ofstream dat("data.txt");
  dat.close();

  //Parametres discretisation temps et espace:
  const double T = 10. ;
  const double dt = 0.001 ;
  const int steps = (int)(T/dt) ;
  //Spatial:
  unsigned int const N = 10.;
  const double L = 1.;
  const double dx = L/(double)N;
  //Parametres:
  const double Du = 0.001;
  const double DV = 1.;
  //Champs a l'instant t:
  double u[N];
  double v[N];
  //Champs a l'instant t+1:(calcul) (pas in-place)
  double u_new[N];
  double v_new[N];
  //CL and CI:
  double time = 0.;
  cout<<"Initialisation CI/CL:"<<endl;
  for(unsigned int j=0; j!= N ; j++){

    if( j < N/2){
      u[j]=0.;
    }
    else{
      u[j]=2.;
    }
    u_new[j]=0.;
  }
  //Ecriture des CI
  ofstream data("data.txt",ios::app);
  for(unsigned int j = 0 ; j!= N ; j++){
    data<<time<<" "<< time<<" "<< j<<" "<< u[j]<< endl;
  }
  data.close();

  //Temporal loop:
  for(unsigned int i = 0 ; i != steps ; i++){
    //Spatial loop:
    time+=dt;
    cout<<"time step: "<<i<<endl;
    for(unsigned int j = 0 ; j!= N ; j++){
      //Faire attention aux bords: cas j = 0 et j = N-1
      if( j == 0 ) {
	u_new[j] = u[j] + ( Du * ( u[j+1] - 2 * u[j] + u[N-1] ) / ( dx * dx ) + u[j]*(1-u[j]) ) * dt ;
      }
      else if (j ==N-1){
	u_new[j] = u[j] + ( Du * ( u[0] - 2 * u[j] + u[j-1] ) / ( dx * dx ) + u[j]*(1-u[j]) ) * dt ;
      }
      else{
	u_new[j] = u[j] + ( Du * ( u[j+1] - 2 * u[j] + u[j-1] ) / ( dx * dx ) + u[j]*(1-u[j]) ) * dt ;
      }
    }
    //Updates champs u = u_new 
    cout<<"Updating"<<endl;
    for(unsigned int j = 0 ; j!= N ; j++){
      u[j] = u_new[j];
    }
    //Ecriture
    ofstream data("data.txt",ios::app);
    for(unsigned int j = 0 ; j!= N ; j++){
      data<<i<<" "<< time <<" "<<j<<" "<< u[j]<< endl;
    }
    data.close();

  }

  return 0;

}
