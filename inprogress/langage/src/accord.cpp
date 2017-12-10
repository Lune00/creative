#include "accord.hpp"

const map<string,string> Exception_NC::NCP = Exception_NC::makeNPC();

//Renvoie le nom propre avec le bon accord
string NomC::accorder(string article){

  string mot = this->mot_;
  string term ;

  //On regarde si l'article est au pluriel
  if(article.back() == 's') 
  {
    //Regarde si c'est un cas particulier
    std::map<string,string>::const_iterator it =  Exception_NC::NCP.find(mot);
    if(it != Exception_NC::NCP.end()) {
      return it->second;
    }

    //ex : des os
    if(mot.back() == 's' || mot.back() == 'z' || mot.back() == 'x' ) return mot;

    //Checker la taille
    if( mot.size() >= 3)
    {
      string last_one= mot.substr(mot.size()-2);
      string last_two= mot.substr(mot.size()-2);
      string last_three= mot.substr(mot.size()-3);

      //On rajoute un x
      if( last_two == "au" || last_two == "eu" || last_three == "eau") 
      {
	mot += "x";
	return mot;
      }
      //On enleve -al et on remplace par -aux
      else if (last_two == "al") 
      {
	mot = mot.substr(0,mot.size()-2);
	mot += "aux";
	return mot;
      }
      else
      {
	mot += "s";
	return mot;
      }

    }
    else
    {
      //On renvoie avec un s par défaut
      mot += "s";
      return mot;
    }

  }
  else
  {
    return this->mot_;
  }
}
