#!/bin/bash

#Script qui permet d'ajouter manuellement une entree a la librairie.

source libconfig.sh

#Debut boucle d'ajout a la librairie
while [ -z $reponse ] || [ "$reponse" != "x" ]; do

  while [ -z $alreadyin ] || [ "$alreadyin" = true ]; do
    
    echo""
    echo -e "${green}Nouvelle entrée ${reset}"
    echo""
    read -p "Entrez le mot à ajouter a la base de données: " mot

    #Grammaire du mot: 3 lettres (adj,nom,verb...)
    echo ""
    found=""
    while [ "$found" != "found" ];do
      read -p "* Grammaire du mot ${green}$mot${reset}(VER,NOM,ADJ): " -n 3 grammar
      found=$(check_grammar $grammar)
    done
    echo""

    #On teste si le mot n'existe pas deja dans la base
    #Check doublon: mot + grammar deja dans $lib
    #wordexist=$(awk '{print $1}' $formatedlib | grep -wc $mot)
    candidate=$mot$grammar
    alreadyin=false
    a=($(gawk -v var="$mot" 'BEGIN{FS="\t"}{if($1==var) print $1$4}' "$formatedlib"))

    for u in "${a[@]}"
    do
      if [ "$candidate" == "$u" ];then
	alreadyin=true
	break
      fi
    done

    if [ "$alreadyin" == true ];then
      echo "Le mot $mot - (Gramm=$grammar) est déjà présent dans la base."
    fi

  done

  #Lemme (base du mot):
  read -p "* ${magenta}Lemme${reset} du mot $mot: " lemme

  #Phonetique + test:
  echo ""
  phonetique_t=""
  while [ "$phonetique_t" != ${#phonetique} ]; do
    read -p "* ${magenta}Phonetique${reset} du mot ${green}$mot${reset}: " phonetique
    if [ -z $phonetique ]; then phonetique=666; fi
    phonetique_t=$(check_phonetique $phonetique) 
  done

  #Lire manuel
  infover=""
  if [ "$grammar" == VER ];then
    read -p "* Infoverbe :" infover
  elif [ "$grammar" == NOM ] || [ "$grammar" == ADJ ];then
    #Genre:m,f
    while read -p "${bold}Genre${reset} du mot ${green}$mot${reset}(m,f): "  -n 1 genre && [ "$genre" != m ] && [ "$genre" != f ]; do
      echo""
    done
    echo""
    #Accord:s,p
    while read -p "${bold}Accord${reset} du mot ${green}$mot${reset}(s,p): " -n 1 accord && [ "$accord" != s ] && [ "$accord" != p ];do
      echo""
    done
  fi
  echo""

  #Nombre de syllabes
  read -p "* Nombre de ${bold}syllabes${reset} du mot ${green}$mot${reset}: " nsyll 
  #Registres 
  echo""
  registres=()
  regt=""
  while [ "$regt" != ${#registres[@]} ]; do 
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
  #Format synonymes
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
  #Format related
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

  echo -e "$sortie" >> $formatedlib

  echo "Le mot ${red}${bold}$mot${reset} a ete ajouté a la base de données."
  read -p "Tapez x pour arrêter la saisie." -n 1 reponse
done

echo -e "\nBase de données mise à jour."
