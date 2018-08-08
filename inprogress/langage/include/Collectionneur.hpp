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

    bool exist_collection_by_name(const std::string& name) const;
    void create_collection(const std::string& name);

    void put_word_into_collections_by_theme(Mot& m);
    void add_word_to_collection(Mot& m, const std::string name);

    void print() const;
    Collection return_collection_by_name(const std::string name) const;

};


#endif
