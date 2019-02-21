#include"maison.h"

Maison::Maison(int a){ nombre_fenetres_ = a ;}
Maison::~Maison(){} 
int Maison::nombre_fenetres() const { return 2  * nombre_fenetres_ ; }
