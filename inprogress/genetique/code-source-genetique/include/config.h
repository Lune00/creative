// Geres les fichiers de config (les features, environement, parametre genetiques etc...) utilises pour initialiser la librairie genetique
#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<iostream>
#include<vector>
#include<libconfig.h++>

class Feature ;

using namespace libconfig ;
using  std::cerr ;
using  std::cout ;
using  std::endl ;

//To be moved elsewhere another time:
//Return factorial of the positive integer n
int fact( int n) ;

// Manage Input/Output of features configuration file
namespace featuresIO {

  const std::string featuresFile = "features.glib" ;
  //Features loaded from the file and in the genetic base
  extern std::vector<Feature*> features ;

  bool checkNumberOfCombinations( int numAlleles, int numCotableRules );
  bool loadFeatures() ;
  bool isFeaturesFilesAndCorrectSyntax() ;
  bool parseFeatures() ;
  void parseFeature( const Setting& ) ;

  //Read features settings 
  bool readName( const Setting&, Feature* feature ) ;
  bool readNature( const Setting&, Feature* feature ) ;
  bool readNumGenes( const Setting&, Feature* feature ) ;
}
#endif
