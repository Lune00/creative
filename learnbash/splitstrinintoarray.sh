#!/usr/local/bin/bash

#Decouper un string en element de tableau selon differents delimiteurs
#Donner le nombre d'éléments differents/identiques

#on suppose qu'on recupere l'ensemble des champs sous cette forme
themes="poésie littérature;voyage poésie"

#IFS permet de specifier l'ensemble des caracteres delimiteurs, ici le ";" et " "
# <<< sert a envoyer de la sortie standard le contenu de string (un pipe poserait probleme car dans un subshell... a mediter)
IFS='; ' read -r -a array <<< "$themes" 

for i in ${array[@]}
do
  echo $i
done

echo "Nombre de thèmes: ${#array[@]}"

#echo "${array[0]}"
#echo "${array[1]}"
#echo "${array[2]}"

#On declare une array associative
#Supprimer un element avec unset arr[index]
declare -A asar

for i in ${array[@]}
do
  for j in ${array[@]}
  do
    if [ "$i" == "$j" ];then
      asar[$i]=$(( ${asar[$i]}+1)) #arithmetic expasion, transforme string en expression numerique
      #On supprime j
    fi
  done
done

for i in ${array[@]}
do
  echo "Theme:$i Occurences:${asar[$i]}"
done

