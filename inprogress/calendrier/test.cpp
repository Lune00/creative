#include<iostream>
#include<map>
#include<string>


//Un simple calendrier où chaque mois a le meme nombre de jours.
//On avance dans le calendrier en incrementant le nombre de jours, de mois et d'années.
//Les mois et années sont des paramètres optionnels

using namespace std;

namespace cal{

  int an = 0 ;
  int jour = 30;
  int mois = 12;
  //Nombre de jours par mois:
  int mois_size = 30 ;
  //Nombre de mois par an:
  int an_size = 12 ;
  //Stocke le nom des mois:
  //La taille de la map doit correspondre a an_size (nombre de mois dans l'année)
  std::map<int,std::string> init_noms_mois(){
    map<int,std::string> m;
    //Hiver:
    m[1] = "Brume";
    m[2] = "Dargent";
    m[3] = "Anor";
    //Printemps:
    m[4] = "Brise";
    m[5] = "Florin";
    m[6] = "Or";
    //Ete:
    m[7] = "Mauve";
    m[8] = "Lune";
    m[9] = "Cuivre";
    //Ete:
    m[10] = "Ether";
    m[11] = "Serpe";
    m[12] = "Aurore";
    return m;
  }
  const map<int,std::string> table_noms_mois = init_noms_mois();

  void afficheDate() {
    string nom_mois;
    std::map<int,std::string>::const_iterator it = table_noms_mois.find(mois);
    if( it != table_noms_mois.end()) nom_mois = it->second;

    cout<<"Jour: "<<jour<<" Mois: " <<nom_mois<<"("<<mois<<")"<<" An:"<<an<<endl;
    return;
  }

  //Calcule la date apres un increment de njour,nmois et nans (nmois et nans optionnels)
  void changeDate(const int njour,const int nmois = 0, const int nans = 0){

    //Petit malin, as tu déja entendu parler de la fleche du temps?
    if(njour<0 || nmois<0 || nans <0) return ;

    int inc_jours = njour + nmois * mois_size;
    for(unsigned int i = 0 ; i < inc_jours; i++){
      jour++;
      if(jour>mois_size){
	mois++;
	jour=1;
      }
      if(mois>an_size){
	an++;
	mois=1;
      }
    }
    an += nans;
    afficheDate();
    return;
  }

  //Methode sans boucle:
  void changeDate2(const int njour,const int nmois = 0, const int nans = 0){

    //Petit malin, as tu déja entendu parler de la fleche du temps?
    if( njour<0 || nmois<0 || nans<0 ) return ;

    //inc_jours: nombre de jours a avancer
    //inc_mois: nombre de mois a avancer
    int inc_jours = njour + nmois * mois_size;
    int inc_mois = (int) inc_jours / mois_size ;
    inc_jours = inc_jours % mois_size;

    //Apport des jours a l'increment en mois:
    inc_mois += (int)(jour + inc_jours)/ mois_size ;

    an += (int) (mois + inc_mois - 1)/ an_size + nans ;
    jour = (jour + inc_jours - 1 ) % mois_size + 1 ;
    mois = (mois + inc_mois - 1) % an_size + 1 ;

    afficheDate();
    return;

  }

  void setDate(const int j, const int m, const int a){

    jour = j;
    mois = m;
    an = a;

    if( jour < 1 || jour > mois_size) jour = 1;
    if( mois < 1 || mois > an_size)   mois = 1;
    if( an < 0 ) an = 1;


    return;

  }

}


int main(){

  //Tests : comparaisons entre les 2 méthodes:
  cal::afficheDate();


  cout<<endl;

  //Test 1:
  cal::setDate(30,12,0);
  cal::changeDate2(31);
  cal::setDate(30,12,0);
  cal::changeDate(31);

  cout<<endl;

  //Test 2:
  cal::setDate(3,1,10);
  cal::changeDate2(913);
  cal::setDate(3,1,10);
  cal::changeDate(913);

  return 0 ; 

}
