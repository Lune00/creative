#ifndef H_adjectif_H
#define H_adjectif_H


#include<string>

using namespace std;

class Adjectif{
  private:
    string mot_;
  public:
    Adjectif(){mot_ ="";}
    Adjectif(string mot) : mot_(mot){} ;
    ~Adjectif(){};
    const string& getmot() const {return mot_;}
    string accorder(string article,char genre); // renvoie le bon accord en genre et nombre
};


#endif
