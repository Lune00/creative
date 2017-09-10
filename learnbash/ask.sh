#!/bin/bash

#Script permet de lire la base de donnees lexique, de completer les entrees et de construire une nouvelle base de donnees personelle
#avec en plus le registre, les synonymes et des mots related. Ces derniers doivent aussi appartenir a la base (dans l'idéal pour avoir leur phonétique)

#Todo
#Completer l'entree
#Checker pour doublon
#Chercher une entree particuliere

declare -r lib=toto.txt
declare -r formatedlib=formatedtoto.txt

#On lit tant que l'utilisateur le souhaite ou tant que le fichier lib n'est pas vide
#Ajouter possibilite de passer au mot suivant si celui choisi ne nous interesse pas (appuyer sur N par exemple)

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
    cgram=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $4}')
    genre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $5}') #masculin,feminin
    nombre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $6}') #singulier,pluriels
    freqlivre=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $8}') #frequence occurence livres
    infover=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $11}') #mode,temps,personne pour verbe!
    nsyll=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $24}') 

    echo ""
    echo -e "\n-> Mot : $mot"
    echo "Phonetique:$phonetique"
    echo "Classe gramm:$cgram"
    echo "Genre:$genre"
    echo "Nombre:$nombre"
    echo "Infover:$infover"
    echo "Nsyllabes:$nsyll"
    echo "Freq Livres:$freqlivre"
    read -p "Appuyez sur N pour passer au mot suivant. Entree pour l'ajouter " -n 1 next
  done

  #Registres(plusieurs possibles)
  #${x%?} supprime le dernier caractere
  registres=()
  freg=""
  echo "Donnez un ou pleusieurs registres: "
  read -a registres
  for i in ${registres[*]}; do freg+=$i";" ; done ; freg="${freg%?}"

  #Checker registre


  #synonymes
  synonymes=()
  fsyn=""
  echo "Donnez des synonymes du mot $mot:"
  read -a synonymes
  for i in ${synonymes[*]}; do fsyn+=$i";" ; done ; fsyn="${fsyn%?}"

  #Related
  related=()
  frel=""
  echo "Donnez des mots associes au mot $mot:"
  read -a related
  for i in ${related[*]}; do frel+=$i";" ; done ; frel="${frel%?}"

  #Formater la sortie totale du mot avec printf

  #On l'enregistre dans fichier de sortie
  #On supprime la ligne en reperant le premier champ (syntaxe spécifique a Mac OSX pour sed)
  #  sed -i '' "/${arr[0]}/d" $lib
  read -p "Tapez x pour arrêter la saisie." uans
done


