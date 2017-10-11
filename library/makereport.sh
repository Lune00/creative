#!/usr/local/bin/bash


#Quand on construit les awaiters on doit supprimer de la liste ceux deja présent dans la base
#On ne va pas rajouter toutes les formes conjuquées des verbes
#Que l'infinif! Et Premier groupe en priorité
#On se servira du programme de conjugaison pour conjugueur apres
#Sinon ce sera interminable!!

source libconfig.sh

echo ""
printf "%50s" "{ ${red}Rapport${green} sur${yellow}${bold} $formatedlib${reset} }"
echo ""

#Nombre de noms

#Themes : nombre et occurences
#A classer par proportion (%)

#Nombres d'entrees en NOM et ADJ
echo ".Occurences par classe grammaticale:"
echo ""
awk 'BEGIN{FS="\t"}/NOM/{b=b+1} END{print "Nombre de NOM: " b}' $formatedlib
awk 'BEGIN{FS="\t"}/ADJ/{a=a+1} END{print "Nomnbe de ADJ: "a}' $formatedlib
awk 'BEGIN{FS="\t"}/VER/{a=a+1} END{print "Nomnbe de VER: "a}' $formatedlib

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
#Un probleme sur la séparation etnre rsyn et related!!!
rsyn=$(awk 'BEGIN{FS="\t";} {print $10";"$11}' $formatedlib)
rsyn=$(gawk 'BEGIN{ RS=";|\\s" ; ORS=" "}{ print $0}' <<< $rsyn)
#rsyn=$(gawk 'BEGIN{ RS=";|\\s" ; ORS=" "}{ print $0}' <<< $rsyn)
rsyn=$(gawk 'BEGIN{RS="\\s" ; ORS=" "}{if(var[$0]==0){var[$0]+=1; print $0}}' <<< "$rsyn")

awaiters=""

#Il faut supprimer les doublons en regardant s'ils ont déja une entrée

#On check si ils ont deja une entree dans la librairie
#Les doublons seront geres par addawaiters et non ici
for i in ${rsyn}
do
  found=$(awk -v var="$i" '$1==var' "$formatedlib")
  if [ -z "$found" ]; then
    awaiters+=$i" "
  fi
done

awaiters="${awaiters%?}"
#On ecrit les awaiters de la librairie formatee dans un fichier awaiters.txt
> "$waitlib"
for i in ${awaiters}
do
  #Check si pas deja present dans le fichier
  found=$(awk -v var="$i" '$1==var' "$waitlib")
  if [ -z "$found" ]; then
    add+=$i" "
    echo "$i" >> $waitlib
  fi
done
add="${add%?}"
#Nombre de mots:
add_table=($add)
#echo -e ".Mots en attente ajoutés depuis le dernier rapport (${green}${#add_table[@]}${reset}):\n$add"

echo ""
#enattente=(`cat "$waitlib"`)
#echo -e "${green}.Liste des mots en attente:${reset}\n ${enattente[@]}"
