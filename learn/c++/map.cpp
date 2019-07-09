#include<iostream>
#include<fstream>
#include<math.h>
#include<map>

using namespace std;
 
int main(){
 
cout<<"Hello Map!"<<endl;

typedef std::pair<int,int> alleles_pair ;
std::map < std::pair <int,int> ,double > codcoeff ; 

//Insert :
codcoeff.insert ( std::make_pair ( std:: make_pair ( 1 , 2 ) , 0.5 ) ) ; 

//Access by key :

//Cette methode est particuliere, si la pair (1,2) n'existe pas elle sera cree et 
//ajoutée a la map avec maped value par default
cout <<  codcoeff[ std::make_pair ( 1 , 2 ) ] << endl ;
//Exemple: on recupere 0 en mapped value. A utiliser avec prudence. Pas cet effet en utilisant un iterator
cout <<  codcoeff[ std::make_pair ( 3 , 4 ) ] << " - Size of the map : " << codcoeff.size() << endl ;
//Uniqueness: map ne peut contenir qu'une unique key, l'element suivant n'est pas rajouté
cout <<  codcoeff[ std::make_pair ( 3 , 4 ) ] << " - Size of the map : " << codcoeff.size() << endl ;


std::map < std::pair < int , int > , double >::iterator it ;
it = codcoeff.find( make_pair( 1, 2 ) ) ;
if (it != codcoeff.end() ) cout << it->second << endl ;

cout << codcoeff.find ( std::make_pair ( 1 , 2 ) )->second << endl ;

//Using Dervied type alleles_pair
cout << codcoeff.find ( alleles_pair( 1 , 2 ) )->second << endl ;

}
