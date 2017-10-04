#!/bin/bash

clear

source libconfig.sh

#Ce script se charge d'ajouter a la librairie les mots en attente (synonymes/related)
if [ ! -s "$waitlib" ];then
  echo "Aucun mot en attente pour le moment."
  exit
fi
#On recupere tous les mots dans un tableau
while read -r mot || [[ -n "$mot" ]] 
do
  mots+=($mot)
done < "$waitlib"

#Process chaque mot
echo "liste des mots à ajouter:"

for mot in "${mots[@]}"
do
  echo "Le mot en attente est ${green}$mot${reset}"
  echo -e "Voulez-vous traiter le mot - $mot - (${green}Y${reset}/n)? (x pour quitter) "
    while read -n 1 next && [ "$next" != y ] && [ "$next" != n ] && [ "$next" != "" ] && [ "$next" != "x" ];do
      echo "Tapez y ou n."
    done

    if [ "$next" == n ];then
      echo ""
      continue
    elif [ "$next" == x ]; then
      echo ""
      break
    fi

    clear

  #On le traite:
  line=$(gawk -v var="$mot" '{if($1==var)a[n++]=$0} END{for(i in a) {printf "%s%s", a[i],(i!=(n-1)?"_":"")}}' "$lib")

  IFS="_" read -r -a arr_lines <<< "$line" 
  echo "Nombre d'occurences du mot ${green}$mot${reset} dans $lib: ${bold}${#arr_lines[@]}${reset}"

  #Process occurences in $lib
  for occurence in "${arr_lines[@]}"
  do
    line="$occurence"
    #On a 13 champs en tout
    phonetique=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $2}')
    lemme=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $3}')
    grammar=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $4}')
    genre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $5}') #masculin,feminin
    accord=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $6}') #singulier,pluriels
    infover=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $11}') #mode,temps,personne pour verbe!
    nsyll=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $24}') 

    #Check doublon: mot + grammar deja dans $lib

    check_doublons_in_formatedlib "$mot" "$grammar"

    if [ "$?" == 1 ];then
      #Si doublon on supprime $mot de la liste de mots en attente
      linetodel=$(awk -v pattern="$mot" '$1==pattern{print NR}' $waitlib)
      sed -i "${linetodel}d" $waitlib
      echo "L'entrée ${yellow}$mot ${reset}a été supprimée de la liste."
      break
    fi

    #Entree disponible:
    echo ""
    printf "${yellow}Mot:${green}%-20s${reset}\n" "$mot"
    echo "Phonetique: $phonetique"
    echo "Classe gramm: $grammar"
    echo "Genre: $genre"
    echo "Nombre: $accord"
    echo "Infover: $infover"
    echo "Nsyllabes: $nsyll"

    echo -e "Voulez-vous ajouter - $mot - (${green}Y${reset}/n)? "
    while read -n 1 next && [ "$next" != y ] && [ "$next" != n ] && [ "$next" != "" ];do
      echo "Tapez y ou n."
    done
    echo""

    #On passe a l'occurence suivante si on veut
    if [ "$next" == n ];then
      continue
    fi

    #Ajout a la librairie
    freg=""
    registres=()
    regt=""
    while [ "$regt" != ${#registres[@]} ]; do 
      echo -e "* Donnez un ou plusieurs ${bold}registres${reset}: "
      echo "(${registre_table[@]})"
      echo ""
      read -a registres
      regt=$(check_registre "${registres[@]}")
    done
    for i in ${registres[*]}
    do
      freg+=$i";" 
    done 
    freg="${freg%?}"
    if [ -z $freg ];then freg=neutre ; fi

    #synonymes
    synonymes=()
    fsyn=""
    echo "* Donnez des ${bold}synonymes${reset} du mot ${green}$mot${reset}:"
    read -a synonymes
    for i in ${synonymes[*]}
    do
      fsyn+=$i";" 
    done 
    fsyn="${fsyn%?}" 

    #Related
    related=()
    frel=""
    echo "* Donnez des ${bold}mots associés ${reset}au mot ${green}$mot${reset}:"
    read -a related
    for i in ${related[*]}
    do 
      frel+=$i";"
    done
    frel="${frel%?}"

    #Theme
    theme=()
    ftheme=""
    echo "* Donnez un ou plusieurs ${bold}thèmes${reset} associés au mot ${green}$mot${reset}:"
    read -a theme
    #Format related
    for i in ${theme[*]}
    do 
      ftheme+=$i";"
    done
    ftheme="${ftheme%?}"

    affiche_resume "$mot" "$lemme" "$phonetique" "$grammar" "$infover" "$accord" "$genre" "$nsyll" "$freg" "$fsyn" "$frel" "$ftheme" 

    format_sortie "$mot" "$lemme" "$phonetique" "$grammar" "$infover" "$accord" "$genre" "$nsyll" "$freg" "$fsyn" "$frel" "$ftheme" 

    #Suppresion de waitlib
    sed -i "/$mot/d" $waitlib

    #On l'enregistre dans fichier de sortie
    echo -e "$sortie" >> $formatedlib
    echo "Le mot ${green}${bold}$mot${reset} a ete ajouté a la base de données."


  done
  #Continuer au mot suivant ou quitter
  echo -e "Voulez-vous ajouter un autre mot (${green}Y${reset}/n)? "
  while read -n 1 quitter && [ "$quitter" != y ] && [ "$quitter" != n ] && [ "$quitter" != "" ];do
    echo "Tapez y ou n."
  done

  if [ "$quitter" = n ];then
    break
  fi

done
clear

