#include"config.h"
#include"feature.h"
#include"gene.h"
#include"rng.h"
#include<sstream>

using namespace std ; 
using namespace configRules ;

Feature::Feature() {
}


void Feature::print_debug( ) {

  std::cerr << "Label : " << label_ << std::endl ;
  std::cerr << "Nature : " << geneticParameters::enumToString( nature_ ) << std::endl ; 
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

void Feature::setNature( std::string stringNature ) {

  geneticParameters::Nature nature = geneticParameters::stringToEnum( stringNature ) ;

  if ( nature == geneticParameters::Nature::Undefined ) {
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
  //Store in increasing order :
  sort(alleles_.begin() , alleles_.end() ) ;
  allelesDefinedByUser_ = true ;
}

//alleles_ filled sorted in increasing order
void Feature::setAllelesDefault( ) {
  alleles_.clear() ;
  for ( int j = 0 ; j != geneticParameters::geneSize ; j++ ) {
    alleles_.push_back( j ) ;
  }
  allelesDefinedByUser_ = false ;
}

//Different split according to nature (different syntaxes for the rules)
Rule Feature::splitStringRuleIntoRule(const std::string& stringRuleWithouSpaces ) {

      switch( nature_ ) {
	case geneticParameters::Nature::C :
	  return splitStringRuleIntoRuleContinuous( stringRuleWithouSpaces ) ;

	case geneticParameters::Nature::D :
	  return splitStringRuleIntoRuleDiscrete( stringRuleWithouSpaces ) ;

	case geneticParameters::Nature::Undefined :
	  return Rule( false ) ;
      }
}

Rule Feature::splitStringRuleIntoRuleDiscrete( const std::string& stringRuleWithouSpaces ) {

  std::size_t pos = 0 ;
  string RuleToBeSplit = stringRuleWithouSpaces ;

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

  //There is a flag indicating probability? 
  std::size_t foundFlag = RuleToBeSplit.find( featuresIO::flagProbability ) ;

  //In the case of absence of flag
  if( foundFlag == std::string::npos ) {
    int dominant_allele = std::stoi( RuleToBeSplit ) ;
    //Check that in syntax a-b=c c is equal to a or b
    if( dominant_allele != allele1 && dominant_allele != allele2 ) return Rule( allele1, allele2 , false ) ; 
    if( dominant_allele == allele1 && allele1 < allele2 ) return Rule( allele1, allele2 , 1. ) ; 
    else if( dominant_allele == allele1 && allele1 > allele2 ) return Rule( allele2, allele1 , 0. ) ;
    else if( dominant_allele == allele2 && allele1 < allele2 ) return Rule( allele1, allele2 , 0. ) ;
    else if( dominant_allele == allele2 && allele1 > allele2 ) return Rule( allele2, allele1 , 1. ) ;

  }
  else {
    std::string domination = RuleToBeSplit.substr( RuleToBeSplit.find( featuresIO::flagProbability ) + 1 ) ;
    return Rule( allele1 , allele2 , std::stod( domination ) ) ;
  }
}

//This function is called after Regex Check on the rule provided by the user. So we KNOW that the rule
//is SYNTAXICALLY correct (type, number) and we can process it without any further tests
Rule Feature::splitStringRuleIntoRuleContinuous( const std::string & stringRuleWithouSpaces ) {

  size_t pos = 0 ;
  string RuleToBeSplit = stringRuleWithouSpaces ;

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

  double domination = std::stod( stringCoefficient ) ;

  //Constructor of Rule puts automatically 
  return Rule ( allele1, allele2 , domination ) ;

}

//Loop over Rules. Call loadRule for each rule if regex syntax is valid 
void Feature::loadRules( const std::vector<std::string>& vectorCodominanceRules ) {

  for (unsigned int i = 0 ; i != vectorCodominanceRules.size() ; i ++ ) {

    std::string stringRule = vectorCodominanceRules[ i ] ;
    std::string stringRuleWithouSpaces  = featuresIO::removeWhiteSpacesFromString( stringRule ) ;
    //Check the Rule Syntax
    if( ! checkRegexForRule( stringRuleWithouSpaces ) )  {
      ostringstream oss ;
      oss << "Feature : " << this->label() << " has one or several invalid 'codRule' syntax "<<endl ;
      throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
      return ;
    }
    else 
      loadRule( stringRuleWithouSpaces ) ;
  }
}


//Load a rule : check validity and add to Rules. If not valid, throw exception
void Feature::loadRule(const std::string& stringRuleWithouSpaces ) {

      Rule rule = splitStringRuleIntoRule( stringRuleWithouSpaces ) ;
      addToRules ( rule ) ;
}

//Check the Rule expression read from user file, check Regex depending on the nature of the feature
bool Feature::checkRegexForRule( const std::string& stringRule ) {

  switch ( this->nature() ) { 
    case geneticParameters::Nature::C : 
      //Regex for Continuous Feature : check that arguments are integer and double < 1.0 (ex : 1-2=0.5)
      if( std::regex_match ( stringRule , std::regex(featuresIO::regexContinuousFeature)) ) 
	return true ;
      else
	return false; 
      //Regex for Discrete Feature : check that arguments are integer and integer (ex : 1-2=2 , 2 dominates 1)
      //or 1-2=p0.5
    case geneticParameters::Nature::D : 
      if( std::regex_match ( stringRule , std::regex(featuresIO::regexDiscreteFeatureBothSyntaxes)) )
	return true ;
      else
	return false; 
    case geneticParameters::Nature::Undefined :
      return false ;
  }
}

//Check if a Rule is valid : alleles of the pair exisy in the alleles_ vec and 0<domination<1
bool Feature::isRuleValid(const Rule& rule ) {

  if( !rule.isCorrect_ ) return false ; 

  int allele1 = rule.pairAlleles_.first ;
  int allele2 = rule.pairAlleles_.second ;

  bool allele1Found = false ;
  bool allele2Found = false ;

  std::vector<int>::const_iterator it = std::find( alleles_.begin(), alleles_.end() , allele1 ) ;
  if( it != alleles_.end() ) allele1Found = true ; 
  it = std::find( alleles_.begin(), alleles_.end() , allele2 ) ;
  if( it != alleles_.end() ) allele2Found = true ; 

  //Check that domination is between 0. and 1.
  bool dominationIsValid = ( rule.domination_ >= 0. ) && ( rule.domination_ <= 1. ) ;

  return ( allele1Found && allele2Found && dominationIsValid ) ;

}

//Add Rule to setOfRules_ if rule is valid. Add automatically identical alleles pair with domination 1.
void Feature::addToRules( Rule rule ) {

  if ( isRuleValid ( rule ) )  {
    //add to the set also (a,a) and (b,b) with default domination 1
    Rule first_first ( rule.pairAlleles_.first ) ;
    Rule second_second ( rule.pairAlleles_.second ) ;

    setOfRules_.insert( first_first ) ;
    setOfRules_.insert( second_second ) ;
    setOfRules_.insert( rule ) ; 
    return ;
  }

  else {
    //Throw exception : 
    ostringstream oss ;
    oss << "Feature : " << this->label() << " has invalid rule. Rule : " ;
    oss << rule.pairAlleles_.first << "-"<< rule.pairAlleles_.second ;
    throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
    return ;
  }  
}

//Not be redo properly with two distinct enums later
void Feature::buildRules( configRules::buildRulesOption option ) {

  cout << "Feature '"<< this->label()<< "' -rules generated -option : "<<configRules::enumToString( option )<< "\n";

  switch ( option ) {
    case configRules::Random : 
      buildRandomRules( ) ;
      break ;

    case configRules::IncreaseGradual : 
      buildIncreaseRules( option ) ;
      break ;
    case configRules::IncreaseStrict : 
      buildIncreaseRules( option ) ;
      break ;

    case configRules::DecreaseGradual : 
      buildDecreaseRules( option ) ;
      break ;

    case configRules::DecreaseStrict : 
      buildDecreaseRules( option ) ;
      break ;

    case configRules::Undefined : 
      break;

    default :
      return ;
  }
  return ;
}

void Feature::buildRandomRules( ) {

  for( size_t i = 0 ; i != alleles_.size() ; i++ ) {
    for( size_t j = i ; j!= alleles_.size() ; j++ ) {

      //Identity relation : manage case of one allele in alleles_
      if( alleles_[ i ] == alleles_[ j ] ) {
	Rule rule(alleles_[ i ] , alleles_[ j ] , 1. ) ;
	addToRules( rule ) ;
      }
      else {

	double domination ;

	if( nature() == geneticParameters::Nature::D ) 
	  domination = rng::unif_rand_int( 0 , 1 );
	else
	  domination = rng::unif_rand_double( 0 , 1 );

	Rule rule(alleles_[ i ] , alleles_[ j ] , domination ) ;
	addToRules( rule ) ;
      }

    }
  }
  return ;
}

//Higher alleles dominate lower ones
void Feature::buildIncreaseRules( configRules::buildRulesOption option ) {

  const double epsilon = 1e-5 ;

  for( size_t i = 0 ; i != alleles_.size() ; i++ ) {

    double domination = 0 ;

    for( size_t j = alleles_.size() - 1 ; j!= 0 ; j-- ) {

      //Identity relation
      if( alleles_[ i ] == alleles_[ j ] ) {
	Rule rule(alleles_[ i ] , alleles_[ j ] , 1. ) ;
	addToRules( rule ) ;
      }
      else{
	  if (domination < epsilon ) domination = 0. ;
	  Rule rule( alleles_[ i ] , alleles_ [ j ] , domination ) ;
	  addToRules( rule ) ;
	  if( option == configRules::buildRulesOption::IncreaseGradual ) 
	    domination += 0.1 ;
	}
      }
  }
  return ;
}
//Lower alleles dominate higher ones
void Feature::buildDecreaseRules(configRules::buildRulesOption option ) {

  for( size_t i = 0 ; i != alleles_.size() ; i++ ) {

    double domination = 1. ;

    for( size_t j = alleles_.size() - 1 ; j!= 0 ; j-- ) {

      //Identity relation
      if( alleles_[ i ] == alleles_[ j ] ) {
	Rule rule (alleles_[ i ] , alleles_[ j ] , 1. ) ;
	addToRules( rule ) ;
      }
      else{
	  Rule rule( alleles_[ i ] , alleles_ [ j ] , domination ) ;
	  addToRules( rule ) ;

	  if( option == configRules::buildRulesOption::IncreaseGradual ) 
	    domination -= 0.1 ;
      }
    }
  }
  return ;
}


bool Feature::isSetOfRulesComplete() {

  if ( alleles_.size() == 0 ) return false ;

  for( size_t i = 0 ; i != alleles_.size()  ; i++ ) {
    for( size_t j = i   ; j != alleles_.size()  ; j++ ) {
      //Find (i,j) if not return false ;
      Rule rule( alleles_[ i ]  , alleles_[ j ] , true ) ;
      if( !findInSetOfRules( rule ) ) {
	cerr << alleles_[i] << "-"<<alleles_[ j ] <<" not found !" << endl ;
	return false ;
      }
    }
  }
  return true ;
}

//Check completness and consistency of the rules , throw exception if not
void Feature::checkRulesCompletness() {
  if ( !isSetOfRulesComplete() ) {
    ostringstream oss ;
    oss << "Feature : " << this->label() << " has incomplete set of Rules "<<endl ;
    throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
    return ;
  }
}

bool Feature::findInSetOfRules(const Rule& rule ) {
  if ( setOfRules_.find( rule ) != setOfRules_.end() ) return true ;
  else return false;
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

  cout << setOfRules_.size() << " rules : " << endl ;
  std::unordered_set<Rule, RuleHasher >::const_iterator it = setOfRules_.begin() ;
  while(it != setOfRules_.end() ){
    //Do not print a-a relation (for clarity)
    if( it->pairAlleles_.first != it->pairAlleles_.second ){
      cout << "allele " << it->pairAlleles_.first << " allele " << it->pairAlleles_.second << " coeff : " << it->domination_ ;
      cout << "\n" ; 
    }
    it++;
  }
  cout << "\n\n" ; 

}
