#include<random>
#include<iostream>

using namespace std;

class RandomGenerator{
  public:
    RandomGenerator();
    double unifRand();
    double unifRand(int,int);
    int unifRandInt(int,int);
  private:
  std::default_random_engine generator_;

};

RandomGenerator::RandomGenerator(){
  cout<<"Seed not init"<<endl;
  //init seed
}

double RandomGenerator::unifRand(){
  std::uniform_real_distribution<double> distribution(0.,1.);
  return distribution(generator_);
}
double RandomGenerator::unifRand(int a, int b){
  std::uniform_real_distribution<double> distribution(a,b);
  return distribution(generator_);
}
int RandomGenerator::unifRandInt(int a, int b){
  std::uniform_int_distribution<int> distribution(a,b);
  return distribution(generator_);
}

int main(){

  RandomGenerator rng;
  cout<<rng.unifRandInt(0,50)<<endl;
  return 0;
}
