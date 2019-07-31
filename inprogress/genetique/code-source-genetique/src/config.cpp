#include "config.h"
#include "feature.h"
#include<stdlib.h>
#include<stdexcept>

int fact( int n ) {

  if( n < 0 ) { cerr << "integer n is not positive \n" ; return 1 ; }
  if ( n == 0 || n == 1 ) return 1 ;
  else return n * fact ( n-1 ) ;
}


namespace exceptions {
  const char * writeMsg( std::ostringstream& os ) {
    std::string Msg = os.str() ;
    return Msg.c_str() ;
  }
}

namespace geneticParameters {

  //Size of a gene , i.e number of alleles availables
  const int geneSize = 10 ;

  buildRulesOption stringToEnum(std::string option) {
    if( option == "random" || option.empty() ) 
      return buildRulesOption::Random ;
    else if( option == "increasing" ) 
      return buildRulesOption::Increasing ;
    else if( option == "decreasing" ) 
      return buildRulesOption::Decreasing ;
    else
      return buildRulesOption::Undefined ;
  }

  std::string enumToString( buildRulesOption option ) {
    switch( option ) {
      case Random : return "random" ;
      case Increasing : return "increasing" ;
      case Decreasing : return "decreasing" ;
      case Undefined : return "undefined" ;
    }
  }

  //Return true if it detects the presence in the setting "codRules" of any building options for Rules
  bool isBuildRulesOption(const std::vector<std::string>& Rules ) {
    for( size_t i = 0 ; i != Rules.size() ; i++){
      if( Rules[i] == "random" || Rules[i] == "increasing" || Rules[i] == "decreasing" ) 
	return true ;
    }
    return false ;
  }

  buildRulesOption getBuildRulesOption( const std::vector<std::string>& Rules ) {

    for( size_t i = 0 ; i != Rules.size() ; i++){
      if( Rules[i] == "random" )
	return buildRulesOption::Random ;
      else if( Rules[i] == "increasing" )
	return buildRulesOption::Increasing ;
      else if ( Rules[i] == "decreasing" ) 
	return buildRulesOption::Decreasing ;
    }
    return buildRulesOption::Undefined ;
  }

}


namespace featuresIO {

  std::vector<Feature*> abstractFeatures(0) ;

  void loadAbstractFeatures() {
    isAbstractFeaturesFileAndCorrectSyntax() ;
    parseAbstractFeatures() ;
  }

  bool checkNumberOfCombinations( int nalleles, int nCotableRules ) {

    int ncombinations = fact( nalleles ) / (fact( nalleles - 2 ) * 2) ;

    return ( ncombinations == nCotableRules );
  }

  //Check that featuresFile exists and no libconfig syntax issues in it
  void isAbstractFeaturesFileAndCorrectSyntax() {
    Config cfg ;
    cfg.readFile( abstractFeaturesFile.c_str() );
  }

  // Parse abstractFeatures add them to the features library. Throw exception if not found the setting
  void parseAbstractFeatures() {

    Config cfg ;

    cfg.readFile( abstractFeaturesFile.c_str() );

    const Setting& root = cfg.getRoot() ;

    const Setting &settingFeatures = root["abstractFeatures"] ;

    int nfeatures = settingFeatures.getLength() ;

    for ( int i = 0 ;i != nfeatures; i++ ) {
      const Setting& settingFeature = settingFeatures[ i ] ;
      parseAbstractFeature( settingFeature ); 
    }
    cerr << "Number of features loaded : " << abstractFeatures.size() << endl ;
    debug::debugPrintAllAbstractFeaturesToStandardOutput() ;
  }

  // Parse each abstractFeature of abstractFeatures
  void  parseAbstractFeature( const Setting& settingFeature ) {

    Feature * abstractFeature = new Feature() ;

    //Read from file
    readLabel( settingFeature, abstractFeature ) ;
    readNature( settingFeature , abstractFeature ) ;
    readNumGenes( settingFeature , abstractFeature ) ;
    readAlleles( settingFeature , abstractFeature ) ;
    readCodominanceRules( settingFeature , abstractFeature  ) ;
    //Add to library
    abstractFeatures.push_back( abstractFeature ) ;

    cout << "abstract feature loaded. " << endl ;
  }

