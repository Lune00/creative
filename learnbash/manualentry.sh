#!/bin/bash

#Script qui permet d'ajouter manuellement une entree a la librairie.

source libconfig.sh

echo "$lib"
#Debut boucle d'ajout a la librairie
while [ -z $reponse ] || [ "$reponse" != "x" ]; do
  while [ -z $wordexist ] || [ $wordexist != "0" ]; do
    echo""
    echo -e "${green}Nouvelle entrée ${reset}"
    echo""
    read -p "Entrez le mot à ajouter a la base de données: " mot
    #On teste si le mot n'existe pas deja dans la base
    wordexist=$(awk '{print $1}' $formatedlib | grep -wc $mot)
    if [ $wordexist != "0" ];then
      echo -e "Le mot - ${magenta}${green}$mot${reset}${reset} - existe déjà dans la base de données."
    fi
  done
  wordexist=""

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

  #Nature du mot: 3 lettres (adj,nom,verb...)
  echo ""
  found=""
  while [ "$found" != "found" ];do
    read -p "* Grammaire du mot ${green}$mot${reset}(VER,NOM,ADJ): " -n 3 grammar
    found=$(check_grammar $grammar)
  done
  echo""

  #Lire manuel
  infover=""
  if [ "$grammar" == VER ];then
    read -p "* Infoverbe :" infover
  elif [ "$grammar" == NOM ] || [ "$grammar" == ADJ ];then
    #Genre:m,f a checker
    read -p "* Genre du mot ${green}$mot${reset}(m,f): " -n 1 genre
    #Accord:s,p,i a checker
    echo""
    read -p "* Accord du mot ${green}$mot${reset}(s,p): " -n 1 accord
  fi

  #Nombre de syllabes
  echo""
  read -p "* Nombre de ${bold}syllabes${reset} du mot ${green}$mot${reset}: " nsyll 
  #Registres 
  echo""
  registres=()
  regt=""
  while [ "$regt" != ${#registres[@]} ]; do 
    echo -e "Donnez un ou plusieurs ${bold}registres${reset}: "
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
  echo "Donnez des ${bold}synonymes${reset} du mot ${green}$mot${reset}:"
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
  echo "Donnez des ${bold}mots associés ${reset}au mot ${green}$mot${reset}:"
  read -a related
  #Format related
  for i in ${related[*]}
  do 
    frel+=$i";"
  done
  frel="${frel%?}"

  #Format de sortie
  echo ""
  echo "Résumé"
  echo ""

  echo "--------------------------------------"
  echo "Mot: ${green}$mot${reset}"
  echo "Lemme: $lemme"
  echo "Phonétique: $phonetique"
  echo "Classe grammaticale: $grammar"
  echo "Infover: $infover"
  echo "Accord: $accord"
  echo "Genre: $genre"
  echo "Nbsyllabes: $nsyll"
  echo "Registre: $freg"
  echo "Synonymes: ${synonymes[*]}"
  echo "Associés: ${related[*]}"
  echo "--------------------------------------"

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

  echo -e "$sortie" >> $formatedlib

  echo "Le mot ${red}${bold}$mot${reset} a ete ajouté a la base de données."
  read -p "Tapez x pour arrêter la saisie." -n 1 reponse
done

echo -e "\nBase de données mise à jour."
