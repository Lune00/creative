#!/bin/bash

source libconfig.sh

echo "$lib"
#Debut boucle d'ajout a la librairie
while [ -z $reponse ] || [ "$reponse" != "x" ]; do
  while [ -z $wordexist ] || [ $wordexist != "0" ];do
    echo""
    echo "->Nouvelle entrée"
    echo""
    read -p "Entrez le mot à ajouter a la base de données: " mot
    #On teste si le mot n'existe pas deja dans la base
    wordexist=$(grep -ci $mot $lib)
    if [ $wordexist != "0" ];then
      echo "Le mot $mot existe déjà dans la base."
    fi
  done
  wordexist=""

  #Phonetique + test:
  echo ""
  phonetique_t=""
  while [ "$phonetique_t" != ${#phonetique} ];do
    read -p "* Phonetique du mot $mot: " phonetique
    phonetique_t=$(check_phonetique $phonetique) 
  done

  #Nature du mot: 3 lettres (adj,nom,verb...)
  echo ""
  found=""
  while [ "$found" != "found" ];do
    read -p "* Grammaire du mot $mot: " grammar
    found=$(check_grammar $grammar)
  done

  #Lire manuel
  infover=""
  if [ "$grammar" == VER ];then
    read -p "* Infoverbe :" infover
  fi

  #Lemme (base du mot):
  read -p "* Lemme du mot $mot: " lemme
  #Genre:m,f a checker
  echo""
  read -p "* Genre du mot $mot (m,f): " genre
  #Accord:s,p,i a checker
  echo""
  read -p "* Accord du mot $mot (s,p): " accord
  #Nombre de syllabes
  echo""
  read -p "* Nombre de syllabes du mot $mot: " nsyll
  #Registres 
  echo""
  while [ "$regt" != ${#registres[@]} ]; do 
    registres=()
    regt=""
    echo "Donnez un ou plusieurs registres: "
    read -a registres
    regt=$(check_registre "${registres[@]}")
  done

  for i in ${registres[*]}
  do
    freg+=$i";" 
  done 
  freg="${freg%?}"

  #synonymes
  synonymes=()
  fsyn=""
  echo "Donnez des synonymes du mot $mot:"
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
  echo "Donnez des mots associes au mot $mot:"
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
  echo "Mot: $mot"
  echo "Lemme: $lemme"
  echo "Phonétique: $phonetique"
  echo "Classe grammaticale: $grammar"
  echo "Infover: $infover"
  echo "Accord: $accord"
  echo "Genre: $genre"
  echo "Nbsyllabes: $nsyll"
  echo "Registre: ${registres[*]}"
  echo "Synonymes: ${synonymes[*]}"
  echo "Associés: ${related[*]}"
  echo "--------------------------------------"

  #Ecriture sortie
  sortie=""
  sortie+=$(printf "%s" "$mot")
  sortie+=$(printf "\t%s" "$lemme")
  sortie+=$(printf "\t%s" "$phonetique")
  sortie+=$(printf "\t%s" "$grammar")
  sortie+=$(printf "\t%s" "$infover")
  sortie+=$(printf "\t%s" "$genre")
  sortie+=$(printf "\t%s" "$accord")
  sortie+=$(printf "\t%s" "$nsyll")
  sortie+=$(printf "\t%s" "$freg")
  sortie+=$(printf "\t%s" "$fsyn")
  sortie+=$(printf "\t%s" "$frel")

  echo -e "$sortie" >> $formatedlib

  echo "Le mot $mot a ete ajouté a la base de données."
  read -p "Tapez x pour arrêter la saisie." -n 1 reponse
done

echo "Base de données mise a jour."




#On pourra implementer des petits scripts qui donne une analyse base de donnes
#Combien de mots masculins, feminins, qui terminent en a, de verbe, le nombre de mots par syllabes
#Faire un script qui imprime un resume de la base de donnees
#Faire un dernier script qui cherche un mot precis dans la base Lexique
