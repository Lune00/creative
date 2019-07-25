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


//Different split according to nature (different syntaxes for the rules)
Feature::Rule Feature::splitStringRuleIntoRule(const std::string& stringRuleWithouSpaces ) {

      switch( nature_ ) {
	case C :
	  return splitStringRuleIntoRuleContinuous( stringRuleWithouSpaces ) ;

	case D :
	  return splitStringRuleIntoRuleDiscrete( stringRuleWithouSpaces ) ;

	case Undefined :
	  return Rule( false ) ;
      }
}

Feature::Rule Feature::splitStringRuleIntoRuleDiscrete( const std::string& stringRuleWithouSpaces ) {

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

    cout << "p flag " << endl ;

  }
}

//This function is called after Regex Check on the rule provided by the user. So we KNOW that the rule
//is SYNTAXICALLY correct (type, number) and we can process it without any further tests
Feature::Rule Feature::splitStringRuleIntoRuleContinuous( const std::string & stringRuleWithouSpaces ) {

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

void Feature::loadRules( const std::vector<std::string>& vectorCodominanceRules ) {

  for (unsigned int i = 0 ; i != vectorCodominanceRules.size() ; i ++ ) {

    std::string stringRule = vectorCodominanceRules[ i ] ;
    std::string stringRuleWithouSpaces  = featuresIO::removeWhiteSpacesFromString( stringRule ) ;

    //Check the Rule Syntax
    if( ! checkRegexForRule( stringRuleWithouSpaces ) )  {

      //Throw exception : 
      ostringstream oss ;
      oss << "Feature : " << this->label() << " has one or several invalid 'codRule' syntax "<<endl ;
      throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
      return ;
    }

    else {

      Feature::Rule tmp_rule = splitStringRuleIntoRule( stringRuleWithouSpaces ) ;

      //Check the Rule Validity (intern logic): alleles exist in the vec alleles_ , domination belongs to [0 :1]
      if ( isRuleValid ( tmp_rule ) ) {
	Feature::Rule rule = buildRule ( tmp_rule ) ;
	//Store
	addToRules( rule ) ;
      }
      else {
	//Throw exception : 
	ostringstream oss ;
	oss << "Feature : " << this->label() << " has invalid rule. Rule : " ;
	oss << tmp_rule.pairAlleles_.first << "-"<< tmp_rule.pairAlleles_.second ;
	throw exceptions::MyStandardException( exceptions::writeMsg( oss ) , __LINE__ ) ;
	return ;

      } } }

}

bool Feature::isRuleValid(const Feature::Rule& rule ) {

  if( !rule.isCorrect_ ) return false ; 
  //Check that pairAlleles_ contain alleles in the vector alleles_
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

void Feature::addToRules( Feature::Rule rule ) {

  //add to the set also (a,a) and (b,b) with default domination 1
  Rule first_first ( rule.pairAlleles_.first ) ;
  Rule second_second ( rule.pairAlleles_.second ) ;

  setOfRules_.insert( first_first ) ;
  setOfRules_.insert( second_second ) ;
  setOfRules_.insert( rule ) ; 
}


//TODO
// If feature is Discrete : random codominance coefficients are either 0 or 1 (integer) OR probability !!!
// If feature is Continuous : random codominance coefficients are between 0 and 1 (floating)
void Feature::buildDefaultRules() {

  switch ( this->nature() ) {
    case Feature::D : 
      cout << "Feature '"<< this->label()<< "' Rules are set according to default parameters\n";
      break ;
    case Feature::C : 
      cout << "Feature '"<< this->label()<< "' Rules are set according to default parameters\n";
      break ;
    case Feature::Undefined : 
      cout<< "Undefined\n" ;
  }
}

//Check the Rule expression read from user file, check Regex depending on the nature of the feature
bool Feature::checkRegexForRule( const std::string& stringRule ) {

  switch ( this->nature() ) { 
    case C : 
      //Regex for Continuous Feature : check that arguments are integer and double < 1.0 (ex : 1-2=0.5)
      if( std::regex_match ( stringRule , std::regex(featuresIO::regexContinuousFeature)) ) 
	return true ;
      else
	return false; 
      //Regex for Discrete Feature : check that arguments are integer and integer (ex : 1-2=2 , 2 dominates 1)
    case D : 

      if( std::regex_match ( stringRule , std::regex(featuresIO::regexDiscreteFeatureBothSyntaxes)) )
	return true ;
      else
	return false; 
    case Undefined :
      return false ;
  }
}



//Handle the discrete Case with syntaxes
Feature::Rule Feature::buildRule( const Rule& rule ) {

  switch( this->nature() ){

    //Nothing to do
    case C : 
      return rule ; 

    case D :
      return rule ;

    case Undefined : 
      //Never reached, exception throwed before in setNature
      return Rule( false ) ; 
      ;
  }

}

//TODO
//Here we have a collection of syntaxcially correct alCo.  We then need to check the logical aspects: 
//Check that each int (allele id) match alleles stored in alleles_ 
//Check that every combination have been covered : 

//TODO: rename checkSetPairAllelesCoefficientConsistency
void Feature::checkRulesConsistency() {


}

void Feature::checkRulesCompletness() {


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
    cout << "allele " << it->pairAlleles_.first << " allele " << it->pairAlleles_.second << " coeff " << it->domination_ ;
    cout << "\n" ; 
    it++;
  }
  cout << "\n\n" ; 

}
