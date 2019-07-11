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

  std::cerr << "Label : " << label_ << std::endl ;
  std::cerr << "Nature : " << enumToString( nature_ ) << std::endl ; 
  std::cerr << "Number of genes : " << numGenes_ << std::endl ; 
  std::cerr << "Number of alleles : " << alleles_.size() << std::endl ; 
}

void Feature::setNumGenes( int numGenes ) {

  if( numGenes < 0 || numGenes == 0 ) {
      ostringstream oss ;
      oss << "Feature : " << this->label() << " - Number of Genes [numGenes] should be greater than 0 " ;
      throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
  }
  else numGenes_ = numGenes ; 
}

void Feature::setAllelesDefinedManually ( bool AllelesDefinedManually ) {
  AllelesDefinedManually_ = AllelesDefinedManually ; 
}

void Feature::setNature( std::string stringNature ) {

  Feature::Nature nature = stringToEnum( stringNature ) ;

  if ( nature == Nature::Undefined ) {
    ostringstream oss ;
    oss << "Feature : " << this->label() << " has undefined nature. Must be (D)iscrete or (C)ontinuous" ;
    throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
    return ;
  }

  else
    nature_ = nature ;
}

//Check the validity of alleles and add them from the configuration file
void Feature::setAlleles( const std::vector<int>& alleles ) {

  std::vector<int>::const_iterator it = alleles.begin( ) ;
  while ( it != alleles.end() ){
    int a = *it ;

    if ( a >= geneticParameters::geneSize || a < 0 ) {
      ostringstream oss ;
      oss << "Feature : " << this->label() << " " << a << " is not an accepted value. Must lie in the range [0:" << geneticParameters::geneSize - 1 <<"] " ;
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

  for (unsigned int i = 0 ; i != vectorCodominanceCoefficientsString.size() ; i ++ ) {

    std::string CodominanceRule = vectorCodominanceCoefficientsString[ i ] ;
    std::string CodominanceRuleWithouSpaces  = featuresIO::removeWhiteSpacesFromString( CodominanceRule ) ;

    //Check the Rule (correct expression)
    if( ! checkRegexForCodominanceRule( CodominanceRuleWithouSpaces ) )  {

      //Throw exception : 
      ostringstream oss ;
      oss << "Feature : " << this->label() << " has invalid 'codcoeff' syntax." ;
      throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
      return ;

    }
    else 
      //Split string into two int (alleles) and a double (coefficient) 
      Feature::allelesAndCoeff alCo = splitCodominanceRuleIntoAllelesAndCoeff ( CodominanceRuleWithouSpaces ) ; 
    //Store
  }

  //ANOTHER FUNCTION HERE
  //Here we have a collection of syntaxcially correct alCo.  We then need to check the logical aspects: 

  //Check that each int (allele id) match alleles stored in alleles_ 
  //Check that every combination have been covered : 
  // at this time we know that each int is an allele stored in alleles_ 
  // Add same allele id the value 1 for codominance between them 

}

//Check the Rule expression read from user file, check Regex depending on the nature of the feature
bool Feature::checkRegexForCodominanceRule( const std::string& Rule ) {

  switch ( this->nature() ) { 
    case C : 
      //Regex for Continuous Feature : check that arguments are integer and double < 1.0 (ex : 1-2=0.5)
      if( std::regex_match ( Rule , std::regex(featuresIO::regexContinuousFeature)) ) 
	return true ;
      else
	return false; 
      //Regex for Discrete Feature : check that arguments are integer and integer (ex : 1-2=2 , 2 dominates 1)
    case D : 

      if( std::regex_match ( Rule , std::regex(featuresIO::regexDiscreteFeature)) )
	return true ;
      else
	return false; 
    case Undefined :
      return false ;
  }
}


//This function is called after Regex Check on the rule provided by the user. So we KNOW that the rule
//is SYNTAXICALLY correct (type, number) and we can process it without any further tests
Feature::allelesAndCoeff Feature::splitCodominanceRuleIntoAllelesAndCoeff( const std::string & CodominanceRuleWithouSpaces ) {

  size_t pos = 0 ;
  pos = CodominanceRuleWithouSpaces.find( featuresIO::delimiterAllele ) ;
  std::string token = CodominanceRuleWithouSpaces.substr( 0 , pos ) ;
  int allele1 = std::stoi( token ) ;


}

