#include"config.h"
#include"feature.h"
#include"gene.h"
#include<sstream>

using namespace std ; 


Feature::Feature() {

  // [ ni lignes * nj colonnes ] Element[i][j] = i * nj + j , 0 < j < nj and 0 < i < ni
  //double * codominanceTable_ = new double [ geneticParameters::geneSize * geneticParameters::geneSize ] ;

}

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
  std::cerr << "Number of genes : " << numGenes_ << std::endl ; 
  std::cerr << "Number of alleles : " << alleles_.size() << std::endl ; 
}

void Feature::setNumGenes( int numGenes ) {

  if( numGenes < 0 || numGenes == 0 ) {
      ostringstream oss ;
      oss << "Feature : " << this->name() << " - Number of Genes [numGenes] should be greater than 0 " ;
      throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
  }
  else numGenes_ = numGenes ; 
}

void Feature::setAllelesDefinedManually ( bool AllelesDefinedManually ) {
  AllelesDefinedManually_ = AllelesDefinedManually ; 
}

//Check the validity of alleles and add them from the configuration file
void Feature::setAlleles( const std::vector<int>& alleles ) {
  
  std::vector<int>::const_iterator it = alleles.begin( ) ;
  while ( it != alleles.end() ){
    int a = *it ;

    if ( a >= geneticParameters::geneSize || a < 0 ) {
      ostringstream oss ;
      oss << "Feature : " << this->name() << " " << a << " is not an accepted value. Must lie in the range [0:" << geneticParameters::geneSize - 1 <<"] " ;
      throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
    }

    it++;
  }

  alleles_ =  alleles ;

}

void Feature::setAllelesDefault( ) {
  alleles_.clear() ;
  for ( int j = 0 ; j != geneticParameters::geneSize ; j++ ) {
    alleles_.push_back( j ) ;
  }
}

void Feature::setCodominanceCoefficients( const std::vector<std::string>& vectorCodominanceCoefficientsString ) {

  //Check that each int (allele id) match alleles stored in alleles_ 
  //Check that every combination have been covered : 
  // at this time we know that each int is an allele stored in alleles_ 
  // Add same allele id the value 1 for codominance between them 
  for (unsigned int i = 0 ; i != vectorCodominanceCoefficientsString.size() ; i ++ ) {

    std::string CodominanceRule = vectorCodominanceCoefficientsString[ i ] ;
    //Split string into two int (alleles) and a double (coefficient) (possible use of regex here)
    Feature::allelesAndCoeff alCo = splitCodominanceRuleIntoAllelesAndCoeff ( CodominanceRule ) ; 
  }

}

//No REGEX yet, we assume the format is %d-%d:%f (int-int:double)
Feature::allelesAndCoeff Feature::splitCodominanceRuleIntoAllelesAndCoeff( const std::string & CodominanceRule ) {

  //Split : 

}
