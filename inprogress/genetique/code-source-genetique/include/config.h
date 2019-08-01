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
#include <boost/functional/hash.hpp>

class Feature ;

using namespace libconfig ;
using  std::cerr ;
using  std::cout ;
using  std::endl ;

namespace geneticParameters {

  extern const int geneSize ;

  // D : Discrete (ex : color of the eyes) C : Continuous value of the trait (ex : height)
  enum Nature { D = 0 , C = 1, Undefined = 2 } ;
  Nature stringToEnum( std::string ) ; 
  std::string enumToString( Nature ) ; 
}


namespace configRules {

  //Rule stating the relation between alleles of the same pair (of one gene)
  struct Rule {

    std::pair < int , int > pairAlleles_ ;
    double domination_ ; 
    bool discreteCaseWithProbability_ ;

    //State saying that the rule is correct and can be used :
    bool isCorrect_ ;

    //Alleles always stored as a pair(a,b) with a <= b
    Rule(int allele1, int allele2, double domination, bool discreteCaseWithProbability = false, bool isCorrect = true ) :
      discreteCaseWithProbability_(discreteCaseWithProbability), isCorrect_(isCorrect)
    {
      if ( allele1 < allele2 ) { 
	pairAlleles_ = std::make_pair( allele1 , allele2 ) ;
	domination_ = domination ; 
      }
      else {
	pairAlleles_ = std::make_pair( allele2 , allele1 ) ;
	domination_ = 1. - domination ;
      }
    }

    //Works properly whatever the nature 
    Rule( int allele ) {
      pairAlleles_ = std::make_pair ( allele, allele ) ;
      domination_ = 1. ;
      discreteCaseWithProbability_ = false ;
    }

    Rule(int allele1, int allele2 , bool isCorrect) : isCorrect_(isCorrect) {
      pairAlleles_ = std::make_pair( allele1 , allele2 ) ;
      domination_ = 1. ;
      discreteCaseWithProbability_ = false ;
    }

    //Equality 
    bool operator==(const Rule& r ) const {
      if ( pairAlleles_ == r.pairAlleles_ )
	return true;
      else
	return false;
    }

  };

  //Hash function based on pairAlleles_ only!
  struct RuleHasher
  {
    size_t
      operator()(const Rule & obj) const
      {
	return boost::hash<std::pair <int, int > >()(obj.pairAlleles_) ;
      }
  };

  //Random (random number) , Increasing (greater coeff for high alleles) , Decreasing (greater coeff for low alleles )
  enum buildRulesOption { Random = 0 , Increasing = 1 , Decreasing = 2, Undefined = 3 } ;
  buildRulesOption stringToEnum( std::string ) ;
  std::string enumToString( buildRulesOption ) ;

  bool isBuildRulesOption( const std::vector<std::string>& ) ;
  buildRulesOption getBuildRulesOption( const std::vector<std::string>& ) ;

  std::unordered_set<Rule, RuleHasher> buildRandomRules( const geneticParameters::Nature& , const std::vector<int> alleles ) ;
  std::unordered_set<Rule, RuleHasher> buildIncreasingRules( const geneticParameters::Nature& , const std::vector<int> alleles ) ;
  std::unordered_set<Rule, RuleHasher> buildDecreasingRules( const geneticParameters::Nature& , const std::vector<int> alleles ) ;

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

#endif
