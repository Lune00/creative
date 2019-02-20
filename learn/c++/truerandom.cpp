#include<iostream>
#include<random>

using namespace std;

int main(){

  int seed = 0 ;
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0,10);

  for(int i = 0 ; i < 10 ; i++){

    int a = distribution(generator); 
    cout<<a<<endl;

  }

  return 0;
}
