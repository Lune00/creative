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

  cout<<"Les portes de la bilbiotheque sont ouvertes"<<endl;

  std::vector<Mot*> lib;
  lib.push_back(new NomC("chocolat","Sokola",3,'m','s'));
  lib.push_back(new Verbe("maner","manger",3));
  for(vector<Mot*>::iterator it = lib.begin() ; it != lib.end(); it++){
    if(NomC* p = dynamic_cast<NomC*>(*it)) p->accorder("le");
  }   

  return 0;
}
