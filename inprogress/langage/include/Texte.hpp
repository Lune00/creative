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
//Elle devra renvoyer le template sous une forme canonique interpretable par la compositeur
//qui se chargera de remplir les trous. Mais il faut d'abord reflechir a la forme des templates...

#define _aphorisme_ 0

//Lit un template

//Transforme une entre _mot_ en objet mot a appeler

//Mettre au point syntaxe de balises

//Regle 0: Un templates est compris entre {}

//Regle 1: les balises _mot_ indiquent qu'on doit y glisser un mot

class Texte{

  private:

    std::string ftemplates_;
    std::vector<std::string> template_;

  public:
    Texte();
    ~Texte();
    //TMP: apres gestion des differents templates
    void loadTemplates();
    void readTemplate(std::ifstream&);
    void parseTemplate();
    void printTemplate() const;
    std::vector<Mot*> askwords() const;

};

#endif