  // Load name of the feature - mandatory
  void readLabel(const Setting& settingFeature, Feature* abstractFeature ) {

    abstractFeature->setLabel( settingFeature.lookup( "label" ) ) ;
  }

  // Load nature of the feature - mandatory
  void readNature(const Setting& settingFeature, Feature* abstractFeature ) {

    abstractFeature->setNature( settingFeature.lookup( "nature" ) ) ;
  }
  // Load nature of the feature - mandatory
  void readNumGenes(const Setting& settingFeature, Feature* abstractFeature ) {

    int numGenes = settingFeature.lookup( "nGenes" ) ;
    abstractFeature->setNumGenes( numGenes ) ;
  }


  // Load alleles of the genes - optional parameter
  void readAlleles(const Setting& settingFeature, Feature* abstractFeature ) {

    std::vector<int> vector_alleles ;

    //Local catch because 'alleles' is optional
    try {
      const Setting& settingAlleles = settingFeature.lookup( "alleles" ) ;

      for( int j = 0 ; j != settingAlleles.getLength() ; j++ ) {
	vector_alleles.push_back( settingAlleles[j] ) ;
      }

      abstractFeature->setAlleles( vector_alleles ) ;
      abstractFeature->setAllelesDefinedManually ( true ) ;

    }

    //If 'alleles' not found it is ok, default parameters
    //The absence of 'allele' here do not need to emit error end the program
    catch(const SettingNotFoundException &nfex)
    {
      // Default behavior : all alleles included (10) 
      abstractFeature->setAllelesDefinedManually ( false ) ;
      abstractFeature->setAllelesDefault( ) ;
    }

  }

  //Read the 'codRules' (aka Rules) or codominance coefficient between two alleles from
  //the config file as strings and load them in a struct 'Rule' ( a struct of Feature)
  //Check are performed here for the correct syntax of the Rule (eg number and delimiter) and logic
  void readCodominanceRules(const Setting& settingFeature, Feature* abstractFeature ){

    std::vector<std::string> vectorStringRules ;

    try {

      const Setting& settingRules = settingFeature.lookup( "codRules" ) ;

      for( int j = 0 ; j != settingRules.getLength() ; j++ ) {
	vectorStringRules.push_back( settingRules[j] ) ;
      }

    }
    //If no "codRules" setting : defaultbuild for Rules is 'random' as a default behavior
    catch(const SettingNotFoundException &nfex )
    {
      abstractFeature->buildDefaultRules( geneticParameters::buildRulesOption::Random )  ;
    }

    //Check for Default Rules options : random , increasing, decreasing detected. If found, has priority
    if( geneticParameters::isBuildRulesOption( vectorStringRules ) ) {

      geneticParameters::buildRulesOption option = geneticParameters::getBuildRulesOption( vectorStringRules ) ;
      abstractFeature->buildDefaultRules( option ) ;
    }
    else {
      abstractFeature->loadRules ( vectorStringRules ) ;
    }

    //Check completness for the Rules of the feature
    abstractFeature->checkRulesCompletness( ) ;
  }

  std::string removeWhiteSpacesFromString( std::string string) {
    std::string::iterator end_pos = std::remove( string.begin() , string.end() , ' ') ;
    string.erase( end_pos , string.end() ) ;
    return string ;
  }

}

namespace debug {

  void debugPrintAllAbstractFeaturesToStandardOutput() {
    cout << "Library of features contains : " << endl ;
    for( std::vector<Feature*>::const_iterator it = featuresIO::abstractFeatures.begin() ; it != featuresIO::abstractFeatures.end() ; it++ ) {
      (*it)->debugPrintToStandardOutput();
    }
  }
  void debugPrintToStandardOutput(const std::string string ) {
    std::cout << string << std::endl ;
  }
}


