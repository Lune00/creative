Ici nous avons commence a definir des mots en fonction de leur type:
 des verbes qui peuvent se conjuguer
 des accors qui peuvent s'accorder (noms communs et adjectifs)

->Un verbe est donne. Automatiquement il est classe dans un groupe et les regles s'accordent en fnction du groupe.
Il faut completer la liste des verbes irreguliers (verbe.hpp)
->Un accord (nom propre seulement pour le moment) est accorde en nombre (avec traitement des exceptions a completer).
->Adjectif : TODO
Les structures de base sont posees. Il faut completer les temps et les conjugaisons du 3e groupe.
Il reste a faire les adjectifs egalement et leur accord, regarder les cas pariculiers.
Ce travail de fond necessite d'etre poursuivi car les structures sont incompletes.
On peut commencer par categoriser les verbes et les rentrer dans une base de donnees. Le but est de produire du texte de maniere procedurale en fonction de parametres de contexte etc... De produire des descriptions.

Cependant, la structure est bonne et prometeuse. Il serait interessant de commenceer a faire une base de donnees des verbes par exemple.
Quelles actions devrivent ils?
On peut imaginer qu a des mots soient attribues un score refletant la distinction (education). Meme si c'est davantage dans les strctures grammaticales meme qu'elle se fait sentir. On pourrait classer des mots, des expressions dans des registres : soutenu, argot, commun.

->Pour les bases de donnees:
	- des verbes: les categoriser par action avec des balises, rentrer la forme infinitive + score (0 , 1 , 2) pour distinguer soutenu, argot, commun et un score d'intensite (0 faible, 1 normal, 2 fort) pour ponderer l'intensite de l'action... Reflechir a d'autres nuances. On cherche des criteres pour appeler des mots dans des categories.
	- les noms communs : forme singuliere + genre (f ou m) (vraiment utile? avoir) + score distinction + ???? ( ceci pourra etre complete par la suite) 

Commencer par essayer de produire une phrase procedurale de description en fonction de differents parametres.
Exemple : Arrivee devant une grande foret. Quelqun' de non sensible dira "Cette satanée foret s'etend a perte de vue." Quelquen de plus sensible dira "Cette belle foret s'etend a perte de vue".


Laisser tomber l'indice d'intensite. Gardons le plus simple possible. Il vaut mieux pour le moment completer avec des complements circonstanciels (avec force, a vive allure etc...)
Note sur la descpition : La description d'un personnage doit etre compose d'une description physique de base ( visage, carrure, specificites) , de son origine sociale et geographique, de ses liens, son caractere, ses passions et son metier, et de quelques anecdotes, elements qui le rendent uniques. Ex : Il avale ses repas". La conjugaison (au lieu de la forme infinitive) rend plus reel et permet de faire des variations dans le passe Ex: Il a longtemps eu peur du noir. Ex: Il adore marcher en foret. Ex: Il n'a jamais aimé la mer.
Il ne faut pas trop en dire. Par exemple, s'il a un gros nez on le mentionnera car ca permet de le distinguer, sinon non. Sinon on se perd dans une myriade de details qui rendent impossible la representation. Ex: Il rigole a haute voix. Ex: Elle ne s'attache jamais les cheveux, elle les prefere libres. Ex: Cet homme a un coeur de pierre, rien ne peut l'emouvoir.


--- Verbes: on essaye un systeme de balise. La lecture devra lire les balises et les stocker. Ensuite on pourra appeler un mot d'une liste de cette balise. Par exemple on peut faire un objet conteneur Categorie. Il a un nom, un vecteur de Verbe. On peut imaginer ensuite complexifier la liste en mettant des associations supplementaires, des sous categories. Pour cela il suffirait d'enrichir l'objet Verbe pour rajouter des infos.

