#ifndef H_adjectif_H
#define H_adjectif_H

#include"Mot.hpp"
#include<string>

using namespace std;

class Adjectif: public Mot{
  private:
    char genre_;
    char nombre_;

  public:
    Adjectif(std::string,std::string,int,char,char);
    ~Adjectif();
    virtual int nature() const { return ADJ_; }
};


#endif
