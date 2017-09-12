#!/usr/local/bin/bash

source libconfig.sh

echo ""
echo " -- ${red}Rapport${green} sur${yellow}${bold} $formatedlib ${reset} --"

#Nombre de noms

#Themes : nombre et occurences

themes=$(awk 'BEGIN{FS="\t";} {print $12}' $formatedlib)
themes=$(gawk 'BEGIN{ RS=";|\\s" ; ORS=" "}{ print $0}' <<< $themes)
declare -A asar
for i in ${themes}; do asar[$i]=$(( ${asar[$i]}+1 )); done
themes=$(gawk 'BEGIN{RS="\\s" ; ORS=" "}{ if(var[$0]==0){var[$0]+=1; print $0}}' <<< "$themes")
echo -e "\nListe des thèmes présents:\n"
for i in ${themes}
do
  printf "${yellow}%-10s${reset}\tNombre d'entrées: ${green}%3s${reset}\n" "$i" "${asar[$i]}"
done


#Mots synonymes/related qui n'ont pas encore d'entree
#on les sortira dans un fichier awaiters.txt
#On fera un script manage_awaiters.sh qui se chargera de lire ce fichier awaiters.txt, de verifier si entre temps ils n'ont pas été ajoutés (soit manuellement soit a l'aide de la base), de les traiter jusqu'a ce que la liste soit vide
