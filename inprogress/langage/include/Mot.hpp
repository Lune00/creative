#ifndef _hpp_Mot_hpp
#define _hpp_Mot_hpp

#include<iostream>
#include<string>
#include<vector>

class Mot{

  //Private mais accessible aux classes filles
  protected:
    //base du mot
    std::string lemme_;
    //phonetique
    std::string phon_;
    //Nombre syllabes
    int nsyll_;

  public:
    Mot(std::string, std::string, int);
    //Un destructeur est toujours virtuel
    virtual ~Mot();

    std::string getlemme() const { return lemme_;} 
    //Resolution dynamique: fonction virtuelle uniquement dans la declaration de la fonction
    virtual void affiche() const { std::cout<<"Le lemme du mot est "<<lemme_;}
    //Methode virtuelle pure: la classe Mot est a present virtuelle
    virtual std::string nature() const = 0 ;

    std::string getlastphoneme() { return std::string (1,phon_.back());}
    std::string getfirstletter() { return std::string (1,lemme_[0]);}

};

#endif
