#ifndef RNG_H
#define RNG_H
#include<random>


namespace rng{
  double unif_rand_double(int,int);
  int unif_rand_int(int,int);
  extern std::default_random_engine generateur_;
  extern unsigned long seed_ ;
}



#endif // RNG_H
