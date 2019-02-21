#include<random>

namespace rng{
 
  extern unsigned long seed ;
  extern std::default_random_engine generateur_;
  double unif_rand_double(int,int);
  int unif_rand_int(int,int);


}
