#include"maison.h"
#include<iostream>

int main() {

  Maison maison(3);

  std::cout<<"La maison a "<<maison.nombre_fenetres() <<" fenêtres."<<std::endl;

  return 0 ; 

}
