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
//On peut eventuellement ajouter dans cette classe la converstion en unité pour le gameplay. Il faut définir un étalon unité, genre 1 unité = 100 g
//On peut egalement envisager que l'unité s'adapte au cas : viande, poisson, epices, graines,... Je pense que cette classe peut etre très utile pour gérer ces aspects.
//Pourqoi avoir besoin d'unite? Quand on ramasse qqchose, il donne la quantité, et on la stocke directement. Une entite(viande,epices) est disponible en poids,volume. Comme ca on peut faire des conversions, et utile pour chimie,physique.

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
  if ( m_ < 0.001 )  buffer << setprecision(3) << m_ * 1000000 << " mg"; 
  if ( m_ > 0.001 && m_ < 1. )  buffer << setprecision(4) << m_ * 1000 << " g"; 
  if ( m_ >= 1. ) buffer << setprecision(1) << m_ << " kg"; 
  return buffer.str();
}

class Volume{
  private:
    double v_ ;
  public:
    Volume() { v_ = 0. ; } ;
    Volume(double v) : v_(v) {}; 
    ~Volume() {};
    double getVolume() ;
    std::string printVolume() ;
};
std::string Volume::printVolume() 
{
  std::stringstream buffer;
  if ( v_ < 0.001 )  buffer << setprecision(3) << v_ * 1000000 << " mL"; 
  if ( v_ > 0.001 && v_ < 1. )  buffer << setprecision(4) << v_ * 1000 << " L"; 
  if ( v_ >= 1. ) buffer << setprecision(1) << v_ << " kL"; 
  return buffer.str();
}


int Masse::getUnits() 
{

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
    Poisson a(0.0001) , b(0.1);
    a.print();
    b.print();
    return 0;
  }
