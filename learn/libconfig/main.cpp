#include<libconfig.h++>
#include<iostream>
//ajouter l'emplacement de la librairie au linker : g++ main.cpp -lconfig++ 
using namespace std;
using namespace libconfig;

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

    for(int i = 0 ; i  != count ; i++){

      const Setting& feature = features[i];

      //On parse chaque feature:

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

    }

    //ALLELES : OPTIONAL (default behavior embeded)
    //TABLE : OPTIONAL (default behavior embeded)

  }

  catch(const SettingNotFoundException &nfex)
  {
    cerr << " No 'features' group in configuration file " << endl;
  }


  return 0 ; 

}
