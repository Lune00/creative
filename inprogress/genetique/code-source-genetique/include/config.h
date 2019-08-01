// Manage and load config files  ( abstractFeatures, environement ... ) and  genetic model parameters 
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
#include<unordered_set>

class Feature ;

using namespace libconfig ;
using  std::cerr ;
using  std::cout ;
using  std::endl ;

namespace exceptions {

  const char * writeMsg( std::ostringstream& os ) ;

  class MyStandardException : public std::exception { 
    public : 
      MyStandardException( const char * Msg, int Line ) {
	std::ostringstream oss ;
	//oss << "Error thrown at lign " << Line << " in the sourcecode - " << Msg ; 
	oss << Msg << " line " << Line  ; 
	this->msg = oss.str() ;
      }
      virtual const char * what() const throw () { return this->msg.c_str() ; }
    private : 
      std::string msg ;
  } ;

}

namespace configRules {

  //Build default Rules options :
  //Random (random number) , Increasing (greater coeff for high alleles) , Decreasing (greater coeff for low alleles )
  enum buildRulesOption { Random = 0 , Increasing = 1 , Decreasing = 2, Undefined = 3 } ;
  buildRulesOption stringToEnum( std::string ) ;
  std::string enumToString( buildRulesOption ) ;

  bool isBuildRulesOption( const std::vector<std::string>& ) ;
  buildRulesOption getBuildRulesOption( const std::vector<std::string>& ) ;

  //std::unordered_set<Feature::Rule> buildRandomRules(const std::string& nature , const std::vector<int> alleles ) ;
  //std::unordered_set buildIncreasingRules(const std::string& nature , const std::vector<int> alleles ) ;
  //std::unordered_set buildDecreasingRules(const std::string& nature , const std::vector<int> alleles ) ;

}

//Options and const for the genetic model
namespace geneticParameters {

  extern const int geneSize ;
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
  const std::string regexContinuousFeature = "[0-9]*-[0-9]*=(0\\.?[0-9]*|1\\.[0]*$|1$)" ;
  //Deprecated
  const std::string regexDiscreteFeature = "[0-9]*-[0-9]*=[0-9]*$" ;
  //Match 2 syntaxes : 
  // 'a-b=a' (where a always dominate b (equiv a-b=p1.) or
  // 'a-b=p0.3' (where a dominates b with probability p=0.3) 
  const std::string regexDiscreteFeatureBothSyntaxes = "[0-9]*-[0-9]*=([0-9]*$|p(0\\.?[0-9]*|1\\.[0]*$))" ;
  const std::string delimiterAllele = "-" ;
  const std::string delimiterCoefficient = "=" ;
  const std::string flagProbability = "p" ;

  //Loading file functions - main function : 
  void loadAbstractFeatures() ;

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

  //Features loaded from the file and in the genetic base
  extern std::vector<Feature*> abstractFeatures ;
}
#endif
