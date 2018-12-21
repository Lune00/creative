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

# Les conditions
if [ TEST ];then
  blabla
elif [ test ];then
  blabla
else
  blabla
fi

Ne pas oublier les espaces a l interieur des crochets!!!

#Trois types de test en bash : test sur chaines de caracteres, test sur des nombres, test sur des fichiers

if [ -z $texte ] : verifier si la chaine est vide

Pour comparer des nombres il faut utiliser -eq -ne -gt -ge ...
Enfin les tests sur les fichiers -e -d ...

if [ -d $fichier ];then 
  verifie que le fichier est un repertoire (un repertoire est un fichier, un fichier n  est pas necessairemnet un repertoire)
  -f verifier si le fichier est un fichier (et non un repertoire et s il existe)
ex:

if [ -f "cheminverslefichier" ];then
  echo "Le fichier existe";
fi

#Tester si une expression est trouvee dans un fichier
grep -ci expression fichier
le -c renvoie le nombre de fois l expression est trouvee au lieu de la ligne
le -i ignore la casse

#do wile
while [ test ]; do
  blablabla
done

#Fonctions 
print_something(){
  echo "Hello $1"
}
appel de la fonction print_something Toi
le $1 refere au premier argument passe a la fonction apres son appel
Le return d une fonction en bash n est pas pousse, on renvoie un nombre qu il faudrai interpreter ensuite (0 en general tout va bien, sinon ca va pas)

print_something(){
  echo "Hello $1"
  return 5;
}
On peut recuperer la derniere valeur retournee par le dernier appel de fonction grace a l expression $?


