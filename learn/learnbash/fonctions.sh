#!/usr/local/bin/bash

echo "Hello Functions"

#On peut ecrire nom_fonction { commandes } ou nom_fonction() {commande} preferer la deuxieme pour plus de portabilité (C style)

say_hello(){
  echo "Hello World!"
  return 2
}

#On peut l'ecrire sous forme comapcte. Ne pas oublier le ; a la fin de la derniere commande de la fonction
say_aurevoir(){ echo "Aurevoir." ; echo "" ;}

#Appel de la fonction.
say_hello
say_aurevoir

#Un appel de fonction est equivalent a executer une commande
a=`say_hello`
echo "$a"

#une fonction ne peut pas etre vide. Si elle contient que des commentaires elle est considérée vide

#Arguments d'une fonction: function_name $arg1 $arg2 (positional parameters, elle les identifie en fonction de l'ordre dans lequel les paramètres sont passés a la fonction

DEFAULT=default
func(){
  if [ -z $1 ];then #Si le parametre est de longueur nulle
    echo "Parameter is zero length"
  else
    echo "Parameter is \"$1\""
  fi
  #Substitution: cette substitution discerne un parametre vide d'un non vide
  #Si le parametre $1 est vide il remplace par $DEFAULT, sinon il ne fait rien
  variable=${1-$DEFAULT}
  echo "variable=$variable"
}

func 
func abricot


#Exit and return
#Les fonctions renvoie une fonction, appelé 'exit status'. l'ES peut etre explicitement spécifié avec un return, sinon par default la fonction renvoie l'exit status de la derniere commande: 0 si succes, non 0 sinon. On peut récuperer ce status avec le parametre "$?". L'exit status joue le role d'un return value fonction.

say_hello
echo $?

#Return a string or array. Utiliser une variable
#Toutes les variables declarés dans une fonction sont partagées avec l'environement d'appel
#Toute variable déclaré locale a une fonction ne le seront pas
return_strin(){
  message="Hello"
  local message_locale="Hello"
}

return_strin

#Declaré dans fonction return_strin mais partagée
echo $message
echo $message_locale #unitialized parameter (car non partagé)

#Passer un tableau a une fonction EQUIV passer tous ses elements
#Les variables $* et $@ contiennent la liste des arguments d'un script shell.
x=("un" "deux" "trois")

print_tableau(){
  local x=("$@")
  for i in "${x[@]}"
  do
    echo $i
  done
}

echo "La fonction s'est terminée avec le code: $?"
echo "Passer un tableau en argument:"
print_tableau "${x[@]}"

#Test local/global
#On peut definir localement des parametres a une fonction qui ne surchargent pas les definitions dans l'environnement
enclume="enclume"
afficher(){ local enclume="marteau"; echo "$enclume";}


afficher
echo $enclume
