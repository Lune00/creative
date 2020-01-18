#include "config.h"
#include<iostream>

//TEST du code source

using namespace std;

int main(){

  cout << "- Genetic Library - \n";

  //load configurations files :
  try {
    featuresIO::loadAbstractFeatures() ;
  }
  //File not found
  catch( const FileIOException &fioex ) {
    std::cerr << "Configuration file '"<<featuresIO::abstractFeaturesFile <<"' not found. " << std::endl;
    return EXIT_FAILURE ;
  }
  //Syntaxic error in the libconfig format
  catch( const ParseException &pex ) {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
      << " - " << pex.getError() << std::endl;
    return EXIT_FAILURE  ;
  }
  catch( const SettingNotFoundException &nfex ) {
    std::cerr << nfex.getPath() <<" group/setting not found in " <<featuresIO::abstractFeaturesFile << endl;
    return EXIT_FAILURE ;
  }
  catch( const exceptions::MyStandardException& ex) {
    std::cerr << ex.what() << endl ;
    return EXIT_FAILURE ; 
  }


  //Use library :

  return 0;
}
