#!/bin/bash

source libconfig.sh

#Script permet de lire la base de donnees lexique, de completer les entrees et de construire une nouvelle base de donnees personelle

#On lit tant que l'utilisateur le souhaite ou tant que le fichier lib n'est pas vide
#Ajouter possibilite de passer au mot suivant si celui choisi ne nous interesse pas (appuyer sur N )

while [ -z $uans ] || [ "$uans" != "x" ] && [ -s $lib ];do
  next=N
  while [ "$next" == "N" ]; do
    #On prend une ligne au hasard
    line=$(gshuf $lib | head -n 1) 
    #On mouline avec awk la ligne pour recuperer les champs qui nous interessent (awk garde trace des champs vides ok)
    #On a 9 champs de base auquel on va rajouter : un registre / synonymes / related
    mot=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $1}')
    phonetique=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $2}')
    lemme=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $3}')
    grammar=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $4}')
    genre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $5}') #masculin,feminin
    nombre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $6}') #singulier,pluriels
    infover=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $11}') #mode,temps,personne pour verbe!
    nsyll=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $24}') 

    echo ""
    echo -e "\n-> Mot : ${green}$mot${reset}"
    echo "Phonetique: $phonetique"
    echo "Classe gramm: $grammar"
    echo "Genre: $genre"
    echo "Nombre: $nombre"
    echo "Infover: $infover"
    echo "Nsyllabes: $nsyll"
    read -p "* Appuyez sur N pour passer au mot suivant. Entree pour l'ajouter " -n 1 next
  done
  echo""
  #Check doublon

  candidate=$mot$grammar
  alreadyin=false
  a=($(gawk -v var="$mot" '{if($1==var) print $1$4}' "$formatedlib"))
  for u in "${a[@]}"
  do
    if [ "$candidate" == "$u" ];then
      alreadyin=true
      break
    fi
  done
  if [ "$alreadyin" == true ];then
    echo "Le mot $mot - (Gramm=$grammar) est déjà présent dans la base"
    continue
  fi

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


    affiche_resume "$mot" "$lemme" "$phonetique" "$grammar" "$infover" "$accord" "$genre" "$nsyll" "$freg" "$fsyn" "$frel" "$ftheme" 

    format_sortie "$mot" "$lemme" "$phonetique" "$grammar" "$infover" "$accord" "$genre" "$nsyll" "$freg" "$fsyn" "$frel" "$ftheme" 

      #On l'enregistre dans fichier de sortie
      echo -e "$sortie" >> $formatedlib
      echo "Le mot ${red}${bold}$mot${reset} a ete ajouté a la base de données."

      #On supprime la ligne en reperant le premier champ (syntaxe spécifique a Mac OSX pour sed)
      #linetodel=$(awk -v pattern="$mot" 'BEGIN{FS="\t"}; $1==pattern {print NR}' $lib)
      #sed -i "${linetodel}d" $lib
      read -p "Tapez x pour arrêter la saisie." -n 1 uans
      echo ""
    done

    echo -e "\nBase de données mise à jour."
