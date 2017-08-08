#ifndef H_Loup_H
#define H_Loup_H
#include<string>
#include<iostream>
#include<fstream>

//Tout ceci est un test pour experimenter des procedures de generation de texte.

//On a un acteur (le loup) avec des bus (se nourrir)

//On se sert des actions effectuees pour batir un recit literaire (interpretation textuelle des mecanismes implementees)
//Il y a une phase d'action en fonction de l'était et une phase descriptive dans le programme.
//Pour cela il faut etoffer la personalite de l'acteur: etat physique, emotionnel qui affectera la vision, et la transcription des evenements.
//Il faut une memoire. L'acteur evolue au cours du temps, de sa vie. Son caractere change.

//On peut enregistrer les etats successifs (faim, repos, faim ...) et batir une interpretation a posteriori de l'histoire.
//Cette interpretation combine un recit exterieur et des appartes interieurs. Par ex: Le loup n'avait pas mangé depuis trois jours "Comment j'ai pu rater ce lapin il y a trois jours?" se repetait il.

//On stocke les etats et action sur un axe temporel qu'on vient relire en textualisant. Pour cela il faut enregistrer toutes les infos et a chaque instant et integrer les etats anterieurs.
//Par exemple le skill : s'il s ameliore beaucoup sur une duree on peut le mentionner. ex: Le loup devenait de plus en plus adroit a la chasse. Au dessus d'un nombre Plus rien ne pouvait lui echapper. 
//S'il passe plusieurs jours dans un etat de faim extreme : Il se souviendrait toujours de cette periode où il n'avait rien mange depuis 5 jours.

//En gros il faut stocker les actions et des variables d'etat (et etudier leur variation). Ces variations affectent l'acteur et il s'exprime differemment.


using namespace std;

#define trouverproie 0.5
#define survie 7 
#define faimcritique 50
//Un pas de simulation : un jour

// renvoie un nombre aléatoire uniforme entre 0 et 1
double unifRand()
{
  return rand()/double(RAND_MAX);
}
// renvoie un nombre alétoire uniforme entre a et b
double unifRand(int a,int b)
{
  return unifRand()*(b-a)+a;
}
// renvoie un entier entre a et b
int unifRandInt(int a,int b)
{
  return (a + (rand() % (b - a + 1)));
}


class Loup{
  private:
    //Mort ou vivant
    bool mort_ ; 
    //Son age
    int age_;
    //Entre 0 et 100 . Si elle est egale a 100 pendant survie jours, mort 
    int faim_;
    //Journees passee en faim critique (1
    int joursFaimMax_;
    //Capacite a attraper (et trouver) une proie trouvee (entre 0 et 100)
    int skill_;
    //Stocke l'histoire
    vector<int> souvenir_;

  public:
    Loup(){ mort_ = false ; age_ = 1 ; faim_ = 0 ; distance_ = 0 ; skill_ = 10 ; joursFaimMax_ = 0 ; };
    ~Loup(){};
    void Update(); //Met a jour le loup
    void Chasser();
    void updateFaim();
    void write(int step, string filename);
    bool estMort();
    int getAge() {return age_;}
};

void Loup::write(int i, string filename){
  ofstream oss(filename,ios::app);
  oss<<i<<" "<<this->faim_<<" "<<joursFaimMax_<<endl;
  oss.close();
}

//La mort est de paser 7 jours consecutifs au max de la faim
bool Loup::estMort(){
  if(joursFaimMax_ > survie ) {
    //On construit le souvenir
    return true;
  else return false;
}

void Loup::updateFaim()
{
  souvenir_.push_back(faim_);
  faim_+= unifRandInt(10,15);
  if( faim_ > 100 ) faim_ = 100;
  if( faim_ < 0 ) faim_ = 0;
}


void Loup::Chasser(){

  cerr<<"Le loup part en chasse."<<endl;

  //Chance de trouver une proie
  double p = unifRand() ;

  if( p < trouverproie ) {
    cerr<<"Proie capturee!"<<endl;
    faim_ -= unifRandInt(10,30); // proie de differente taille;
  }
  else
  {
    cerr<<"Le loup n'a rien attrape aujourd'hui"<<endl;
  }


}

//Update l etat du loup au jour i
void Loup::Update(){

  //Le loup vieillit
  age_ += 1 ;

  //Chaque jour la faim augmente:
  updateFaim();

  //On teste la faim, si au dessus de la limite chasse
  if( faim_ > faimcritique ) {
    Chasser();
  }
  else
  {
    //Que fait le loup quand il n'a pas faim?
    cerr<<"Le loup se repose."<<endl;

  }
  //Si faim = 100 on increment le nombre de joursdefaim
  if(faim_ < 100 ) {
    joursFaimMax_ = 0 ;
  }
  else
  {
    joursFaimMax_++;
    cerr<<"Le loup a toujours faim."<<endl;  
  }

}


int main(){

  srand(time(NULL));
  int ts = 2000 ;
  cerr<<"Programme du Loup."<<endl;
  Loup loup;
  string filename = "suivi.txt";
  ofstream out(filename,ios::out);
  out.close();
  for(int i = 0 ; i != ts ; i++){
    cerr<<"--- Jour "<<i<<endl;
    loup.Update();
    if(loup.estMort()) break;
    loup.write(i,filename);
  }
  if(loup.estMort())cerr<<"Le loup est mort au bout de "<<loup.getAge()<<" jours."<<endl;

  return 0;
}


#endif
