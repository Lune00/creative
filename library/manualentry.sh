#!/bin/bash

#Script qui permet d'ajouter manuellement une entree a la librairie.

source libconfig.sh

#Debut boucle d'ajout a la librairie
while [ -z $reponse ] || [ "$reponse" != "x" ]; do

  while [ -z $alreadyin ] || [ "$alreadyin" = 1 ]; do
    
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
    check_doublons_in_formatedlib "$mot" "$grammar"
    alreadyin="$?"
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

    affiche_resume "$mot" "$lemme" "$phonetique" "$grammar" "$infover" "$accord" "$genre" "$nsyll" "$freg" "$fsyn" "$frel" "$ftheme" 

    format_sortie "$mot" "$lemme" "$phonetique" "$grammar" "$infover" "$accord" "$genre" "$nsyll" "$freg" "$fsyn" "$frel" "$ftheme" 

  echo -e "$sortie" >> $formatedlib

  echo "Le mot ${red}${bold}$mot${reset} a ete ajouté a la base de données."
  read -p "Tapez x pour arrêter la saisie." -n 1 reponse
done

echo -e "\nBase de données mise à jour."
