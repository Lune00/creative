#!/usr/local/bin/bash

echo "Fonction d'affichage"

afficher(){
  animaux=("$1")
  pronoms=("$2")

  echo "Animaux:"
  for i in "$animaux"
  do
    echo "$i"
  done
  echo "Pronoms:"
  for i in "$pronoms"
  do
    echo "$i"
  done
}

a=("chien" "chat" "loup")
b=("je" "tu" "il")

#On les passe comme string
as="${a[@]}"
bs="${b[@]}"

afficher "$as" "$bs"


