#!/bin/bash

clear

source libconfig.sh

#Ce script se charge d'ajouter a la librairie les mots en attente (synonymes/related)

#On recupere tous les mots dans un tableau

while read -r mot || [[ -n "$mot" ]] 
do

  echo "Le mot qui attend est ${green}$mot${reset}"
  #Process
  #On le cherche dans la base

  line=$(gawk -v var="$mot" '{if($1==var)a[n++]=$0} END{for(i in a) {printf "%s%s", a[i],(i!=(n-1)?"_":"")}}' "$lib")

  #Il faut traiter le cas une ou plusieurs occurences
  #En esperant que '_' ne soit pas utilise par lexique...
  IFS="_" read -r -a arr_lines <<< "$line" 
  echo "Nombre d'occurences du mot ${green}$mot${reset} dans $lib: ${bold}${#arr_lines[@]}${reset}"
  for i in "${arr_lines[@]}"
  do
    line="$i"
    #On a 13 champs en tout
    phonetique=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $2}')
    lemme=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $3}')
    grammar=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $4}')
    genre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $5}') #masculin,feminin
    nombre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $6}') #singulier,pluriels
    infover=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $11}') #mode,temps,personne pour verbe!
    nsyll=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $24}') 

    #Entree disponible:
    echo ""
    printf "${yellow}Mot:${green}%-20s${reset}\n" "$mot"
    echo "Phonetique: $phonetique"
    echo "Classe gramm: $grammar"
    echo "Genre: $genre"
    echo "Nombre: $nombre"
    echo "Infover: $infover"
    echo "Nsyllabes: $nsyll"


    #Problem! Several nested read loops

    #echo -e "Voulez-vous ajouter - $mot - (${green}Y${reset}/n)? "
    #while read -n 1 next </dev/tyy && [ "$next" != y ] && [ "$next" != n ] && [ "$next" != "" ];do
    #  echo "Tapez y ou n."
    #done
    #echo""

    #Si on veut passer au suivant, on passe au suivant
    if [ "$next" == n ];then
      continue
    fi

  done

  echo -e "Voulez-vous ajouter un autre mot (${green}Y${reset}/n)? "
  #Nested read (direct from terminal)
  while read -n 1 quitter </dev/tty && [ "$quitter" != y ] && [ "$quitter" != n ] && [ "$quitter" != "" ];do
    echo "Tapez y ou n."
  done
  if [ "$quitter" = n ];then
    break
  fi
done < "$waitlib"

echo "Mise à jour terminée."



