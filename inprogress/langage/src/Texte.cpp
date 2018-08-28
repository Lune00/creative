#include"Texte.hpp"

using namespace std;

std::string Texte::ftemplates_ = "../ressources/templates.txt";


Texte::Texte(){
  //TMP
  read_templates_datafile();
}

Texte::~Texte(){}

//TMP: pour le moment lit tout
//A definir, randomiser par type de templates etc..
void Texte::read_templates_datafile(){

  cerr<<"load template : no preferences"<<endl;

  ifstream is(ftemplates_);

  if(!is){
    cerr<<"Texte::load_templates : cannot open file."<<endl;
    return ;
  }

  string token;
  is >> token;

  while(is){

    //Comment : ignore
    if(token.at(0)=='#') {
      is >> token;
      continue;
    }

    if(token.at(0)=='{'){
      //TMP
      load_template(is);
      break;
    }

    is >> token;
  }

  return ;
}

void Texte::load_template(ifstream& is){
  string token;
  while(is){
    is >> token;
    if(token.back()=='}') break;
    template_.push_back(token);
  }
  return ;
}

void Texte::print_template() const{
  cout<<"Template choisi: ";
  for(vector<string>::const_iterator it = template_.begin(); it!= template_.end();it++){
    cout<<*it<<" ";
  }
  cout<<endl;
}

//Hache le template en mots donnes et mots a remplir de manière formatee, en ecartant tous les biais/erreurs du template

void Texte::fill_template(){

  //On separe bien les entrees
  for(vector<string>::iterator it = template_.begin(); it!= template_.end();it++){

  }

  return ;

}


vector<Mot*> Texte::askwords() const {

	vector<Mot*> vm;

	return vm;

}


