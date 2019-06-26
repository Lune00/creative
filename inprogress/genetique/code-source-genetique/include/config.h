// Geres les fichiers de config (les features, environement, parametre genetiques etc...) utilises pour initialiser la librairie genetique
#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<iostream>
#include<libconfig.h++>

using namespace libconfig ;
using  std::cerr;
using  std::cout;
using  std::endl;

//To be moved elsewhere another time:
//Return factorial of the positive integer n
int fact(int n) ;

// Manage Input/Output from configuration files
namespace cfgIO{
  const std::string featuresFile = "features.glib" ;
  bool checkNumberOfCombinations(int nalleles, int nCotableRules);
  bool readFeaturesFile();
}
#endif
