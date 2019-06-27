#include"feature.h"
#include"gene.h"

using namespace std ; 

Feature::Nature Feature::stringToEnum( std::string nature ) {

  if( nature == "C" || nature == "Continuous" ) return Feature::Nature::C ;
  else if ( nature == "D" || nature == "Discrete" ) return Feature::Nature::D ;
  else return  Feature::Nature::Undefined ;
}


string Feature::enumToString( Feature::Nature nature ) {

  switch( nature ) {
    case D : return "Discrete" ;
    case C : return "Continuous" ;
    case Undefined : return "Undefined" ;
  }
}

void Feature::print_debug( ) {

  std::cerr << "Name : " << name_ << std::endl ;
  std::cerr << "Nature : " << enumToString( nature_ ) << std::endl ; 
  std::cerr << "Number of genes : " << nGenes_ << std::endl ; 
}

bool Feature::setNumGenes( int nGenes ) {

  if( nGenes < 0 || nGenes == 0 ) {
    cerr << "Number of Genes must be greater than or equal to 1 " << endl ;
    return( EXIT_FAILURE ) ;
  }
  else nGenes_ = nGenes ; 
}