#include<cstdlib>
#include<cstdlib>
#include<stdio.h>
#include<ctime>
#include "arithmetique.h"

//ARITHMETIQUES-DISTRIBUTIONS UNIFORMES:
//NECESSITE BIBLIO #include<cstdlib>
// init: srand(static_cast<unsigned int>(time(0)));

using namespace std;

CALCULUS::CALCULUS()
{
        
   srand(static_cast<unsigned int>(time(0)));    
        
        
        
}

CALCULUS::~CALCULUS()
{
        
        
}


//renvoie un float entre 0 et 1
 double CALCULUS::unifRand()
 {
   return rand()/double(RAND_MAX);
 }
 // renvoie un float aléatoire uniforme entre a et b
 double CALCULUS::unifRand(int a,int b)
 {
   return unifRand()*(b-a)+a;
 }
 // renvoie un int aléatoire unif entre a et b
 int CALCULUS::unifRandInt(int a,int b)
 {
   return (a + (rand() % (b - a + 1)));
 } 

