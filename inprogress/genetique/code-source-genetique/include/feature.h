// Feature (phenotype)
#ifndef FEATURE_H
#define FEATURE_H

#include<string>
#include<vector>
#include<iostream>
#include<unordered_set>
#include <boost/functional/hash.hpp>

class Feature {

  //For managing codominance rules between alleles
  struct Rule {

    std::pair < int , int > pairAlleles_ ;

    double domination_ ; 

    //If the rule is for a discrete feature with a probability expression of the gene = presence of 'p' in the rule
    //ex : 1-0=p0.5 -> allele 1 dominates allele 0 with probability p = 0.5 
    //ex : 0-1=p1 or 0-1=p1. -> allele 0 dominates allele 1 with p=1. (always)
    //ex : 0-1=1 -> allele 1 dominates allele 0 with p=1. (always)
    //
    //False by default
    bool discreteCaseWithProbability_ ;

    //Alleles always stored as a pair(a,b) with a <= b
    Rule(int allele1, int allele2, double domination, bool discreteCaseWithProbability = false ) :
      domination_ ( domination ), discreteCaseWithProbability_(discreteCaseWithProbability)
    {
      if ( allele1 < allele2 ) 
	pairAlleles_ = std::make_pair( allele1 , allele2 ) ;
      else
	pairAlleles_ = std::make_pair( allele2 , allele1 ) ;
    }

    //Works properly whatever the nature 
    Rule( int allele ) {
      pairAlleles_ = std::make_pair ( allele, allele ) ;
      domination_ = 1. ;
      discreteCaseWithProbability_ = false ;
    }

    //Equality 
    bool operator==(const Rule& r ) const {
      if ( pairAlleles_ == r.pairAlleles_ )
	return true;
      else
	return false;
    }

  };
  //Hash function baserd on pairAlleles_
  struct RuleHasher
  {
    size_t
      operator()(const Rule & obj) const
      {
	return boost::hash<std::pair <int, int > >()(obj.pairAlleles_) ;
      }
  };

  public :

  Feature() ;

  // D : Discrete (ex : color of the eyes) C : Continuous value of the trait (ex : height)
  enum Nature { D = 0 , C = 1, Undefined = 2 } ;
  Nature stringToEnum( std::string ) ; 
  std::string enumToString( Nature ) ; 

  void print_debug() ;
  std::string name() const { return name_ ; }
  std::string label() const { return label_ ; }
  Nature nature() const { return nature_ ; }

  // Initialisition from the features file configuration
  void setLabel( std::string label) { label_ = label ; }
  void setName( std::string name ) { name_ = name ; }
  void setNature( std::string nature ) ;  
  void setNumGenes( int nGenes ) ;
  void setAllelesDefinedManually( bool ) ;
  void setAlleles( const std::vector<int>& ) ;
  void setAllelesDefault( ) ;

  void loadRules(const std::vector< std::string > & vectorCodominanceRules ) ;
  void addToRules(Feature::Rule ) ;
  void buildDefaultRules( ) ;

  //'CodominanceRule' refers to the string given by the user in the config file
  Rule splitStringRuleIntoRule( const std::string& ) ;
  bool checkRegexForRule(const std::string& ) ;

  void checkRulesConsistency( ) ;
  void checkRulesCompletness( ) ;

  //Debug:
  void debugPrintToStandardOutput() ;

  private :

  //Alleles parameters : number and value for each nu
  std::string label_ ;
  std::string name_ ;
  Nature nature_  ;

  bool AllelesDefinedManually_ ; 

  //Raw phenotype value lies in the interval [-1:1]. Have to be rescaled my min/max to represents a quantity with a meaning and unit.
  double value_ ;

  //The value of the phenotype must lie in the interval [valueMin_:valueMax_]
  double valueMin_ ;
  double valueMax_ ;

  //Number of genes to code for the trait (by default 1 if nature_ = 0 )
  unsigned int numGenes_ ;

  //Alleles available for each gene
  std::vector<int> alleles_ ;
  //CodominanceRule for each alleles (tmp struct)

  //Store Rules between each Allele of the same gene
  std::unordered_set< Rule, RuleHasher >  setOfRules_ ;
} ;


#endif // FEATURE_H
