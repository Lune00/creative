#!/bin/bash
#Lit un fichier en entree (chaque champ est stocke dans un tableau), l'écrit dans un fichier de sortie, et supprime la ligne dans input
filename="$1"
output="output$1"
while read -r line
do
  arr=($line)
  #On l'enregistre dans fichier de sortie
  echo ${arr[*]} >> $output
  #On supprime la ligne en reperant le premier champ (syntaxe spécifique a Mac OSX pour sed)
  sed -i '' "/${arr[0]}/d" $filename
done < "$filename"


