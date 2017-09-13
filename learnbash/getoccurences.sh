#!/usr/local/bin/bash

#Le but est de recuperer toutes les occurences dans un fichier, et de pouvoir les traiter une par une par l'utilisateur

echo "Hello"

#On a un fichier avec plusieurs occurences
echo -e "danse\tADJ\tbla" > occ.txt
echo -e "danse\tVER\tbla" >> occ.txt
echo -e "danser\tVER\tbla" >> occ.txt
echo -e "danse\tADV\tbla" >> occ.txt

#On stocke toutes les occurences il n'y a plus de separateur par defaut
#a=$(gawk '{if($1=="danse") print $0}' occ.txt)
#echo $a

#Ici les recors sont stockes dans un tableau. Pour l'output separator record on peut donc traiter facileemnt le cas du dernier element
#Chaque record est séparé par un ';' sauf le dernier
a=$(gawk '{if($1=="danse")a[n++]=$0} END{for(i in a) {printf "%s%s", a[i],(i!=(n-1)?";":"")}}' occ.txt)
echo $a
#Pour spliter les elements dans un tableau on peut changer IFS mais ca me plait pas trop (global)
#IFS=$';'
#for i in $a
#do
#  echo $i
#done
#unset IFS

#Aleternative: stocker dans un tableau en passant par read qui a son propre IFS
IFS=';' read -ra table <<< "$a"
echo "Nombre d'entrees: ${#table[@]}"
for i in "${table[@]}"
do
  echo $i
done
#OK ca marche


