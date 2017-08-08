//PAGE 212 Procedural Generation in Game Design
//Essaye un generateur de poesie de deux lignes
//Faire une base de donnees avec categories par syllable et lier des synonymes

// MOT NSYLLABES REGISTRE ,SYNONYMES (stocker aussi dans la base de donnes, si expression mettre entre "")
//ex baleine 2 N(eutre) cetace,"geant des mers" 4
//   geant 2 E(epique) immense
//   cetace N 3

//Recuperer la derniere syllabe (ryme)
//Donner un titre " Nager avec la grande baleine" (apres on peut generer des titres qui genereront des poemes)
//On donne un theme : epique, melancolique, joyeux et on va collecter des mots synonymes appartenant a cette categorie
//Ensuite on a une base de phrase a trous predefinies: "Avec des _____ aussi ___ que ____" et ces phrases demandent d'appeler
//un ajdectif, un verbe, ou un nom
//Chaque ligne est appelée en fonction de la précédente pour avoir une logique (reflechir a ce point)
//On preset les styles de rymes aabb, abab, etc...
//Ca peut etre bien marrant a tester, ca a pas l'air trop compliqu
