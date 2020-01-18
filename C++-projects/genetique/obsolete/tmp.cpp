#include<libconfig.h++>
#include<iostream>
#include<vector>
#include<string>

//ajouter l'emplacement de la librairie au linker : g++ main.cpp -lconfig++ 
using namespace std;
using namespace libconfig;

//Return factorial of the positive integer n :
int fact(int n){
  if( n < 0 ) cerr << "integer n is not positive " << endl;
  if (n == 0 || n == 1) return 1 ;
  else return n * fact (n-1);
}

// Number of combinaisons: k = 2 always and n = nalleles
bool checkNumberOfCombinations(int nalleles, int nCotableRules){
  int ncombinations = fact(nalleles) / ( fact( nalleles - 2 ) * 2) ;
//  cerr << "number of combinations = "<< ncombinations << endl;
  return (ncombinations == nCotableRules);
}

int main(){

  cout << "Test de libconfig " << endl;

  Config cfg ;

  //Verifie que le fichier existe et pas d'erreur de syntaxe:
  try{
    cfg.readFile("configuration.cfg");
  }
  catch(const FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file " << std::endl;
    return(EXIT_FAILURE);
  }
  catch(const ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return(EXIT_FAILURE);
  }

  const Setting& root = cfg.getRoot() ;

  //Verifie que le group 'features' existe bien:

  try{
    const Setting &features = root["features"];
    int count = features.getLength();
    cout << "Number of features in the lib : " << count << endl ;  

    //On parse chaque feature:
    for(int i = 0 ; i  != count ; i++){

      //Par default les alleles sont gérées de maniere automatique
      bool manual_alleles = false ;
      //Deplaces temporairement pour etre global et accessible a table:
      //Store alleles:
      std::vector<int> alleles_list;
      //Store alleles codominance rules:
      std::vector<std::string> codominance_rules_string;

      const Setting& feature = features[i];

      //Name : REQUIS
      try{
	string name = feature.lookup("name");
	cout << "Name : "<< name <<endl;
      }
      catch(const SettingNotFoundException &nfex)
      {
	cerr << "No 'name' setting in configuration file." << endl;
	return(EXIT_FAILURE);
      }

      //Nature : REQUIS
      try{
	string nature = feature.lookup("nature");
	cout << "Nature : "<< nature <<endl;
      }
      catch(const SettingNotFoundException &nfex)
      {
	cerr << "No 'nature' setting in configuration file." << endl;
	return(EXIT_FAILURE);
      }

      //NGENES : REQUIS
      try{
	int nGenes = feature.lookup("nGenes");
	cout << "nGenes : "<< nGenes <<endl;
      }
      catch(const SettingNotFoundException &nfex)
      {
	cerr << "No 'nGenes' setting in configuration file for feature " << i + 1 <<"!" << endl;
	return(EXIT_FAILURE);
      }

      //ALLELES : OPTIONAL (default behavior embeded)
      try{
	//const Setting &alleles = features[i]["alleles"];
	const Setting &alleles = feature.lookup("alleles");


	//Parse alleles :
	for(int j = 0 ; j != alleles.getLength() ; j++){
	  alleles_list.push_back(alleles[j]);
	}
	manual_alleles = true ;
      }
      catch(const SettingNotFoundException &nfex)
      {
	cerr << "Default allele parameters applied for this feature" <<endl;
	manual_alleles = false ;
      }
      //TABLE : OPTIONAL (default behavior embeded)
      if( manual_alleles ) {

	try{
	  const Setting &cotable = feature.lookup("cotable");
	  //Parse alleles :
	  for(int j = 0 ; j != cotable.getLength() ; j++){
	    codominance_rules_string.push_back(cotable[j]);
	    cout << codominance_rules_string[j] <<" ";
	  }
	  cout<<endl;
	  //Check that number of alleles and number of combination (number of rules) are coherent (check on the completness of coefficient later)
	  if(!checkNumberOfCombinations(alleles_list.size(), codominance_rules_string.size()))
	  {
	    cerr << "The number of combinaisons do not match the number of alleles defined " << endl;
	    return(EXIT_FAILURE);
	  }

	}
	catch(const SettingNotFoundException &nfex){
	  cerr << "No 'cotable' setting in configuration file for feature " << i + 1 <<" whereas user-defined alleles have been provided. Fix. " << endl;
	  return(EXIT_FAILURE);
	}
      }
    } // for loop ends

  } // parse features end

  catch(const SettingNotFoundException &nfex)
  {
    cerr << " No 'features' group in configuration file " << endl;
  }

  return 0 ; 

}
