#!/usr/local/bin/bash

source libconfig.sh

echo ""
printf "%50s" "{ ${red}Rapport${green} sur${yellow}${bold} $formatedlib${reset} }"
echo ""

#Nombre de noms

#Themes : nombre et occurences

themes=$(awk 'BEGIN{FS="\t";} {print $12}' $formatedlib)
themes=$(gawk 'BEGIN{ RS=";|\\s" ; ORS=" "}{ print $0}' <<< $themes)
declare -A asar
for i in ${themes}; do asar[$i]=$(( ${asar[$i]}+1 )); done
themes=$(gawk 'BEGIN{RS="\\s" ; ORS=" "}{ if(var[$0]==0){var[$0]+=1; print $0}}' <<< "$themes")
echo -e "\n.Liste des thèmes présents:\n"
for i in ${themes}
do
  printf "${yellow}%-10s${reset}\tNombre d'entrées: ${green}%3s${reset}\n" "$i" "${asar[$i]}"
done

echo ""

#Maj related et synonmes demandant une entree
rsyn=$(awk 'BEGIN{FS="\t";} {print $10 $11}' $formatedlib)
rsyn=$(gawk 'BEGIN{ RS=";|\\s" ; ORS=" "}{ print $0}' <<< $rsyn)
rsyn=$(gawk 'BEGIN{RS="\\s" ; ORS=" "}{if(var[$0]==0){var[$0]+=1; print $0}}' <<< "$rsyn")

awaiters=""
#On check si ils ont deja une entree dans la librairie
#Si non, on ajoute a awaiters
for i in ${rsyn}
do
  found=$(awk -v var="$i" '$1==var' "$formatedlib")
  if [ -z "$found" ]; then
    awaiters+=$i" "
  fi
done

awaiters="${awaiters%?}"
#On ecrit les awaiters dans un fichier awaiters.txt
for i in ${awaiters}
do
  #Check si pas deja present dans le fichier
  found=$(awk -v var="$i" '$1==var' "$waitlib")
  if [ -z $found ]; then
    add+=$i" "
    echo "$i" >> $waitlib
  fi
done
add="${add%?}"
echo -e ".Mots en attente ajoutés (${green}${#add}${reset}):\n$add"


#On fera un script manage_awaiters.sh qui se chargera de lire ce fichier awaiters.txt, de verifier si entre temps ils n'ont pas été ajoutés (soit manuellement soit a l'aide de la base), de les traiter jusqu'a ce que la liste soit vide
