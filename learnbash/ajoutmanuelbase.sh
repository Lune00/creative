#!/bin/bash

#Reference a la base de donnees(bdd)
bdd="poesielibrairie.txt"
#Tableau de phonetique voyelle et consonnes
#Note : le • alt+maj+point represente la phoneme "on"
phon_table=('a' 'i' 'y' 'u' 'o' 'O' 'e' 'E' '°' '2' '9' '5' '1' '@' '•' '3' 'j' '8' 'w' 'p' 'b' 't' 'd' 'k' 'g' 'f' 'v' 's' 'z' 'Z' 'm' 'n' 'N' 'I' 'R' 'x' 'G' 'S' 'l')
nature_table=('nom' 'adj' 'ver')

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
check_nature(){
  for i in "${nature_table[@]}"
  do
    if [ $1 == $i ];then
      echo "found"
      break
    fi
  done
}

#On test si la base existe, si elle n'existe pas, on la cree.
if [ -f "$bdd" ];then
  echo "La base de donnees $bdd existe."
else
  echo "La base de donnees $bdd n'a pas encore ete cree."
  touch $bdd
  echo "La base de donnees $bdd a ete cree."
fi

taillebase=`awk 'END{print NR}' $bdd`
echo "La base contient $taillebase mots."

#Debut boucle d'ajout a la librairie
while [ -z $reponse ] || [ "$reponse" != "x" ]; do
  while [ -z $wordexist ] || [ $wordexist != "0" ];do
    echo""
    echo "->Nouvelle entrée"
    echo""
    read -p "Entrez le mot à ajouter a la base de données: " mot
    #On teste si le mot n'existe pas deja dans la base
    wordexist=$(grep -ci $mot $bdd)
    if [ $wordexist != "0" ];then
      echo "Le mot $mot existe déjà dans la base."
    fi
  done
  wordexist=""

  #Traitement de l'entree:

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
    read -p "* Nature du mot $mot: " nature
    found=$(check_nature $nature)
  done

  #Genre:m,f,n a checker
  echo""
  read -p "* Genre du mot $mot (m,f,n): " genre
  #Accord:s,p,i,n a checker
  echo""
  read -p "* Accord du mot $mot (s,p,i,n): " accord
  #Nombre de syllabes
  echo""
  read -p "* Nombre de syllabes du mot $mot: " nsyll
  #Registre checker
  echo""
  read -p "* Registre du mot $mot: " registre

  #Synonymes 
  synonymes=()
  echo "Donnez des synonymes du mot $mot:"
  read -a synonymes

  #Related
  related=()
  echo "Donnez des mots associes au mot $mot:"
  read -a related

  #Format de sortie
  echo ""
  echo "Résumé"
  echo ""

  echo "--------------------------------------"
  echo "Mot: $mot"
  echo "Phonétique: $phonetique"
  echo "Nature: $nature"
  echo "Accord: $accord"
  echo "Genre: $genre"
  echo "Nbsyllabes: $nsyll"
  echo "Registre: $registre"
  echo "Synonymes: ${synonymes[*]}"
  echo "Associés: ${related[*]}"
  echo "--------------------------------------"

  #Recapitulatif et demande de confirmation

  #Ecriture sortie

  echo "Le mot $mot a ete ajouté a la base de données."
  read -p "Tapez x pour arrêter la saisie." reponse
done


echo "Base de données mise a jour."


#On pourra implementer des petits scripts qui donne une analyse base de donnes
#Combien de mots masculins, feminins, qui terminent en a, de verbe, le nombre de mots par syllabes
#Faire un script qui imprime un resume de la base de donnees

