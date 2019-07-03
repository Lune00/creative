// Geres les fichiers de config (les features, environement, parametre genetiques etc...) utilises pour initialiser la librairie genetique
#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<iostream>
#include<vector>
#include<libconfig.h++>
#include<exception>
#include<sstream>

class Feature ;

using namespace libconfig ;
using  std::cerr ;
using  std::cout ;
using  std::endl ;

//To be moved elsewhere another time:
//Return factorial of the positive integer n
int fact( int n) ;

namespace exceptions {

  const char * writeMsg( std::ostringstream& os ) ;

  class MyStandardException : public std::exception { 
    public : 
      MyStandardException( const char * Msg, int Line ) {
	std::ostringstream oss ;
	oss << "Error lign " << Line << " --- " << Msg  ; 
	this->msg = oss.str() ;
      }
      virtual const char * what() const throw () { return this->msg.c_str() ; }
    private : 
      std::string msg ;
  } ;

}

namespace geneticParameters {

  extern const int geneSize ;
  extern const double nucleicContribution ; 
}

// Manage Input/Output of features configuration file
namespace featuresIO {

  //File storing the features to be loaded
  const std::string featuresFile = "features.glib" ;
  //Features loaded from the file and in the genetic base
  extern std::vector<Feature*> features ;

  //Loading file functions - main function : 
  void loadFeatures() ;

  bool checkNumberOfCombinations( int numAlleles, int numCotableRules );
  void isFeaturesFilesAndCorrectSyntax() ;
  void parseFeatures() ;
  void parseFeature( const Setting& ) ;

  //Read features settings 
  void readName( const Setting&, Feature* feature ) ;
  void readNature( const Setting&, Feature* feature ) ;
  void readNumGenes( const Setting&, Feature* feature ) ;
  void readAlleles( const Setting&, Feature* feature ) ;
}
#endif
