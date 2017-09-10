#!/bin/bash
#Lit un fichier en entree (chaque champ est stocke dans un tableau), l'écrit dans un fichier de sortie, et supprime la ligne dans input
#Prendre une ligne au hasard
#Demander si on veut process une nouvelle ligne
#Completer l'entree
#Checker pour doublon
#Chercher une entree particuliere
lib="toto.txt"
formatedlib="formatedtoto.txt"

#On lit tant que l'utilisateur le souhaite ou tant que le fichier lib n'est pas vide
while [ -z $uans ] || [ "$uans" != "x" ] && [ -s $lib ] ;do
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
  nsyll=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $24}') #mode,temps,personne pour verbe!

  #echo "Ligne prise au hasard: $line"
  echo "->Mot:$mot"
  echo "Phonetique:$phonetique"
  echo "Classe gramm:$cgram"
  echo "Genre:$genre"
  echo "Nombre:$nombre"
  echo "Infover:$infover"
  echo "Nsyllabes:$nsyll"
  echo "Freq Livres:$freqlivre"
  #Ajouter registre, synonymes, related

  #On l'enregistre dans fichier de sortie
  #On supprime la ligne en reperant le premier champ (syntaxe spécifique a Mac OSX pour sed)
#  sed -i '' "/${arr[0]}/d" $lib
  read -p "Tapez x pour arrêter la saisie." uans
done


