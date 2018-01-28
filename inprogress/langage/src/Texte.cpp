#include"Texte.hpp"

using namespace std;

Texte::Texte(){
  ftemplates_ = "../ressources/templates.txt";
  //TMP
  loadTemplates();
}

Texte::~Texte(){}

//TMP: pour le moment lit tout
//A definir, randomiser par type de templates etc..
void Texte::loadTemplates(){

  cerr<<"LoadTemplate"<<endl;

  ifstream is(ftemplates_);

  if(!is){
    cerr<<"Texte::readTemplate : cannot open file."<<endl;
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
      readTemplate(is);
      //TMP
      break;
    }

    is >> token;

  }
  return ;
}

void Texte::readTemplate(ifstream& is){

  string token;

  //vector<string> Template;
  while(is){
    is >> token;
    if(token.back()=='}') break;
    //Template.push_back(token);
    template_.push_back(token);
  }


  //TMP:
  for(vector<string>::iterator it = template_.begin(); it!= template_.end();it++){

    cout<<*it<<endl;

  }

  return ;

}
