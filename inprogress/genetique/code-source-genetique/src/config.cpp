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
  const int geneSize = 10 ;
  const double nucleicContribution = 0.1 ;
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
    debugPrintAllAbstractFeaturesToStandardOutput() ;
  }

  // Parse each abstractFeature of abstractFeatures
  void  parseAbstractFeature( const Setting& settingFeature ) {

    Feature * abstractFeature = new Feature() ;

    readLabel( settingFeature, abstractFeature ) ;
    readNature( settingFeature , abstractFeature ) ;
    readNumGenes( settingFeature , abstractFeature ) ;
    readAlleles( settingFeature , abstractFeature ) ;
    readCodominanceRules( settingFeature , abstractFeature  ) ;

    abstractFeatures.push_back( abstractFeature ) ;
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

  //Read the 'codRules' (aka codominanceRule) codominance coefficient between two alleles as a codominanceRule from
  //the config file as strings and load them in a struct pairAllelesCoefficient ( a struct of Feature)
  //Check are performed here for the correct syntax of the Rule (eg number and delimiter)
  //After being read into a vector (if exist) abstractFeature read the vector and process them into pairAllelesCoefficient
  void readCodominanceRules(const Setting& settingFeature, Feature* abstractFeature ){

    std::vector<std::string> vectorCodominanceRules ;

    try {
      const Setting& settingCodominanceRules = settingFeature.lookup( "codRules" ) ;
      for( int j = 0 ; j != settingCodominanceRules.getLength() ; j++ ) {
	vectorCodominanceRules.push_back( settingCodominanceRules[j] ) ;
      }
    }
    catch(const SettingNotFoundException &nfex )
    {
      abstractFeature->buildDefaultPairAllelesCoefficient( )  ;
    }

    abstractFeature->loadPairAllelesCoefficient ( vectorCodominanceRules ) ;

    //Check completness and consistency of the rules , throw exception if not
    abstractFeature->checkPairAllelesCoeffcientCompletness( ) ;
    abstractFeature->checkPairAllelesCoeffcientConsistency( ) ;
  }


  std::string removeWhiteSpacesFromString( std::string string) {
    std::string::iterator end_pos = std::remove( string.begin() , string.end() , ' ') ;
    string.erase( end_pos , string.end() ) ;
    return string ;
  }

  void debugPrintAllAbstractFeaturesToStandardOutput() {
    cout << "Library of features contains : " << endl ;
    for( std::vector<Feature*>::const_iterator it = abstractFeatures.begin() ; it != abstractFeatures.end() ; it++ ) {
      (*it)->debugPrintToStandardOutput();
    }
  }
}



