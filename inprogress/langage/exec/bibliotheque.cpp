#include<list>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
#include<map>

#include"Mot.hpp"
#include"NomC.hpp"
#include"Verbe.hpp"

using namespace std;

int main()
{
  cout<<"Les portes de la bilbiotheque sont ouvertes"<<endl;

  std::vector<Mot*> lib;
  lib.push_back(new NomC("chocolat","Sokola",3,'m','s'));
  lib.push_back(new Verbe("maner","manger",3));
  for(vector<Mot*>::iterator it = lib.begin() ; it != lib.end(); it++){
    if(NomC* p = dynamic_cast<NomC*>(*it)) p->accorder("le");
  }   

  return 0;
}
