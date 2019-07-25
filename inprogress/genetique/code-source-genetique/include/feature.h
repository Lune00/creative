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
  //TODO: change it. Change the name to Relation or Rule (maybe Rule to be consistent with the rest of the code)
  struct pairAllelesCoefficient {

    std::pair < int , int > pairAlleles_ ;

    //TODO : change to domination : how allele1 dominate allele 2
    //In the case of Continuous : contribution of each allele in % to the continuous value of the feature
    //In the case of Discrete : probability of expression.
    //Interface in the config file. For discrete we could say : '3-6=3' dominance = 1. (3 domine 6 always), or '3-6=p0.5' 3 domine 6 with a probability 0.5. We should add the p to avoid complication in the regex verification (or not)
    //We should also have a check that in the first expression the domination operant (3 here) is found on the left operand.
    double domination_ ; 

    //Alleles always stored as a pair(a,b) with a <= b
    pairAllelesCoefficient(int allele1, int allele2, double domination ) :
      domination_ ( domination )  
    {
      if ( allele1 < allele2 ) 
	pairAlleles_ = std::make_pair( allele1 , allele2 ) ;
      else
	pairAlleles_ = std::make_pair( allele2 , allele1 ) ;
    }

    //Works properly whatever the nature 
    pairAllelesCoefficient( int allele ) {
      pairAlleles_ = std::make_pair ( allele, allele ) ;
      domination_ = 1. ;
    }

    //Equality 
    bool operator==(const pairAllelesCoefficient& p ) const {
      if ( pairAlleles_ == p.pairAlleles_ )
	return true;
      else
	return false;
    }

  };
  //Hash function baserd on pairAlleles_
  struct pairAllelesCoefficientHasher
  {
    size_t
      operator()(const pairAllelesCoefficient & obj) const
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

  void loadPairAllelesCoefficient(const std::vector< std::string > & vectorCodominanceRules ) ;
  void addToSetPairAllelesCoefficientRecursive(Feature::pairAllelesCoefficient ) ;
  void buildDefaultPairAllelesCoefficient( ) ;

  //'CodominanceRule' refers to the string given by the user in the config file
  pairAllelesCoefficient splitCodominanceRuleIntoPairAllelesCoefficient( const std::string& ) ;
  bool checkRegexForCodominanceRule(const std::string& ) ;

  void checkPairAllelesCoeffcientConsistency( ) ;
  void checkPairAllelesCoeffcientCompletness( ) ;

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

  //Codominance factor between each Allele of the same gene
  std::unordered_set< pairAllelesCoefficient, pairAllelesCoefficientHasher >  setPairAllelesCoefficient_ ;
} ;


#endif // FEATURE_H
