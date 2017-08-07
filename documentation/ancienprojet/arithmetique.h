#ifndef ARITH000
#define ARITH000

#include<stdio.h>
#include<cstdlib>
#include<ctime>

class CALCULUS
{


private:



public:
        
CALCULUS();
~CALCULUS();
        
double unifRand(); 
double unifRand(int a,int b);
double gaussianDOUBLE(float moyenne,float sigma);
int gaussianINT(float moyenne,float sigma);
int unifRandInt(int a,int b);
int RANDOM();

};
#endif