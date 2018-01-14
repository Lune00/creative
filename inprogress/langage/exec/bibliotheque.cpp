#include<list>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
#include<map>

#include"Archiviste.hpp"

using namespace std;

int main()
{

  Archiviste archiviste;
  archiviste.afficher();

  cout<<"Les portes de la bilbiotheque sont ouvertes."<<endl;

  //Tests downcast (a partir pointeur Mot(classe mere), je peux acceder a la partie classe fille):
  std::vector<Mot*> lib;
  lib.push_back(new NomC("chocolat","Sokola",3,'m','s'));
  lib.push_back(new Verbe("manger","manger",3));
  for(vector<Mot*>::iterator it = lib.begin() ; it != lib.end(); it++){
    if(NomC* p = dynamic_cast<NomC*>(*it)) p->accorder("le");
  }   

  //Test finds:
  Mot * m = archiviste.findword("baleine","NOM");
  m->affiche();

  m = archiviste.findword("géant","ADJ");
  m->affiche();

  return 0;
}
