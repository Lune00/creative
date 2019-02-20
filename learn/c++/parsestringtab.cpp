#include<string>
#include<iostream>
#include<vector>
//On a une phrase avec un delimiter(tab) et on veut le couper elements
using namespace std;

//Fonction prend en argument un string et le decoupe en element separes par un delimiteur.
//Elle renvoie les éléments découpés dans un vecteur de tokens
//Cette fonction fonctionne si les champs séparés sont vides.

vector<std::string> parsestring(string stringtoparse, string delimiter)
{
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
  return tokens;
}

int main(){

  string stringtoparse="A\t\tC\tD";

  vector<string> tokens = parsestring(stringtoparse,"\t");

  vector<string>::iterator it = tokens.begin();

  for(it = tokens.begin() ; it != tokens.end(); it++){
    cout<<*it<<endl;
  }


  return 0;

}
