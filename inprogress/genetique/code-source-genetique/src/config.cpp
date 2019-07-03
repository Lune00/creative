#include "config.h"
#include "feature.h"

int fact( int n ) {

  if( n < 0 ) { cerr << "integer n is not positive \n" ; return 1 ; }
  if ( n == 0 || n == 1 ) return 1 ;
  else return n * fact ( n-1 ) ;
}

namespace featuresIO {

  std::vector<Feature*> features(0) ;

  bool checkNumberOfCombinations( int nalleles, int nCotableRules ) {

    int ncombinations = fact( nalleles ) / (fact( nalleles - 2 ) * 2) ;

    return ( ncombinations == nCotableRules );
  }

  //Check that featuresFile exists and no libconfig syntax issues in it
  bool isFeaturesFilesAndCorrectSyntax() {

    Config cfg ;

    try{
      cfg.readFile( featuresFile.c_str() );
      cout << featuresFile << " loaded \n" ;
    }

    catch( const FileIOException &fioex ) {
      std::cerr << "I/O error while reading file " << std::endl;
      return( EXIT_FAILURE );
    }

    catch( const ParseException &pex ) {
      std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
	<< " - " << pex.getError() << std::endl;
      return( EXIT_FAILURE ) ;
    }

    return true ;
  }

  bool loadFeatures() {

    if( !isFeaturesFilesAndCorrectSyntax() ) return false;

    else return parseFeatures( ) ;
  }

  //Check that group 'features' exists, if true parse them and
  //add them to the features library
  bool parseFeatures() {

    Config cfg ;

    cfg.readFile( featuresFile.c_str() );

    const Setting& root = cfg.getRoot() ;

    try{
      const Setting &settingFeatures = root["features"] ;

      int nfeatures = settingFeatures.getLength() ;

      for ( int i = 0 ;i != nfeatures; i++ ) {
	const Setting& settingFeature = settingFeatures[ i ] ;
	parseFeature( settingFeature ); 
      }

    }
    catch( const SettingNotFoundException &nfex ) {
      cerr << " No 'features' group in configuration file " << endl;

      return( EXIT_FAILURE );
    }

    cerr << "Number of features loaded : " << features.size() << endl ;

    return true ;
  }

  // Parse each feature of features
  void  parseFeature( const Setting& settingFeature ) {

    Feature * feature = new Feature() ;

    //Load settings : 
    readName( settingFeature, feature ) ;
    readNature( settingFeature , feature ) ;
    readNumGenes( settingFeature , feature ) ;

    feature->print_debug() ;

    features.push_back( feature ) ;
  }

  // Load name of the feature
  bool readName(const Setting& settingFeature, Feature* feature ) {

    try {
      feature->setName( settingFeature.lookup( "name" ) ) ;
    }

    catch( const SettingNotFoundException &nfex ) {
      cerr << "No 'name' setting in "<< featuresFile << endl ;
      return( EXIT_FAILURE ) ;
    }
  }
  
  // Load nature of the feature
  bool readNature(const Setting& settingFeature, Feature* feature ) {

    try {
      feature->setNature( settingFeature.lookup( "nature" ) ) ;
    }

    catch( const SettingNotFoundException &nfex ) {
      cerr << "No 'nature' setting in "<< featuresFile << endl ;
      return( EXIT_FAILURE ) ;
    }
  }
  // Load nature of the feature
  bool readNumGenes(const Setting& settingFeature, Feature* feature ) {

    try {
      int numGenes = settingFeature.lookup( "nGenes" ) ;
      feature->setNumGenes( numGenes ) ;
    }

    catch( const SettingNotFoundException &nfex ) {
      cerr << "No 'nGenes' setting in "<< featuresFile << endl ;
      return( EXIT_FAILURE ) ;
    }
  }


  bool readAlleles(const Setting& settingFeature, Feature* feature ) {

    std::vector<int> vector_alleles ;

    try {
      const Setting& settingAlleles = settingFeature.lookup( "alleles" ) ;

      for( int j = 0 ; j != settingAlleles.getLength() ; j++ ) {
	vector_alleles.push_back( settingAlleles[j] ) ;
      }

      feature->setAlleles( vector_alleles ) ;
      feature->setAllelesDefinedManually ( true ) ;

      return true ;
    }

    catch(const SettingNotFoundException &nfex)
    {
      cerr << "Default 'allele pool' applied for this feature" <<endl;
      // Default behavior : all alleles included (10) 
      feature->setAllelesDefinedManually ( false ) ;

      return true ;
    }

  }
}
