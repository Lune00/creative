#!/bin/bash

clear

source libconfig.sh
#Script permet de lire la base de donnees lexique, d'y chercher une entree particuliere et de l'ajouter a la base de donnees formatee.

#On lit tant que l'utilisateur le souhaite ou tant que le fichier lib n'est pas vide
#Ajouter possibilite de passer au mot suivant si celui choisi ne nous interesse pas (appuyer sur N )
while [ -z $uans ] || [ "$uans" != "x" ] && [ -s $lib ];do
  next=N
  while [ "$next" == "N" ]; do
    #On cherche un mot precis:
    line=""
    while [ -z "$line" ];do
      read -p "Quel mot voulez vous ajouter: " mot
      line=$(gawk -v var="$mot" '{if($1==var)a[n++]=$0} END{for(i in a) {printf "%s%s", a[i],(i!=(n-1)?"-":"")}}' "$lib")
    done
    clear
    #Il faut traiter le cas une ou plusieurs occurences
    IFS="-" read -r -a arr_lines <<< "$line" 
    echo "Nombre d'occurences du mot ${green}$mot${reset} dans $lib: ${bold}${#arr_lines[@]}${reset}"
    for i in "${arr_lines[@]}"
    do
      line=$i
      #On a 9 champs de base auquel on va rajouter : un registre / synonymes / related / themes
      #On a 13 champs en tout
      phonetique=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $2}')
      lemme=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $3}')
      grammar=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $4}')
      genre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $5}') #masculin,feminin
      nombre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $6}') #singulier,pluriels
      infover=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $11}') #mode,temps,personne pour verbe!
      nsyll=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $24}') 
      echo ""
      printf "%20s\n" "-"
      printf "${yellow}Mot:${green}%-20s${reset}\n" "$mot"
      echo "Phonetique: $phonetique"
      echo "Classe gramm: $grammar"
      echo "Genre: $genre"
      echo "Nombre: $nombre"
      echo "Infover: $infover"
      echo "Nsyllabes: $nsyll"
      printf "%20s\n" "-"
      echo -e "Appuyez sur ${red}N${reset} pour passer au mot suivant.\nAppuyez sur ${green}Entrée${reset} pour l'ajouter:"
      read -n 1 next
    done
    echo""

    #Checker registre
    freg=""
    while [ "$regt" != ${#registres[@]} ]; do 
      registres=()
      regt=""
      echo -e "* Donnez un ou plusieurs ${bold}registres${reset}: "
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
    for i in ${synonymes[*]}; do fsyn+=$i";" ; done ; fsyn="${fsyn%?}"

      #Related
      related=()
      frel=""
      echo "* Donnez des ${bold}mots associés ${reset}au mot ${green}$mot${reset}:"
      read -a related
      for i in ${related[*]}; do frel+=$i";" ; done ; frel="${frel%?}"

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

	#Format de sortie
	clear
	echo ""
	echo "${bold}Résumé${reset}"
	echo ""

	echo "&---------------(*)------------------&"
	echo "Mot: ${green}$mot${reset}"
	echo "Lemme: $lemme"
	echo "Phonétique: $phonetique"
	echo "Classe grammaticale: $grammar"
	echo "Infover: $infover"
	echo "Accord: $accord"
	echo "Genre: $genre"
	echo "Nbsyllabe(s): $nsyll"
	echo "Registre(s): $freg"
	echo "Synonyme(s): ${synonymes[*]}"
	echo "Associé(s): ${related[*]}"
	echo "Theme(s): $ftheme"
	echo "&---------------(*)------------------&"

	#Ecriture sortie
	sortie=""
	sortie+=$(printf "%20s" "$mot")
	sortie+=$(printf "\t%20s" "$lemme")
	sortie+=$(printf "\t%20s" "$phonetique")
	sortie+=$(printf "\t%10s" "$grammar")
	sortie+=$(printf "\t%20s" "$infover")
	sortie+=$(printf "\t%10s" "$genre")
	sortie+=$(printf "\t%10s" "$accord")
	sortie+=$(printf "\t%10s" "$nsyll")
	sortie+=$(printf "\t%40s" "$freg")
	sortie+=$(printf "\t%40s" "$fsyn")
	sortie+=$(printf "\t%40s" "$frel")
	sortie+=$(printf "\t%40s" "$ftheme")

	#On l'enregistre dans fichier de sortie
	echo -e "$sortie" >> $formatedlib
	echo "Le mot ${green}${bold}$mot${reset} a ete ajouté a la base de données."

	#On supprime la ligne en reperant le premier champ (syntaxe spécifique a Mac OSX pour sed)
	#A enrichir pour traiter le cas d'un mot ayant plusieurs entrees en fonction de sa classe grammaticale
	#linetodel=$(awk -v pattern="$mot" 'BEGIN{FS="\t"}; $1==pattern {print NR}' $lib)
	#sed -i "${linetodel}d" $lib
      done
      read -p "Tapez x pour arrêter la saisie." -n 1 uans
      echo ""
    done

    clear

    echo -e "\nBase de données mise à jour."
