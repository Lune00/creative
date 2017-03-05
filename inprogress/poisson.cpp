#include<iomanip>
#include<cmath>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>


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
    double masse_;
    int puissance_;
    double taux_; // nouveau = ancien * ( 1 + % )
    string nom_;

  public:

};


int main() {
cout<<"Poisson génération."<<endl;
return 0;
}
