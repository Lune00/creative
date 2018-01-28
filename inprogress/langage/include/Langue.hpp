#ifndef H_LANGUE_H
#define H_LANGUE_H
#include<string>

//Ici seront stockees toutes constantes du langage(phonetique, voyelles, consonnes...)
//Ainsi que les regles pour les manipuler
//Seule la conjugaison est laisee a verbe ( y reflechir)


namespace phonetique{
  //Table phonetique
  const std::string phon_table[]={ "a","i","y","u","o","O","e","E","°","2","9","5","1","@","§","3","j","8","w","p","b","t","d","k","g","f","v","s","z","Z","m","n","N","I","R","x","G","S","l"};

}


namespace lettres{
  //Voyelles:
  const std::string voyelles[]= {"a","e","i","o","u","y"};
  const std::string Voyelles[]= {"A","E","I","O","U","Y"};

  //Consonnes:
  const std::string consonnes[]= {"z","r","t","p","q","s","d","f","g","h","j","k","l","m","w","x","v","b","n"};
  const std::string Consonnes[]= {"Z","R","T","P","Q","S","D","F","G","H","J","K","L","M","W","X","V","B","N"};

}

namespace articles{
//Voir en pratique le meilleur moyen de gerer l'elision
//Elements ranges : 0 masculin 1 feminin 2 pluriel 3 elisé (m/f)
const std::string definis[]= {"le","la","les","l'"};
const std::string indefinis[]= {"un","une","des"};
const std::string partitif[]= {"du","de la","de l'"};

}

namespace grammaire{

  //Les classes interpretables par le programme donnees dans le template
  const std::string classes[] = {"nom","verbe","adjectif","partitif","defini","indefini","CCT"};

}


#endif
