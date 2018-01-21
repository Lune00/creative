#include"Collectionneur.hpp"
#include"Archiviste.hpp"

using namespace std;


//Return true if a collecion named by name exists in collections_
bool Collectionneur::isCollection(const string& name) const{

  std::vector<Collection>::const_iterator it = collections_.begin();
  while(it!=collections_.end()){
    if(name == it->name()){
      return true ;
      break;
    }
    it++;
  }
  return false;

}

//Create a new collection with name name
void Collectionneur::addCollection(const string& name){

  if(!isCollection(name)){
    Collection c(name);
    collections_.push_back(c);
    return ;
  }
  else{
    return ;
  }

}


void Collectionneur::addToCollection(Mot& mot, const string name){

  vector<Collection>::iterator it = collections_.begin();
  while(it!=collections_.end()){
    if( name == it->name()){
      //Add mot a la Collection it
      //Add a pointer to this word
      Mot * pm = &mot;
      it->addWord(pm);
      break;
    }
    it++;
  }

}

//Add word to the collection named name
void Collectionneur::addToCollection(Mot& m){

  //Run through all themes the word m is linked to
  vector<string> themes = m.getThemes() ;
  //Rajouter un theme "pas de theme" -> "notheme"
  vector<string>::iterator it = themes.begin();

  //TODO: EXception Pas de theme si le premiet theme est vide
  if((*it).size() == 0 ) {
    //cerr<<"Le mot "<<m.getmot()<<" a un theme vide."<<endl;
    //On l'ajoute a une collection "notheme", on pourra corriger la librairie
    addCollection("notheme");
    addToCollection(m,"notheme");
    return;
  }

  while( it != themes.end() ){
    //La collection n'existe pas encore
    if(!isCollection(*it)){
      addCollection(*it);
      addToCollection(m,*it);
    }
    //La collection existe deja
    else{
      addToCollection(m,*it);
    }
    it++;
  }

}

void Collectionneur::print() const {

  cout<<"Nombre de collections: "<<collections_.size()<<endl;
  vector<Collection>::const_iterator it = collections_.begin();
  while(it != collections_.end()){
    cout<<it->name()<<" : "<<it->size()<<endl;
    it++;
  }

}

Collection Collectionneur::askCollection(const string name) const{

  std::vector<Collection>::const_iterator it = collections_.begin();
  while(it!=collections_.end()){
    if(name == it->name()){
      return *it ;
      break;
    }
    it++;
  }
  return Collection();

}
