#include<sstream>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>


bool randb(){
  return (rand()%2>0);
}
int rand(int a , int b){
  return (a+(rand()%(b-a+1)));
}
double rand(double min,double max){
  return ((max-min)*((double)rand()/(double)RAND_MAX)+min);
}
double gaussrand(double moyenne,double variance){
  double u1=rand(0.,1.);
  double u2=rand(0.,1.);
  return (moyenne+variance*sqrt(-2.*log(u1))*cos(2*M_PI*u2));
}

// mReproduction_ : mois de reproduction ex: "1" le premier mois
//					 ex: "1 5 8" le premier,5e et 8e mois

// mdMigration_ : mois et durée de migration ex: "1 3" Absent le premier mois pendant trois mois,controle visibilité

using namespace std;

enum gabarit{petit,moyen,grand,gigantesque};
enum alimentation{herbivore,planctonophage,carnivore};
enum profondeur{faible,moyenne,forte,abysse};
enum social{solitaire,banc,grandBanc};
enum tauxReproduction{mauvais,normal,bon};
enum nageoireCaudale{croissant,pointue,arrondie,tronquee,echancree};
enum nageoireDorsale{une,deux,trois};
enum nbcouleurs{uneC,deuxC,troisC,quatreC,cinqC};
enum venin{absent,anesthesique,paralysant,mortel,hallucinatoire};

//La masse est en kg.
class Masse{

  private:
    double m_ ;
  public:
    Masse() { m_ = 0. ; } ;
    Masse(double m) : m_(m) {}; 
    ~Masse() {};
    double getMasse() ;
    std::string printMasse() ;
};

std::string Masse::printMasse() 
{
  std::stringstream buffer;
  if ( m_ < 1. )  buffer << setprecision(4) << m_ * 1000 << " g"; 
  if ( m_ >= 1. ) buffer << setprecision(1) << m_ << " kg"; 
  return buffer.str();
}

class Poisson{

  private:
    gabarit gabarit_;
    alimentation alimentation_;
    profondeur profondeur_;
    social social_;
    tauxReproduction tauxReproduction_;
    nageoireCaudale nageoireCaudale_;
    nageoireDorsale nageoireDorsale_;
    nbcouleurs nbcouleurs_;
    venin venin_;
    string mReproduction_;
    string mdMigration_;

    int id_; //espece
    Masse masse_;
    int puissance_;
    double taux_; // nouveau = ancien * ( 1 + % )
    string nom_;

  public:
    Poisson();
    Poisson(double);
    ~Poisson();
    void print();

};

Poisson::Poisson(double m) : masse_(m) {}
void Poisson::print() { cout<<masse_.printMasse()<<endl; } ;
Poisson::~Poisson(){};
Poisson::Poisson()
{

  gabarit_ = gabarit( rand() % 4 ) ;

  switch ( gabarit_ ){
    case petit : cout<<"petit"<<endl; break;
  }


  };


  int main() {
    cout<<"Poisson génération."<<endl;
    Poisson a(2.) , b(0.1);
    a.print();
    b.print();
    return 0;
  }
