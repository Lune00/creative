#include"Archiviste.hpp"

using namespace std;


Archiviste::Archiviste()
{
  mylibrary_ = "../library/mylibrary.txt";
  importLibrary();
  buildlinks();
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


vector<string> Archiviste::parseEntry(string stringtoparse, const string delimiter ){

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
  //Synonymes et related
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

  cout<<"Nombre d'adjectifs:"<<getNadjectifs()<<endl;
  cout<<"Nombre de noms communs:"<<getNnomsC()<<endl;
  cout<<"Nombre de verbes:"<<getNverbes()<<endl;
}

//Une fois les entrees chargees, on cree des liens entre
//les mots et leurs synonymes et related. Seuls les
//references ayant aussi une entree sont comptés.
//Pour cela on fait en deux temps. D'abord on a chargé
//Les entrées, maintenant on peut facilement checker
//si le synonymes/related sont aussi en tant qu'entée.
void Archiviste::buildlinks(){

  cout<<"Création des liens entres mots..."<<endl;
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
    //From tokens build links
    link(tokens);
  }
  cout<<"Création des liens entre mots...done"<<endl;

}

void Archiviste::link(vector<string>& tokens){

  //Mot auquel on va rattacher syn et associes
  string mot = tokens[0];
  string nature = tokens[3];
  string delimiter = ";";
  //On recupere les synonymes indiques
  vector<string> syn = parseEntry(tokens[9],delimiter);
  vector<string> associes = parseEntry(tokens[10],delimiter);

  //On parcourt les synonymes du mot mot:
  //On le cherche dans chaque liste:

  //Overload == de Mot (egal si mot et nature egal)
  //En fait on peut pas connaitre la classe grammaticale
  //du mot synonnymes ou associe a partir de la librairie
  //Mais bon c'est un petit side effect pas forcement
  //indesirable. 
  //Pour le moment on prend tous les mots si on les
  //trouve, peu importe leur nature_
  //Utiliser find demanderait de creer un Mot
  //or Mot est une classe abstraite...
  //A voir si ca pose des pbs plus tard...

  for(vector<string>::iterator it = syn.begin();it!=syn.end();it++){
    //Ces boucles devront etre repetees pour mot associes -> a mettre dans une fonction
    for(vector<Mot>::iterator ita = adjectifs_.begin();ita!=adjectifs_.end();ita++){
      if( *it == ita->getmot() ) {
	//On l'associe:

	break ; // il ne peut y avoir 2 mots identiques
	// de meme nature_
      }

    }
    //Meme chose pour verbe et NomC
    for(vector<Mot>::iterator ita = verbes_.begin();ita!=verbes_.end();ita++){
      if( *it == ita->getmot() ) {
	//On l'associe:

	break ; // il ne peut y avoir 2 mots identiques
	// de meme nature_
      }

    }
    for(vector<Mot>::iterator ita = nomsC_.begin();ita!=nomsC_.end();ita++){
      if( *it == ita->getmot() ) {
	//On l'associe:

	break ; // il ne peut y avoir 2 mots identiques
	// de meme nature_
      }

    }

  }
}
