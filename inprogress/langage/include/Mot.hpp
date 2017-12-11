#ifndef _hpp_Mot_hpp
#define _hpp_Mot_hpp

#include<iostream>
#include<string>
#include<vector>

#define NOMC_ 0
#define ADJ_  1
#define VER_  2

class Mot{

  //Private mais accessible aux classes filles
  protected:
    //base du mot: a voir si utilité par la suite
    //std::string lemme_;
    //le mot lui meme
    std::string mot_;
    //phonetique
    std::string phon_;
    //Nombre syllabes
    int nsyll_;
    //Synonymes:
    std::vector<Mot*> synonymes_;
    //Related:
    std::vector<Mot*> associés_;

  public:
    Mot(std::string, std::string, int);
    //Un destructeur est toujours virtuel
    virtual ~Mot();

    std::string getmot() const { return mot_;} 
    //Resolution dynamique: fonction virtuelle uniquement dans la declaration de la fonction
    virtual void affiche() const { std::cout<<"Le mot est "<<mot_;}
    //Methode virtuelle pure: la classe Mot est a present virtuelle
    virtual int nature() const = 0 ;

    std::string getlastphoneme() const { return std::string (1,phon_.back());}
    std::string getfirstletter() const { return std::string (1,mot_[0]);}

};

#endif
