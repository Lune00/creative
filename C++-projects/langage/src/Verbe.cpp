#include"Verbe.hpp"

const map<string,string> ConjPremier::present_ = ConjPremier::makePresent();
const map<string,string> ConjPremier::futur_ = ConjPremier::makeFutur();

const map<string,string> ConjDeuxieme::present_ = ConjDeuxieme::makePresent();
const map<string,string> ConjDeuxieme::futur_ = ConjDeuxieme::makeFutur();

const map<string,string> ConjTroisieme::present_credretre = ConjTroisieme::makePresent_credretre();

const map<string,string> ConjTroisieme::present_defaut = ConjTroisieme::makePresent_defaut();

const list<string> ListeIrr::irreguliers = ListeIrr::makeliste();

Verbe::Verbe(string lemme, string phon, int nsyll): Mot(lemme, phon, nsyll)
{
  nature_ = VER_ ;
}

Verbe::~Verbe(){

}

//Recupere la terminaison (deux dernieres lettres) de l'infinitif 
string Verbe::getTerminaison(){

  if( ! getInfinitif().empty() )
  {
    std::string::size_type size = this->getInfinitif().size();
    std::size_t pos = size - 2 ;
    return this->getInfinitif().substr(pos);

  }
  else
  {
    return string();
  }

}

//Fonction qui determine le groupe a partir de la forme infinitive (les deux dernieres lettres-
int Verbe::groupe(){
  //D'abord tester si irregulier (base), sinon tester terminaison
  string mot = this->getInfinitif();
  bool found = ( std::find(ListeIrr::irreguliers.begin(), ListeIrr::irreguliers.end(), mot) != ListeIrr::irreguliers.end());

  if(found){
    return troisieme;
  }
  else{
    string terminaison = this->getTerminaison();
    if(terminaison == "er" ) return premier;
    else if(terminaison == "ir" ) return deuxieme;
    else return 2;
  }
}

//Fonction qui en fonction du group (1er, 2e ou 3e) renvoies la conjugaison (pour le moment: passe, present, futur)
//string Verbe::conjuguer(string pronom, int temps){
//  //Test si conjuguable ici
//  //Fonction groupe:
//  if(this->groupe() == 0 ) return this->conjuguerpremier(pronom,temps);
//  else if(this->groupe() == 1 ) return this->conjuguerdeuxieme(pronom,temps);
//  else if(this->groupe() == 2 ) return this->conjuguertroisieme(pronom,temps);
//  else return string();
//}
//
////Gerer les exceptions (ex manger pour nous)
//string Verbe::conjuguerpremier(string pronom,int temps){
//  string mot = this->getInfinitif() ;
//  std::string::size_type size = mot.size();
//  std::size_t pos = size - 2 ;
//  string c = mot.substr(0,pos);
//  string term;
//  switch(temps){
//    case(0): term = ConjPremier::present_.find(pronom)->second;
//	     break;
//    case(2): term = ConjPremier::futur_.find(pronom)->second;
//	     break;
//    default : term = string();
//	      break;
//  }
//  c += term ;
//  return c;
//}
//
//string Verbe::conjuguerdeuxieme(string pronom,int temps){
//
//  string mot = this->getInfinitif() ;
//
//  string c , term;
//
//  switch(temps){
//    case(0): c = mot.substr(0,mot.size()-1);
//	     term = ConjDeuxieme::present_.find(pronom)->second;
//	     break;
//    case(2): c = mot ; 
//	     term = ConjDeuxieme::futur_.find(pronom)->second;
//	     break;
//    default : term = string();
//	      break;
//  }
//  c += term ;
//  return c;
//}
//
//string Verbe::conjuguertroisieme(string pronom,int temps){
//  string mot = this->getInfinitif() ;
//  string c , term;
//  switch(temps){
//    case(0) : return this->troisiemepresent(mot,pronom);
//    default:
//	      return string();
//  }
//  c += term ;
//  return c;
//}
//
////Conjugue au present un verbe du troisieme groupe
//string Verbe::troisiemepresent(string mot, string pronom){
//  string c, term ;
//  if(mot.size() <= 3 ) cerr<<"@attention 3e groupe inf a 3 lettres"<<endl;
//
//  string last_two= mot.substr(mot.size()-2);
//  string last_three= mot.substr(mot.size()-3);
//  string last_four= mot.substr(mot.size()-4);
//
//  if( last_four == "indre" || last_four == "oudre"){
//    //Exception, regarder un dictionnaire
//    return string();
//  }
//  else if (last_three == "cre" || last_three == "dre" || last_three == "tre")
//  {
//    //Appeler struct
//    c = mot.substr(0,mot.size()-2);
//    term = ConjTroisieme::present_credretre.find(pronom)->second;
//    c += term;
//    return c;
//  }
//  else
//  {
//    //Appeler struct par defaut
//    if(last_three == "tir" && (pronom == "il" || pronom == "elle") ) c = mot.substr(0,mot.size()-3);
//    else c = mot.substr(0,mot.size()-2);
//
//    term = ConjTroisieme::present_defaut.find(pronom)->second;
//    c += term;
//    return c;
//
//  }
//
//
//}

