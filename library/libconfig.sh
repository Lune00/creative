#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2` yellow=`tput setaf 3`
blue=`tput setaf 4`
magenta=`tput setaf 5`
bold=`tput bold`
reset=`tput sgr0`

#Base de donnees source (Librairie381.txt)
declare -r lib=lexique381.txt
#Base de donnees formatee generee
declare -r formatedlib=mylibrary.txt
#Mots synonymes/related en attente d'etre ajoute comme entree
declare -r waitlib=awaiters.txt

#Tableau de phonetique voyelle et consonnes
phon_table=('a' 'i' 'y' 'u' 'o' 'O' 'e' 'E' '°' '2' '9' '5' '1' '@' '§' '3' 'j' '8' 'w' 'p' 'b' 't' 'd' 'k' 'g' 'f' 'v' 's' 'z' 'Z' 'm' 'n' 'N' 'I' 'R' 'x' 'G' 'S' 'l')
#Tableau de classes gramaticales accpetees
grammar_table=('NOM' 'ADJ' 'VER')
#Tableau de registres acceptes, si aucun registre indique il sera par defaut neutre
registre_table=('neutre' 'lyrique' 'epique' 'melancolique' 'scientifique' 'comique' 'dramatique')

#Fonction qui teste si la phonetique correspond aux symboles (pas d erreur)
#Prend comme argument la phonetique du mot $1
#On construit un tableau vide
#Si chaque caractere correspond a un phoneme de la table on rajoute un 0
#Si la taille du tableau de verite est egale a celle du phoneme en entree c ok
check_phonetique(){
  verite=()
  for i in $(seq 1 ${#1})
  do
    phoneme=${phonetique:$i-1:1}
    #Check si le phoneme  $i existe dans phon_table
    for j in "${phon_table[@]}"
    do
      if [ $phoneme == $j ];then
	verite+="0"
	break
      fi
    done
  done
  echo ${#verite}
}

#Verifie si la classe grammaticale du mot existe
check_grammar(){
  for i in "${grammar_table[@]}"
  do
    if [ $1 == $i ];then
      echo "found"
      break
    fi
  done
}
#Verifie si le registre existe. Si return de check_registre == taille du tableau de registre en argument alors c'estok
check_registre(){
  a=("$@")
  verite=()
  for i in "${a[@]}";do
    for j in "${registre_table[@]}";do
      if [ $i == $j ];then
	verite+="0"
	break
      fi
    done
  done
  echo ${#verite}
}

#Fonction d'affichage

affiche_resume(){

  clear
  echo ""
  echo "${bold}Résumé${reset}"
  echo ""

  local mot="$1"
  local lemme="$2"
  local phonetique="$3"
  local grammar="$4"
  local infover="$5"
  local accord="$6"
  local genre="$7"
  local nsyll="$8"
  local reg="$9"
  local syn="${10}"
  local ass="${11}"
  local themes="${12}"

  echo "&---------------(*)------------------&"
  echo "Mot: ${green}$mot${reset}"
  echo "Lemme: $lemme"
  echo "Phonétique: $phonetique"
  echo "Classe grammaticale: $grammar"
  echo "Infover: $infover"
  echo "Accord: $accord"
  echo "Genre: $genre"
  echo "Nbsyllabe(s): $nsyll"
  echo "Registre(s): $reg"
  echo "Synonyme(s): $syn"
  echo "Associé(s): $ass"
  echo "Theme(s): $themes"
  echo "&---------------(*)------------------&"
}

format_sortie(){

  local mot="$1"
  local lemme="$2"
  local phonetique="$3"
  local grammar="$4"
  local infover="$5"
  local accord="$6"
  local genre="$7"
  local nsyll="$8"
  local reg="$9"
  local syn="${10}"
  local ass="${11}"
  local themes="${12}"

  sortie=""
  #Ecriture sortie
  sortie+=$(printf "%20s" "$mot")
  sortie+=$(printf "\t%20s" "$lemme")
  sortie+=$(printf "\t%20s" "$phonetique")
  sortie+=$(printf "\t%10s" "$grammar")
  sortie+=$(printf "\t%20s" "$infover")
  sortie+=$(printf "\t%10s" "$genre")
  sortie+=$(printf "\t%10s" "$accord")
  sortie+=$(printf "\t%10s" "$nsyll")
  sortie+=$(printf "\t%40s" "$reg")
  sortie+=$(printf "\t%40s" "$syn")
  sortie+=$(printf "\t%40s" "$ass")
  sortie+=$(printf "\t%40s" "$themes")
}

  balise=" - "

  #Test sur la base de donnees source
  if [ ! -f "$lib" ];then
    echo "Impossible de trouver la librairie source ${red}$lib${reset}."
    exit
  else
    echo -e "Base de données source: ${red}$lib${reset}"
    lastmodif=$(ls -l | grep -w $lib | awk ' {print $6" "$7" "$8}')
    echo -e "${balise}Date de la dernière modification:${magenta} $lastmodif ${reset}"
  fi

  #Test sur la base de donnees cible
  if [ -f "$formatedlib" ];then
    taillebase=`awk 'END{print NR}' $formatedlib`
    lastmodif=$(ls -l | grep -w $formatedlib | awk ' {print $6" "$7" "$8}')
    echo -e "Base de données cible: ${red}$formatedlib${reset}"
    echo " - Nombre d'entrées dans $formatedlib: ${bold}${green}$taillebase${reset}"
    echo -e " - Date de la dernière modification:${magenta} $lastmodif ${reset}"
    #Backup
    cp $formatedlib "bk_$formatedlib"
  else
    echo "La base de données $formatedlib n'a pas encore été créee."
    touch $formatedlib
    echo "La base de donnees $formatedlib est créee."
  fi

  #Test sur la base de mots a ajouter
  if [ -f "$waitlib" ];then
    taillewait=`awk 'END{print NR}' $waitlib`
    lastmodif=$(ls -l | grep -w $waitlib | awk ' {print $6" "$7" "$8}')
    echo -e "Liste des mots à ajouter: ${red}$waitlib${reset}"
    echo -e " - Mots en attente: ${green}$taillewait${reset}"
    echo -e " - Date de la dernière modification:${magenta} $lastmodif ${reset}"
    #Backup
    cp $waitlib "bk_$waitlib"
  else
    echo "La liste de mots en atttente n'a pas encore été créee."
    touch $waitlib
    echo "La liste $waitlib est créee"
  fi
