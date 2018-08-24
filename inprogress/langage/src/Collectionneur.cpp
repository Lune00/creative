#include"Collectionneur.hpp"
#include"Archiviste.hpp"

using namespace std;


//Return true if a collecion named by name exists in collections_
bool Collectionneur::exist_collection_by_name(const string& name) const{

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
void Collectionneur::create_collection(const string& name){

  if(!exist_collection_by_name(name)){
    Collection c(name);
    collections_.push_back(c);
    return ;
  }
  else{
    return ;
  }

}


//Add word to the collection named name
void Collectionneur::add_word_to_collection(Mot& mot, const string name){

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

void Collectionneur::put_word_into_collections_by_theme(Mot& m){

  //Run through all themes the word m is linked to
  vector<string> themes = m.getThemes() ;
  //Rajouter un theme "pas de theme" -> "notheme"
  vector<string>::iterator it = themes.begin();

  //TODO: EXception Pas de theme si le premiet theme est vide
  if((*it).size() == 0 ) {
    //cerr<<"Le mot "<<m.getmot()<<" a un theme vide."<<endl;
    //On l'ajoute a une collection "notheme", on pourra corriger la librairie
    create_collection("notheme");
    add_word_to_collection(m,"notheme");
    return;
  }

  while( it != themes.end() ){
    //La collection n'existe pas encore
    if(!exist_collection_by_name(*it)){

      create_collection(*it);

      add_word_to_collection(m,*it);
    }
    //La collection existe deja
    else{
      add_word_to_collection(m,*it);
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

Collection Collectionneur::return_collection_by_name(const string name) const{

  std::vector<Collection>::const_iterator it = collections_.begin();
  while(it!=collections_.end()){
    if(name == it->name()){
      return *it ;
    }
    it++;
  }
  return Collection();

}
