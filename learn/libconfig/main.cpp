#include<libconfig.h++>
#include<iostream>

//ajouter l'emplacement de la librairie au linker : g++ main.cpp -lconfig++ 

using namespace std;
using namespace libconfig;

int main(){

  cout << "test de libconfig " << endl;

  Config cfg ;

  //Verifie que le fichier existe:
  try{
    cfg.readFile("configuration.cfg");
  }
  catch(const FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file " << std::endl;
  }
  //Verifie qu'il n'y a pas d'erreur dans la syntaxe du fichier de configuration:
  catch(const ParseException &pex){
    std::cerr << "Pare error at " << pex.getFile() << " : " << pex.getLine() 
      << " - " << pex.getError() << std::endl;
  }

  //Recupere les données dans un group :
  try{
    string version = cfg.lookup("version");
    cout << "version = " << version << endl;
  }
  catch(SettingNotFoundException &nfex){
    cerr << "No 'version' setting in configuration file " << endl;
  }


  return 0 ; 

}
