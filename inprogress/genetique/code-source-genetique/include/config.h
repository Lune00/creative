// Geres les fichiers de config (les features, environement, parametre genetiques etc...) utilises pour initialiser la librairie genetique
#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<iostream>
#include<vector>
#include<exception>
#include<sstream>
#include<regex>
#include<algorithm>
#include<libconfig.h++>

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

namespace debug {

  void debugPrintAllAbstractFeaturesToStandardOutput( ) ;
  void debugPrint(const std::string&) ;

}

// Manage Input/Output of features configuration file
namespace featuresIO {

  //File storing the features to be loaded
  const std::string abstractFeaturesFile = "abstractFeatures.glib" ;

  //Syntax of the codRules
  //const std::string regexContinuousFeature = "[0-9]*-[0-9]*=(0\.?[0-9]*|1\.[0]*$|1$)" ;
  const std::string regexContinuousFeature = "[0-9]*-[0-9]*=(0\\.?[0-9]*|1\\.[0]*$|1$)" ;
  const std::string regexDiscreteFeature = "[0-9]*-[0-9]*=[0-9]*$" ;
  //Match 2 syntaxes : 
  // 'a-b=a' (where a always dominate b (equiv a-b=p1.) or
  // 'a-b=p0.3' (where a dominates b with probability p=0.3) 
  const std::string regexDiscreteFeatureBothSyntaxes = "[0-9]*-[0-9]*=([0-9]*$|p(0\\.?[0-9]*|1\\.[0]*$))" ;
  const std::string delimiterAllele = "-" ;
  const std::string delimiterCoefficient = "=" ;

  //Features loaded from the file and in the genetic base
  extern std::vector<Feature*> abstractFeatures ;

  //Loading file functions - main function : 
  void loadAbstractFeatures() ;

  bool checkNumberOfCombinations( int numAlleles, int numCotableRules );
  void isAbstractFeaturesFileAndCorrectSyntax() ;
  void parseAbstractFeatures() ;
  void parseAbstractFeature( const Setting& ) ;

  //Read features settings 
  void readLabel( const Setting&, Feature* feature ) ;
  void readNature( const Setting&, Feature* feature ) ;
  void readNumGenes( const Setting&, Feature* feature ) ;
  void readAlleles( const Setting&, Feature* feature ) ;
  void readCodominanceRules( const Setting&, Feature* feature ) ;

  //String parsing for entry
  std::string removeWhiteSpacesFromString( std::string ) ;

}
#endif
