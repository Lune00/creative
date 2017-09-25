#include<iostream>
#include<string>
#include<vector>

#define library "mylib.txt"

using namespace std;

class Mot{

  private:

  string mot_;
  string lemme_;
  string phon_;
  string grammar_;
  string infover_;

  char genre_;
  char accord_;
  int nsyll_;

  std::vector<string> registre_;
  std::vector<string> syn_;
  std::vector<string> ass_;
  std::vector<string> themes_;

  public:
  Mot();
  ~Mot();
};

Mot::Mot(){};
Mot::~Mot(){};


class Librairie{

  private:
    std::vector<Mot> corpus_;
  public:
    Librairie();
    ~Librairie();
};

Librairie::Librairie(){};
Librairie::~Librairie(){};


int main(){

  cout<<"Bonjour poésie."<<endl;

}
