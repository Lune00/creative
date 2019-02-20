#include "rng.h"

using namespace std;

RandomGenerator::RandomGenerator(): generator_((std::random_device())()) 
{}

double RandomGenerator::unifRand(int a, int b){
  std::uniform_real_distribution<double> distribution(a,b);
  return distribution(generator_);
}
int RandomGenerator::unifRandInt(int a, int b){
  std::uniform_int_distribution<int> distribution(a,b);
  return distribution(generator_);
}

