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
  }
  return false;

}

//Create a new collection with name name
void Collectionneur::addCollection(const string& name){

  if(!isCollection(name)){
    Collection c(name);
    collections_.push_back(c);
  }

}

//Add word to the collection named name
void Collectionneur::addToCollection(Mot& m, const string& name){


}
