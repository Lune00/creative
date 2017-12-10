#ifndef hpp_ARCHIVISTE_hpp
#define hpp_ARCHIVISTE_hpp

#include"Adjectif.hpp"
#include"Verbe.hpp"
#include"NomC.hpp"

#include<fstream>
#include<iostream>

//Archiviste est la classe qui sert d'interface entre le programme et la librairie formatée de mots
//C'est elle qui lit la librairie, parse les entrees, et cree la bibliotheque utilisée dans le programme
//C'est la classe Config quoi
class Archiviste{


  private:
    //Chemin d'acces a la librairie
    std::string mylibrary_;
    //Listes de mots stockées apres lecture:
    std::vector<Adjectif> adjectifs_;
    std::vector<NomC> nomsC_;
    std::vector<Verbe> verbes_;

  public:
    Archiviste();
    ~Archiviste();
    void importLibrary();
    void afficher() const;
    void addEntry(const std::vector<string>&);
    //Parse a string into a vec according to a delimiter
    std::vector<std::string> parseEntry(std::string toparse, std::string delimiter);

};



#endif
