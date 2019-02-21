#ifndef RNG_H
#define RNG_H
#include<random>

class RandomGenerator{
  public:
    RandomGenerator();
    double unifRand(int,int);
    int unifRandInt(int,int);
  private:
  std::default_random_engine generator_;
};


#endif // RNG_H
