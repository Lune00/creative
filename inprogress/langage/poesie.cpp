//PAGE 212 Procedural Generation in Game Design
//Essaye un generateur de poesie de deux lignes

//Faire une base de donnees avec categories par syllable et lier des synonymes
//Structure
// mot phonetique lemme(base du mot) genre nbsyllables registre synonymes

//Le lemme permet d'accorder? bilbiotheque renvoie la forme plurielle, elle la cherche dans une base de donnees...
//Avec ca + bibliotheque.cpp on peut deja faire pas mal de choses

//ex baleine balEn baleine 2 N(eutre) cetace,"geant des mers" 4
//   geant 2 E(epique) immense
//   cetace N 3

//Recuperer la derniere phoneme
//Donner un titre " Nager avec la grande baleine" (apres on peut generer des titres qui genereront des poemes)
//On donne un theme : epique, melancolique, joyeux et on va collecter des mots synonymes appartenant a cette categorie
//Ensuite on a une base de phrase a trous predefinies: "Avec des _____ aussi ___ que ____" et ces phrases demandent d'appeler
//un ajdectif, un verbe, ou un nom
//Chaque ligne est appelée en fonction de la précédente pour avoir une logique (reflechir a ce point)
//On preset les styles de rymes aabb, abab, etc...

//Ca peut etre bien marrant a tester, ca a pas l'air trop compliqu


//1er objectif: donner un code phonetique decomposer un mot en ses differents phonemes
//ex; Qu'importe ___nom___, Qurimporte ___nom___, Et que ___nom___ soit ___adjectif___
