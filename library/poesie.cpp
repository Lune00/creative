#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#define mylibrary "mylibrary.txt"

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
    Mot(string);
    ~Mot();
};

Mot::Mot(){};

Mot::Mot(string entree)
{

  cerr<<"Init mot"<<endl;



};

Mot::~Mot(){};


//class Librairie{
//  private:
//    std::vector<Mot> noms_;
//    std::vector<Mot> adjectifs_;
//    std::vector<Mot> verbes_;
//  public:
//    Librairie();
//    ~Librairie();
//};
//
//Librairie::Librairie(){};
//Librairie::~Librairie(){};


int main(){

  cout<<"Bonjour poésie."<<endl;
  std::vector<Mot> corpus;
  ifstream mylib(mylibrary);

  while(mylib){
    string entree;
    getline(mylib,entree);
    //Chaque entree (entree) de la librairie est contenue dans entree
    //Il faut maintenant la splitter pour en faire un mot, constructeur mot
    Mot mot = Mot(entree);
    corpus.push_back(mot);
  };
}
