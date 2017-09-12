#!/usr/local/bin/bash


themes="poésie littérature;voyage poésie"

#---- Decouper un string en element de tableau selon differents delimiteurs
#Donner le nombre d'éléments differents/identiques

#on suppose qu'on recupere l'ensemble des champs sous cette forme

#IFS permet de specifier l'ensemble des caracteres delimiteurs, ici le ";" et " "
# <<< sert a envoyer de la sortie standard le contenu de string (un pipe poserait probleme car dans un subshell... a mediter)
IFS='; ' read -r -a array <<< "$themes" 

for i in ${array[@]}
do
  echo $i
done

echo "Nombre de thèmes: ${#array[@]}"

#---- Effacer les doublons dans un chaine de caracteres avec awk
doublons="poire pomme chocolat poire poirepoire pomme"
#EN specifiant " "comme RS, on traite chaque parametre de la chaine comme un record(ligne) et non comme un field(colonne)
sansdoublons=$(gawk 'BEGIN{RS="\\s" ; ORS=" "}{ if(var[$0]==0){var[$0]+=1; print $0}}' <<< "$doublons")
#echo "$doublons"
#echo "$sansdoublons"

echo " ****   UPDATE **** "
echo " "

#Sans passer par un tableau
#Formater
themes="poésie littérature;voyage poésie"
echo "Input : $themes"
themes=$(gawk 'BEGIN{ RS=";|\\s" ; ORS=" "}{ print $0}' <<< $themes)

#Occurences avec une array associative -A
declare -A asar
for i in ${themes}
  do
      asar[$i]=$(( ${asar[$i]}+1)) #arithmetic expasion, transforme string en expression numerique
done
#Remove doublons:
themes=$(gawk 'BEGIN{RS="\\s" ; ORS=" "}{ if(var[$0]==0){var[$0]+=1; print $0}}' <<< "$themes")
#Print occurences par theme
echo "Output:"
for i in ${themes}
do
  echo "Theme : $i  - Nombre d'entrées: ${asar[$i]} " 
done

