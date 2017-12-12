#include"Mot.hpp"

using namespace std;

Mot::Mot(std::string mot,std::string phon, int nsyll): mot_(mot), phon_(phon), nsyll_(nsyll)
{

}


Mot::~Mot(){

}

bool operator==(const Mot& a, const Mot& b){
  return ( a.mot_ == b.mot_);
}

