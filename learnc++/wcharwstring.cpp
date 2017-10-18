#include<iostream>
#include <sstream>
#include<string>
#include<wchar.h>

using namespace std;

int main(){

  //Comment sont codés les caracteres avec accents?
  //Les donnees peuvent changer d'un Os a l'autre j'imagine
  cout<<"Hello wchar/wstrings: traitement des accents"<<endl;
  string c = "àèéêç";

  cout<<c<<endl;
  for(unsigned int i = 0 ; i != c.size() ; i++){
    cout<<c.substr(i,1)<<" "<<int(c[i])<<endl;
  }
  c = "aeeec";
  cout<<c<<endl;
  for(unsigned int i = 0 ; i != c.size() ; i++){
    cout<<c.substr(i,1)<<" "<<int(c[i])<<endl;
  }


  //Test minimal pour detecter un accent(on cherche juste a gerer l'élision, majuscule)
  string s = "Un bel été";
  cout<<s<<endl;
  for(unsigned int i = 0 ; i != s.size() ; i++){
    if( int(s[i]) < 0 ) cout<<"Il y a un accent!"<<endl;
    //Je sais maintenant qu'un accent est codé sur 2 caracteres: le premier indique 
  }

  
  //Test Unicode:
  int x = 0xC3 ;
  cout <<x <<endl;
  cout<< "\u00E9" <<endl;



  return 0;
}
