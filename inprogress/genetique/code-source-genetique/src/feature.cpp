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

//CodominanceRule refers to the string defining codominance coefficient between two alleles
// ex : "1-3=0.8" : alleles 1 and 3, coefficient 0.8 such that alleles 1 dominates by 0.8 allele 3
void Feature::loadPairAllelesCoefficient( const std::vector<std::string>& vectorCodominanceRules ) {

  for (unsigned int i = 0 ; i != vectorCodominanceRules.size() ; i ++ ) {

    std::string CodominanceRule = vectorCodominanceRules[ i ] ;
    std::string CodominanceRuleWithouSpaces  = featuresIO::removeWhiteSpacesFromString( CodominanceRule ) ;

    //Check the Rule (correct expression)
    if( ! checkRegexForCodominanceRule( CodominanceRuleWithouSpaces ) )  {

      //Throw exception : 
      ostringstream oss ;
      oss << "Feature : " << this->label() << " has one or several invalid 'codRule' syntax "<<endl ;
      throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
      return ;
    }
    else {
      //Split string into two int (alleles) and a double(continuous) / int(discrete) 
      //We pass from codRules to codCoeff_
      Feature::pairAllelesCoefficient pAC = splitCodominanceRuleIntoPairAllelesCoefficient ( CodominanceRuleWithouSpaces ) ; 
      //Store into set
      addToSetPairAllelesCoefficientRecursive( pAC ) ;
    }

  }

}

void Feature::addToSetPairAllelesCoefficientRecursive( Feature::pairAllelesCoefficient pAC ) {

  //add to the set also (a,a) and (b,b) with default coeff 1
  pairAllelesCoefficient pACFirst ( pAC.pairAlleles_.first ) ;
  pairAllelesCoefficient pACSecond ( pAC.pairAlleles_.second ) ;

  setPairAllelesCoefficient_.insert( pACFirst ) ;
  setPairAllelesCoefficient_.insert( pACSecond ) ;
  setPairAllelesCoefficient_.insert( pAC ) ; 
}


  //TODO
  // If feature is Discrete : random codominance coefficients are either 0 or 1 (integer) OR probability !!!
  // If feature is Continuous : random codominance coefficients are between 0 and 1 (floating)
void Feature::buildDefaultPairAllelesCoefficient() {

  switch ( this->nature() ) {
    case Feature::D : 
      cout << "Feature '"<< this->label()<< "' codominance coefficients are set according to default parameters\n";
      break ;
    case Feature::C : 
      cout << "Feature '"<< this->label()<< "' codominance coefficients are set according to default parameters\n";
      break ;
    case Feature::Undefined : 
      cout<< "Undefined\n" ;
  }
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
Feature::pairAllelesCoefficient Feature::splitCodominanceRuleIntoPairAllelesCoefficient( const std::string & CodominanceRuleWithouSpaces ) {

  size_t pos = 0 ;
  string RuleToBeSplit = CodominanceRuleWithouSpaces ;
  
  //Get allele1 (int)
  pos = RuleToBeSplit.find( featuresIO::delimiterAllele ) ;
  std::string token = RuleToBeSplit.substr( 0 , pos ) ;
  int allele1 = std::stoi( token ) ;

  RuleToBeSplit = RuleToBeSplit.substr( pos + featuresIO::delimiterAllele.length() ) ;

  //Get allele2 (int)
  pos = RuleToBeSplit.find( featuresIO::delimiterCoefficient ) ;
  token = RuleToBeSplit.substr( 0 , pos ) ;
  int allele2 = std::stoi( token ) ;

  //Get coefficient (int/double depending on Nature of the Feature)
  RuleToBeSplit = RuleToBeSplit.substr( pos + featuresIO::delimiterCoefficient.length() ) ;
  std::string stringCoefficient = RuleToBeSplit ; 

  switch( this->nature() ){
    case C : 
      return pairAllelesCoefficient(allele1, allele2, std::stod( stringCoefficient ), 0 ) ; 
    case D :
      return pairAllelesCoefficient(allele1, allele2, 0. , std::stoi( stringCoefficient ) ) ; 
      //TODO DESIGN: if we put a double coefficient stating for the probability of an allele dominating the other
      //For the moment we assume it is always 1 ex : '3-2=3' -> 3 dominates. But we could have '3-2=0.5' -> 3 dominates hwith a probability 0.5. We need further test....
  }

}


//TODO
//Here we have a collection of syntaxcially correct alCo.  We then need to check the logical aspects: 
//Check that each int (allele id) match alleles stored in alleles_ 
//Check that every combination have been covered : 

//TODO: rename checkSetPairAllelesCoefficientConsistency
void Feature::checkPairAllelesCoeffcientConsistency() {


}

void Feature::checkPairAllelesCoeffcientCompletness() {


}

//Just use for debug : 
void Feature::debugPrintToStandardOutput() {

  cout << label_ << endl ;
  cout << "nature : " <<enumToString( nature_ ) << endl ;
  cout << "number of genes : " <<numGenes_ << endl ;
  cout << "alleles : " ;
  for(unsigned int i = 0 ; i != alleles_.size() ; i++){ 
  cout << alleles_[i] << " ";
  }
  cout <<endl ;

  cout << setPairAllelesCoefficient_.size() << " rules : " << endl ;
  std::unordered_set<pairAllelesCoefficient, pairAllelesCoefficientHasher >::const_iterator it = setPairAllelesCoefficient_.begin() ;
  while(it != setPairAllelesCoefficient_.end() ){
    cout << "allele " << it->pairAlleles_.first << " allele " << it->pairAlleles_.second << " coeff " ;
    if( nature_ == D ) cout << it->dominantAllele_ ;
    else cout << it->coeffCodominance_ ;
  cout << "\n" ; 
    it++;
  }
  cout << "\n\n" ; 

}
