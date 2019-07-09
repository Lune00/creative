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

  std::vector<Feature*> features(0) ;

  void loadFeatures() {
    isFeaturesFilesAndCorrectSyntax() ;
    parseFeatures() ;
  }

  bool checkNumberOfCombinations( int nalleles, int nCotableRules ) {

    int ncombinations = fact( nalleles ) / (fact( nalleles - 2 ) * 2) ;

    return ( ncombinations == nCotableRules );
  }

  //Check that featuresFile exists and no libconfig syntax issues in it
  void isFeaturesFilesAndCorrectSyntax() {
    Config cfg ;
    cfg.readFile( featuresFile.c_str() );
  }

  // Parse features add them to the features library. Throw exception
  void parseFeatures() {

    Config cfg ;

    cfg.readFile( featuresFile.c_str() );

    const Setting& root = cfg.getRoot() ;

    const Setting &settingFeatures = root["features"] ;

    int nfeatures = settingFeatures.getLength() ;

    for ( int i = 0 ;i != nfeatures; i++ ) {
      const Setting& settingFeature = settingFeatures[ i ] ;
      parseFeature( settingFeature ); 
    }
    cerr << "Number of features loaded : " << features.size() << endl ;
  }

  // Parse each feature of features
  void  parseFeature( const Setting& settingFeature ) {

    Feature * feature = new Feature() ;

    readName( settingFeature, feature ) ;
    readNature( settingFeature , feature ) ;
    readNumGenes( settingFeature , feature ) ;
    readAlleles( settingFeature , feature ) ;
    readCodominanceCoefficients( settingFeature , feature  ) ;

    features.push_back( feature ) ;
  }

  // Load name of the feature - mandatory
  void readName(const Setting& settingFeature, Feature* feature ) {

      feature->setName( settingFeature.lookup( "name" ) ) ;
  }

  // Load nature of the feature - mandatory
  void readNature(const Setting& settingFeature, Feature* feature ) {

      feature->setNature( settingFeature.lookup( "nature" ) ) ;
  }
  // Load nature of the feature - mandatory
  void readNumGenes(const Setting& settingFeature, Feature* feature ) {

      int numGenes = settingFeature.lookup( "nGenes" ) ;
      feature->setNumGenes( numGenes ) ;
  }


  // Load alleles of the genes - optional parameter
  void readAlleles(const Setting& settingFeature, Feature* feature ) {

    std::vector<int> vector_alleles ;

    //Local catch because 'alleles' is optional
    try {
      const Setting& settingAlleles = settingFeature.lookup( "alleles" ) ;

      for( int j = 0 ; j != settingAlleles.getLength() ; j++ ) {
	vector_alleles.push_back( settingAlleles[j] ) ;
      }

      feature->setAlleles( vector_alleles ) ;
      feature->setAllelesDefinedManually ( true ) ;

    }

    //If 'alleles' not found it is ok, default parameters
    //The absence of 'allele' here do not need to emit error end the program
    catch(const SettingNotFoundException &nfex)
    {
      // Default behavior : all alleles included (10) 
      feature->setAllelesDefinedManually ( false ) ;
      feature->setAllelesDefault( ) ;
    }

  }

  void readCodominanceCoefficients(const Setting& settingFeature, Feature* feature ){

    std::vector<std::string> vectorCodominanceCoefficientsString ;

    try {

      const Setting& settingCodominanceCoefficients = settingFeature.lookup( "codcoeff" ) ;

      for( int j = 0 ; j != settingCodominanceCoefficients.getLength() ; j++ ) {

	vectorCodominanceCoefficientsString.push_back( settingCodominanceCoefficients[j] ) ;

      }
	//A la feature de constuire en interne le reste, et non au read
	feature->setCodominanceCoefficients ( vectorCodominanceCoefficientsString ) ;
    }

    catch(const SettingNotFoundException &nfex )
    {
      // If feature is Discrete : random codominance coefficients are either 0 or 1 (integer)
      // If feature is Continuous : random codominance coefficients are between 0 and 1 (floating)
      switch ( feature->nature() ) {

	case Feature::D : 
	  cout << "D\n";
	  break ;

	case Feature::C : 
	  cout << "C\n" ;
	  break ;

	case Feature::Undefined : 
	  cout<< "Undefined\n" ;
      }
    }
  }
}



