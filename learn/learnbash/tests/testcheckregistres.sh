#!/bin/bash
source libconfig.sh

while [ "$regt" != ${#registres[@]} ]; do 
  registres=()
  regt=""
  echo "Donnez un ou plusieurs registres: "
  read -a registres
  regt=$(check_registre "${registres[@]}")
  echo ${regt} ${#registres[@]}
done
