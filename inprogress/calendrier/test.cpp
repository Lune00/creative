#include<iostream>
#include<map>
#include<string>


//Un simple calendrier où chaque mois a le meme nombre de jours.
//On avance dans le calendrier en incrementant le nombre de jours, de mois et d'années.
//Les mois et années sont des paramètres optionnels

using namespace std;


namespace cal{

  int an = 0 ;
  int jour = 29;
  int mois = 1;
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

  //avance et recule de njour, nmois, nans
  void changeDate2(const int njour,const int nmois = 0, const int nans = 0){



  }

}


int main(){

  cal::changeDate(1);
  cal::changeDate(1);
  cal::changeDate(1,1,1);


  return 0 ; 

}
