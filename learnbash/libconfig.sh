#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`

reset=`tput sgr0`

#Reference a la base de donnees(bdd)
declare -r lib=toto.txt
declare -r formatedlib=formatedtoto.txt

#Tableau de phonetique voyelle et consonnes
phon_table=('a' 'i' 'y' 'u' 'o' 'O' 'e' 'E' '°' '2' '9' '5' '1' '@' '§' '3' 'j' '8' 'w' 'p' 'b' 't' 'd' 'k' 'g' 'f' 'v' 's' 'z' 'Z' 'm' 'n' 'N' 'I' 'R' 'x' 'G' 'S' 'l')
grammar_table=('NOM' 'ADJ' 'VER')

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

#Verifie si la nature du mot existe
check_grammar(){
  for i in "${grammar_table[@]}"
  do
    if [ $1 == $i ];then
      echo "found"
      break
    fi
  done
}
#Si return de check_registre == taille du tableau de registre en argument alors c'estok
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

#On test si la base existe, si elle n'existe pas, on la cree.
if [ -f "$formatedlib" ];then
  echo "La base de donnees $formatedlib existe."
  taillebase=`awk 'END{print NR}' $lib`
  echo "La base contient $taillebase mots."
else
  echo "La base de donnees $formatedlib n'a pas encore ete cree."
  touch $formatedlib
  echo "La base de donnees $formatedlib a ete cree."
fi


