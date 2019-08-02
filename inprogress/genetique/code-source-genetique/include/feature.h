// Feature (phenotype)
#ifndef FEATURE_H
#define FEATURE_H

#include<string>
#include<vector>
#include<iostream>
#include<unordered_set>
#include <boost/functional/hash.hpp>
#include"config.h"

class Feature {

  public :

  Feature() ;


  std::string name() const { return name_ ; }
  std::string label() const { return label_ ; }
  geneticParameters::Nature nature() const { return nature_ ; }
  bool allelesDefinedByUser( ) const { return allelesDefinedByUser_ ; } ;

  // Initialisition from the features file configuration
  void setLabel( std::string label) { label_ = label ; }
  void setName( std::string name ) { name_ = name ; }
  void setNature( std::string nature ) ;  
  void setNumGenes( int nGenes ) ;
  void setAlleles( const std::vector<int>& ) ;
  void setAllelesDefault( ) ;

  //Default Rules when not defined by user 
  void buildRules(configRules::buildRulesOption ) ;
  void buildRandomRules( ) ;
  void buildIncreasingRules( ) ;
  void buildDecreasingRules( ) ;

  void loadRules(const std::vector< std::string > & vectorCodominanceRules ) ;
  void loadRule(const std::string & Rule ) ;
  void addToRules( configRules::Rule ) ;

  //Split string Rule (from file) into a struct temp Rule
  configRules::Rule splitStringRuleIntoRule( const std::string& ) ;
  configRules::Rule splitStringRuleIntoRuleContinuous( const std::string& ) ;
  configRules::Rule splitStringRuleIntoRuleDiscrete( const std::string& ) ;

  //Check the validity of a Rule
  bool isRuleValid( const configRules::Rule& ) ;
  //Check the syntax of a Rule (from file)
  bool checkRegexForRule(const std::string& ) ;

  //Check over the set of Rules
  void checkRulesCompletness( ) ; //throw exception if not
  bool isSetOfRulesComplete( ) ;

  bool findInSetOfRules( const configRules::Rule& ) ;

  //Debug:
  void debugPrintToStandardOutput() ;
  void print_debug() ;

  private :

  //label (abstract name, id in the config file. Different features can be built from the same abstract feature identified by its label)
  std::string label_ ;
  //name (real name in the program) 
  std::string name_ ;
  //nature (Discrete Or Continuous)
  geneticParameters::Nature nature_  ;

  //If alleles have been defined or not by the user (config file)
  bool allelesDefinedByUser_ ; 

  //Abstract phenotype value. Lies in the interval [-1:1].
  //Have to be rescaled my min/max to represents a quantity with a meaning and unit.
  double value_ ;

  //The value of the phenotype must lie in the interval [valueMin_:valueMax_]
  double valueMin_ ;
  double valueMax_ ;

  //Number of genes to code for the trait (by default 1 if nature_ = 0 )
  unsigned int numGenes_ ;

  //Alleles available for this feature for all its genes
  std::vector<int> alleles_ ;

  //Store Rules between each Allele for the same gene
  std::unordered_set< configRules::Rule, configRules::RuleHasher >  setOfRules_ ;
} ;


#endif // FEATURE_H
