#-QUOTES

#En bash les doubles quotes " " demandent au bash d'interpreter les variables
#Les back quotes ` ` demandent au bash d executer et de stocker le resultat dans une variable
ex : message=`pwd`; echo $message ; 
affichera le resultat de la commande pwd 


#-READ : permet de demander une input a l'utilisateur
read variable (stocke le resultat dans une variable)
ex : read nom prenom
     echo "Bonjour $nom $prenom!"
#-READ -p : pour afficher un message de prompt
ex : read -p "Entrez votre nom et prenom: " nom prenom
     echo "Bonjour $nom $prenom !"


#En bash toutes les variables sont des chaines de caracteres!
#Pour faire des operations mathematiques on peut utiliser let
let "a = 5"
let "b = 2"
let "c = a + b "
echo $c
#les variables d'environnement sont des variables globales, pour les afficher on peut taper env
env

#Creer et manipuler des tableaux
tableau=('valeur0' 'valeur1' 'valeur2')
echo ${tableau[0]}
pour afficher le premier element
echo ${tableau[*]} 
pour afficher tous les elements

#-Existence fichier
if [ -f "cheminverslefichier" ];then
  echo "Le fichier existe";
fi

#Les conditions

