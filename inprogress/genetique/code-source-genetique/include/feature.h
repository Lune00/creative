// Feature (phenotype)
#ifndef FEATURE_H
#define FEATURE_H

#include<string>
#include<vector>
#include<iostream>
#include<map>

class Feature {


  typedef std::pair < int , int > pair_alleles ;

  struct allelesAndCoeff {
    int alleleA ;
    int alleleB ;
    double coeffCodominance ;
  };


  public :

    Feature() ;

    // D : Discrete (ex : color of the eyes) C : Continuous value of the trait (ex : height)
    enum Nature { D = 0 , C = 1, Undefined = 2 } ;
    Nature stringToEnum( std::string ) ; 
    std::string enumToString( Nature ) ; 

    void print_debug() ;
    std::string name() const { return name_ ; }
    Nature nature() const { return nature_ ; }

    // Initialisition from the features file configuration
    void setName( std::string name ) { name_ = name ; }
    void setNature( std::string nature ) { nature_ = stringToEnum( nature ) ; }
    void setNumGenes( int nGenes ) ;
    void setAllelesDefinedManually( bool ) ;
    void setAlleles( const std::vector<int>& ) ;
    void setAllelesDefault( ) ;
    void setCodominanceCoefficients(const std::vector< std::string > & ) ;
    allelesAndCoeff splitCodominanceRuleIntoAllelesAndCoeff( const std::string& ) ;
    bool checkRegexForCodominanceRule(const std::string& ) ;

  private :

    //Alleles parameters : number and value for each nu
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

    //Codominance factor between each Allele of the same gene
    std::map< pair_alleles , double  >  codominanceCoefficient_ ;
} ;


#endif // FEATURE_H
