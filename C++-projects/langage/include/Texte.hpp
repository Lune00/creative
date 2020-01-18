#ifndef H_TEXTE_H
#define H_TEXTE_H

#include<fstream>
#include<iostream>
#include<vector>

#include"Langue.hpp"
#include"Adjectif.hpp"
#include"Verbe.hpp"
#include"NomC.hpp"

//Cette classe lit les templates de texte ecrit a la main en interpretant leur grammaire

#define _aphorisme_ 0


//Lit un template

//Transforme une entre _mot_ en objet mot a appeler

//Regle 0: Un templates est compris entre {}

class Texte{

  private:

    //data file common for all templates
    static std::string ftemplates_;
    //tem:plate: mots utilisateur + balises
    std::vector<std::string> template_;
    //Texte final formaté
    std::string texte_;

  public:
    Texte();
    ~Texte();
    //TMP: apres gestion des differents templates
    void read_templates_datafile();
    void load_template(std::ifstream&);
    void fill_template();
    void print_template() const;
    std::vector<Mot*> askwords() const;

};

#endif
