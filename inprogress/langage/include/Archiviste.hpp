#ifndef hpp_ARCHIVISTE_hpp
#define hpp_ARCHIVISTE_hpp

#include"Adjectif.hpp"
#include"Verbe.hpp"
#include"NomC.hpp"
#include"Langue.hpp"

#include<algorithm>
#include<fstream>
#include<iostream>
#include<random>


//Archiviste est la classe qui sert d'interface entre le programme et la librairie formatée de mots
//C'est elle qui lit la librairie, parse les entrees, et cree la bibliotheque utilisée dans le programme
//C'est la classe Config quoi

class Collectionneur;

class Archiviste{

  private:

    int seed_;
    //Chemin d'acces a la librairie
    std::string mylibrary_;
    //Listes de mots importés apres lecture:
    std::vector<Adjectif> adjectifs_;
    std::vector<NomC> nomsC_;
    std::vector<Verbe> verbes_;

    //Acces to Collectionneur
    Collectionneur * collectionneur_;

  public:

    Archiviste();
    ~Archiviste();
    //Run at initialisation: plug to Collectionneur
    void plugtoCollectionneur(Collectionneur&);

    //Called in constructor
    void importLibrary();
    void buildlinks();
    //Remove doublons if they exist in the links for each word
    void cleanlinks();
    
    void link(std::vector<std::string>&);
    //Called by link:
    void link_to_adj(Mot* const,std::vector<std::string>&,std::vector<std::string>&);
    void link_to_ver(Mot* const,std::vector<std::string>&,std::vector<std::string>&);
    void link_to_noC(Mot* const,std::vector<std::string>&,std::vector<std::string>&);

    //Built theme collections:
    void buildThemesCollections();

    void afficher() const;
    void addEntry(const std::vector<string>&);


    //Parse a string into a vec according to a delimiter
    std::vector<std::string> parseEntry(std::string toparse, const std::string delimiter);

    //Container sizes
    int getNadjectifs() const { return adjectifs_.size();}
    int getNnomsC() const { return nomsC_.size();}
    int getNverbes() const { return verbes_.size();}

    //Return a word (defined as mot and nature)
    //This pointer can be used to modify the word
    Mot * findword(const std::string&, const std::string&) ;

    Mot * findADJ(const std::string&);
    Mot * findNOMC(const std::string&);
    Mot * findVER(const std::string&);

    //Random word from entire library
    const Mot * randomword() const;
    //Return a random integer with value uniformly distributed between 0 and size, useful for random access in vector



    //TODO
    //To be moved to another class Random
    //only made for this (on aura un pointeur dessus) 
    int randomIndex(const int size) const;

};



#endif
