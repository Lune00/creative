#ifndef H_collectionneur_H
#define H_collectionneur_H

#include<vector>
#include"Collection.hpp"

class Archiviste;

//Collectionneur demande des mots a archiviste pour creer des collecions de mots
//Collection de mots par: theme, phonetique etc... possible grâce à a la bibliotheque

class Collectionneur{

  private:
    Archiviste * archiviste_;
    std::vector<Collection> collections_;

  public:
    Collectionneur(){};
    ~Collectionneur(){};
    void plugtoArchiviste(Archiviste& a) { archiviste_ = &a;}

    bool isCollection(const std::string& name) const;
    void addCollection(const std::string& name);
    void addToCollection(Mot& m);
    void addToCollection(Mot& m, const std::string name);

    void print() const;
    Collection askCollection(const std::string name) const;

};


#endif
