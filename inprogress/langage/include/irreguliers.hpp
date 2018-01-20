#ifndef IRREGULIERS_H
#define IRREGULIERS_H

//Stocke les verbes irreguliers
using namespace std;

//Liste des verbes irreguliers (troisieme groupe)
struct ListeIrr{
  static list<string> makeliste()
  {
    list<string> l;
    l.push_back("partir");
    l.push_back("courir");
    l.push_back("mourir");
    return l;
  }
  static const list<string> irreguliers;
};

#endif
