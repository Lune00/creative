Getting started with awk p 25

awk 'pattern {action}' , les simples quotes disent que c'est pas a interpreter en shell mais a donner a l'interpreteur awk

on cherche la chaine 'li' dans le fichier, si trouve affiche la ligne
awk '/li/ {print $0}' filename
equivalant
awk '/li/ {print } filename

Les / / indiquent que li est le motif que l'on cherche (expression reguliere)
Dans une commande awk, le pattern ou l'action peut etre omise mais pas les deux !
Si le pattern est omis, l'action est appliquee sur chaque ligne. Si l'action est omise, l'action par defaut est d'afficher toutes les lignes qui correspondent au pattern. Donc alternativement on aurait pu ecrire

awk '/li/' filename

Affiche toutes les lignes qui depassent 80 caracteres
awk 'length($0) > 80 ' filename

Affiche la longueur de la ligne la plus longue de l'input

awk '{if(length($0)>max) max = length($0)} END {print max}' filename
Le code associe a END s execute une fois que toute l'input filename a ete lue
Le code associe a BEGIN s exexute avant que l'input soit lue (si pas d'input a utiliser)

Affiche toutes les lignes qui ont AU MOINS UN CHAMP
awk 'NF > 0' filneame

NF Number of Fields, si champ separes. Pratique pour supprimer les lignes vides d'un fichier
awk 'NF > 0' filneame > newfilename

Petit essai perso

awk 'BEGIN{x=0} NF==0 {x=x+1;} END {print "Nombre de lignes vides dans le fichier: "x}' data.txt

Affiche le nombre de lignes d'un fichier

awk ‘END{ print NR}' filename

Affiche les lignes paires d'un fichier

awk 'NR % 2 ==0' filaneme

The awk utility reads the input  les one line at a time. For each line, awk tries the patterns of each rule. If several patterns match, then several actions execute in the order in which they appear in the awk program. If no patterns match, then no actions run.

STOP p26
