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

void Mot::linksynonymes(Mot * linked){
  synonymes_.push_back(linked);
}
void Mot::linkassocies(Mot * linked){
  associes_.push_back(linked);
}

void Mot::affiche()const{

  cout<<"mot : "<<mot_<<endl;

  cout<<"=>synonymes : "<< synonymes_.size()<<endl;
  for(std::vector<Mot*>::const_iterator it = synonymes_.begin(); it != synonymes_.end();it++){
    cout<<(*it)->getmot()<<" "<<(*it)->nature()<<endl;
  }
  cout<<"=>associes : "<<associes_.size()<<endl;
  for(std::vector<Mot*>::const_iterator it = associes_.begin(); it != associes_.end();it++){
    cout<<(*it)->getmot()<<" "<<(*it)->nature()<<endl;
  }
  cout<<"=>themes : ";
  for(std::vector<string>::const_iterator it = themes_.begin(); it != themes_.end();it++){
    cout<<(*it)<<" ";
  }
  cout<<endl;
  cout<<"=>registres : ";
  for(std::vector<string>::const_iterator it = registres_.begin(); it != registres_.end();it++){
    cout<<(*it)<<" ";
  }
  cout<<endl;
}

//Erase possible doublons in synonyms with the double association, or within associes if the user did a mistake by writing twice a word
//Do not erase doublons if found between synonymes and associes
//Extra doublons can be deleted when the pool of words is made later
void Mot::cleanlinks() {

	//On efface les doublons en se servant du container set
	set<Mot*> s;
	unsigned size = synonymes_.size();
	//On ne peut inserer que des elements uniques, ici on se debarasse des doublons
	//Comme il s'agit de pointeur sur les Mot je n'ai meme pas besoin de
	//faire de tests pour les differencier (en nature), l'adresse s'en charge
	for(unsigned i = 0; i != size ; i++){
		s.insert(synonymes_[i]);
	}
	size = s.size();
	//On reset les synonymes
	synonymes_.clear();
	set<Mot*>::iterator it = s.begin();
	while(it != s.end()){
		synonymes_.push_back(*it);
		it++;
	}

	//On fait la meme chose pour les mots associes:
	s.clear();
	size = associes_.size();
	for(unsigned i = 0; i != size ; i++){
		s.insert(associes_[i]);
	}
	size = s.size();
	//On reset les associes
	associes_.clear();
	it = s.begin();
	while(it != s.end()){
		associes_.push_back(*it);
		it++;
	}

	return ;
}

