#include<cstdlib>
#include<cstdlib>
#include<stdio.h>
#include<ctime>
#include <cmath>
#include "arithmetique.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



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
 
 int CALCULUS::RANDOM()
 {
	return floor(rand());
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
 
 // renvoie un float distribué selon loi normale de moyenne moyenne et de variance variance:
 double CALCULUS::gaussianDOUBLE(float moyenne,float variance)
 {
	float u1=unifRand();
	float u2=unifRand();
	
	return (moyenne+variance*sqrt(-2*log(u1))*cos(2*M_PI*u2));
	
 }

int CALCULUS::gaussianINT(float moyenne,float variance)
{
	float u1=unifRand();
	float u2=unifRand();
	
	return round((moyenne+variance*sqrt(-2*log(u1))*cos(2*M_PI*u2)));
	
}