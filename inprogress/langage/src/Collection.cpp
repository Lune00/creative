#include "Collection.hpp"

using namespace std;

void Collection::addWord(Mot * pm){
  mots_.push_back(pm);
}

void Collection::print()const{
  for(vector<Mot*>::const_iterator it = mots_.begin(); it != mots_.end(); it++){
    //(*it)->affiche(); too exhaustive for test
    cout<<(*it)->getmot()<<" ";
  }
  cout<<endl;
}
