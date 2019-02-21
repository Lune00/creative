#include<iostream>
#include"rng.h"

//Ca marche aussi, extern dit que c'est defini quelquepart
//nimporte ou (au linkage c'est verifie). Je peux le definir ici
//ou ailleurs dans le code (dans le rng.cpp ce qui parait mieux)

//Les variables doivent etre extern car sinon sans m'en rendre compte je la declare et la defini en meme temps (caché). en faisant des includes 2 fois ici et dans rng.cpp j'ai trois definitions de seed ce qui est interdit (une et une seule definition, multiples declarations mais qu'une definition)

//Je comprends le linkage externe comme quand le compilateur met tous les .o bout a bout et verifie que tout est bien defini une fois (resolution des liens). La compilation verifie que les fonctions existent (declaration) et le linkage que les definitions existent en un seul exemplaire.


//unsigned long rng::seed = 4 ;

int main(){

  using std::cout;
  using std::endl;
  using namespace rng;

  cout.precision(2);
  for(int i = 0 ; i< 10; i++){
    cout<<unif_rand_double(1,6)<<" " ; 

  }
  cout<<endl;

  return 0 ;

}
