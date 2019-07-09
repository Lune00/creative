#include<iostream>
#include<string>
#include<algorithm>
#include<regex>



// REGEX I need : pour regle de codominance : match entier-entier=double (peu importe format)
//
using namespace std;

//Envoie tous les caracteres non 'espace' au debut string et tous les whitespace a la fin
//end_pos pointe sur le premier caractere espace.
//On efface inplace les caracteres vides placés a la fin
std::string removeWhiteSpacesFromString(std::string string) {

  std::string::iterator end_pos = std::remove( string.begin() , string.end() , ' ') ;
  string.erase( end_pos , string.end() ) ;
  return string ;
}

void removeWhiteSpacesFromStringDemo() {

  const std::string string_original = " 3 - 4 = 0.5 " ;
  std::string string = string_original ;
  cout << "String before : " << string << " Size = " << string.size() << endl ;
  string = removeWhiteSpacesFromString( string_original ) ;
  cout << "String after : " << string << " Size = " << string.size() << endl ;

}


bool isNumber(const std::string & s){
  //return std::regex_match(s, std::regex("[(-|+)|][0-9]+"));
  return std::regex_match( s, std::regex( ( "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?" ) ) );
}

// Split / Parse 
void splitParseDemo() {

  // allele1-allele2=coefficient de la forme int-int=double
  int allele1 ;
  int allele2 ;
  double coefficient ;
  const std::string string_original = " 3 - 4 = 0.5 " ;

  std::string string = string_original ; 
  const std::string delimiter_allele = "-" ;
  const std::string delimiter_coeff = "=" ;

  size_t pos = 0 ;

  string = removeWhiteSpacesFromString( string ) ;

  pos = string.find( delimiter_allele ) ;

  std::string token = string.substr( 0 , pos ) ;

  if( pos != std::string::npos ) 
    cout << "Allele found : " << token << " in " << string << endl ;

  //Conversion from string to int : 
  if ( isNumber( token ) ) 
    allele1 = std::stoi( token ) ;

  //Remove begining of string
  string = string.substr( pos + delimiter_allele.length() ) ; 

  //Next item to find :
  pos =  string.find( delimiter_coeff ) ;

  token = string.substr( 0 , pos ) ;

  if( pos != std::string::npos ) 
    cout << "Allele found : " << token << " in " << string << endl ;

  if ( isNumber( token ) ) 
    allele2 = std::stoi( token ) ;

  string = string.substr ( pos + delimiter_coeff.length() ) ;

  cout << "s " << string << endl ;

  if( isNumber( string ) )
    coefficient = stod( string ) ;

  cout<< "Alleles : " << allele1 << " and " << allele2 << " - coefficient : " << coefficient << endl ;
}


int main() {

  cout << "Split / Parse strings " << endl ;

  splitParseDemo() ;

  return 0 ;
}
