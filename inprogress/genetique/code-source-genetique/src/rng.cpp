#include "rng.h"

namespace rng{

  unsigned long seed = 1;
  std::default_random_engine generateur_(seed);

  double unif_rand_double(int a, int b){
    std::uniform_real_distribution<double> distribution(a,b);
    return distribution(generateur_);
  }

  int unif_rand_int(int a, int b){
    std::uniform_int_distribution<int> distribution(a,b);
    return distribution(generateur_);
  }

}

