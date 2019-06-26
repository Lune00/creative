#include"config.h"

int fact(int n){
  if( n < 0 ) cerr << "integer n is not positive \n";
  if (n == 0 || n == 1) return 1 ;
  else return n * fact (n-1);
}

namespace cfgIO{

  bool checkNumberOfCombinations(int nalleles, int nCotableRules){
    int ncombinations = fact(nalleles) / ( fact( nalleles - 2 ) * 2) ;
    return (ncombinations == nCotableRules);
  }

  bool readFeaturesFile(){
    Config cfg ;
  //Verifie que le fichier existe et pas d'erreur de syntaxe:
  try{
    cfg.readFile(featuresFile.c_str());
    cout << featuresFile << " loaded \n" ;
  }
  catch(const FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file " << std::endl;
    return(EXIT_FAILURE);
  }
  catch(const ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return(EXIT_FAILURE);
  }
    return true ;
  }
}
