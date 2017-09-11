#!/bin/bash

source libconfig.sh

#Script permet de lire la base de donnees lexique, de completer les entrees et de construire une nouvelle base de donnees personelle

#On lit tant que l'utilisateur le souhaite ou tant que le fichier lib n'est pas vide
#Ajouter possibilite de passer au mot suivant si celui choisi ne nous interesse pas (appuyer sur N )

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
    infover=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $11}') #mode,temps,personne pour verbe!
    nsyll=$(echo "$line" | awk 'BEGIN{FS="\t"}; {print $24}') 

    echo ""
    echo -e "\n-> Mot : ${green}$mot${reset}"
    echo "Phonetique:$phonetique"
    echo "Classe gramm:$cgram"
    echo "Genre:$genre"
    echo "Nombre:$nombre"
    echo "Infover:$infover"
    echo "Nsyllabes:$nsyll"
    read -p "Appuyez sur N pour passer au mot suivant. Entree pour l'ajouter " -n 1 next
  done
  echo""

  #Checker registre
  while [ "$regt" != ${#registres[@]} ]; do 
    registres=()
    regt=""
    echo -e "* Donnez un ou plusieurs ${bold}registres${reset}: "
    read -a registres
    regt=$(check_registre "${registres[@]}")
  done

  for i in ${registres[*]}
  do
    freg+=$i";" 
  done 
  freg="${freg%?}"

  if [ -z $freg ];then freg=neutre ; fi

  #synonymes
  synonymes=()
  fsyn=""
  echo "* Donnez des ${bold}synonymes${reset} du mot ${green}$mot${reset}:"
  read -a synonymes
  for i in ${synonymes[*]}; do fsyn+=$i";" ; done ; fsyn="${fsyn%?}"

  #Related
  related=()
  frel=""
  echo "* Donnez des ${bold}mots associés ${reset}au mot ${green}$mot${reset}:"
  read -a related
  for i in ${related[*]}; do frel+=$i";" ; done ; frel="${frel%?}"

  #Format de sortie
  echo ""
  echo "Résumé"
  echo ""

  echo "--------------------------------------"
  echo "Mot: ${green}$mot${reset}"
  echo "Lemme: $lemme"
  echo "Phonétique: $phonetique"
  echo "Classe grammaticale: $grammar"
  echo "Infover: $infover"
  echo "Accord: $accord"
  echo "Genre: $genre"
  echo "Nbsyllabes: $nsyll"
  echo "Registre: $freg"
  echo "Synonymes: ${synonymes[*]}"
  echo "Associés: ${related[*]}"
  echo "--------------------------------------"

  #Ecriture sortie
  sortie=""
  sortie+=$(printf "%20s" "$mot")
  sortie+=$(printf "\t%20s" "$lemme")
  sortie+=$(printf "\t%20s" "$phonetique")
  sortie+=$(printf "\t%10s" "$grammar")
  sortie+=$(printf "\t%20s" "$infover")
  sortie+=$(printf "\t%10s" "$genre")
  sortie+=$(printf "\t%10s" "$accord")
  sortie+=$(printf "\t%10s" "$nsyll")
  sortie+=$(printf "\t%40s" "$freg")
  sortie+=$(printf "\t%40s" "$fsyn")
  sortie+=$(printf "\t%40s" "$frel")

  #On l'enregistre dans fichier de sortie
  echo -e "$sortie" >> $formatedlib
  echo "Le mot ${red}${bold}$mot${reset} a ete ajouté a la base de données."

  #On supprime la ligne en reperant le premier champ (syntaxe spécifique a Mac OSX pour sed)
  #  sed -i '' "/${arr[0]}/d" $lib
  read -p "Tapez x pour arrêter la saisie." uans
done

echo -e "\nBase de données mise à jour."
