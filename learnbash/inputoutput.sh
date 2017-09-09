#!/bin/bash

#Reference a la base de donnees(bdd)
bdd="poesielibrairie.txt"

#On test si la base existe, si elle n'existe pas, on la cree.
if [ -f "$bdd" ];then
  echo "La base de donnees $bdd existe."
else
  echo "La base de donnees $bdd n'a pas encore ete cree."
  touch $bdd
  echo "La bae de donnees $bdd a ete cree."
fi

