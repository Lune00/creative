#include"Archiviste.hpp"

using namespace std;


Archiviste::Archiviste()
{
  mylibrary_ = "../library/mylibrary.txt";
  importLibrary();
}

Archiviste::~Archiviste()
{


}

void Archiviste::importLibrary()
{
  cout<<"Importation de la librairie..."<<endl;
  ifstream mylib(mylibrary_);
  while(true){
    string entree;
    vector<string> tokens;
    getline(mylib,entree);
    if (mylib.eof() ) break;
    tokens = parseEntry(entree,"\t");
    //Check tokens: ils doivent avoir 12 champs definis par mylibrary.txt
    if( tokens.size() < 12) {
      cerr<<"L'entree \""<<tokens[0]<<"\" ne contient pas 12 champs requis."<<endl;
      continue;
    }
    if (tokens.size() == 0 ) continue;
    //From tokens build lists
    addEntry(tokens);
  }
  cout<<"Importation de la librairie...done"<<endl;
}


vector<string> Archiviste::parseEntry(string stringtoparse, string delimiter ){

  vector<std::string> tokens;
  size_t pos = 0 ;
  string token;
  while( (pos = stringtoparse.find(delimiter)) != std::string::npos)
  {
    token = stringtoparse.substr(0, pos);
    stringtoparse.erase(0, pos + delimiter.length());
    tokens.push_back(token);
  }
  //On rajoute la derniere entree (ce qu'il reste)
  tokens.push_back(stringtoparse);

  //On retire les caracteres vides (dus au formatage en bash)
  //On place tous les caracteres vides a la fin de string et on se place au premier caractere vide
  //puis on supprime jusqu'a la fin (algorithm)
  for(vector<std::string>::iterator it = tokens.begin() ; it != tokens.end() ; it++ ){
    it->erase(std::remove_if(it->begin(), it->end(), ::isspace), it->end());
  }

  return tokens;

}



void Archiviste::addEntry(const vector<string>& entree){

  //for(int i = 0; i < entree.size();i++){
  //  cout<<entree[i]<<endl;
  //}
  //L'ordre des champs est defini par la librairie (libconfig.sh)
  //TODO
  //Rajouter les champs suivants ensuite
  string mot = entree[0];
  string phon = entree[2];
  string genre = entree[5];
  string nombre = entree[6];
  int nsyll = stoi(entree[7]);

  //NomC, Adjectif, Verbe ... ?
  string nature = entree[3];

  if( nature == "NOM") {
    NomC a(mot,phon,nsyll,genre[0],nombre[0]);
    nomsC_.push_back(a);
  }
  else if ( nature == "ADJ"){
    Adjectif a(mot,phon,nsyll,genre[0],nombre[0]);
    adjectifs_.push_back(a);
  }
  else if (nature == "VER"){
    Verbe a(mot,phon,nsyll);
    verbes_.push_back(a);
  }
  else{
    cerr<<"L'Archiviste ne connait pas la catégorie "<<nature<<" du mot "<<mot<<". Entree écartée."<<endl;
    return ;
  }

}

void Archiviste::afficher() const{

  cout<<"Liste des ajectifs:"<<endl;
  cout<<"Nombre:"<<adjectifs_.size()<<endl;
  for(vector<Adjectif>::const_iterator it = adjectifs_.begin(); it!= adjectifs_.end();it++){
    cout<<it->getmot()<<" ";
  }
  cout<<endl;
}
