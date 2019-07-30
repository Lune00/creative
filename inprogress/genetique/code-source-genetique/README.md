# GENOMLIB

## Objectifs

*Genomlib* est une librairie C++. Elle utilise elle même la libraire libconfig pour l'interface avec le fichier de configuration.

**Ce projet n'a pas pour but de simuler les mécanismes génétiques mais de les modéliser**, en reproduisant les mécanismes généraux ayant lieu lors de la reproduction afin d'obtenir une variété de phénotypes satisfaisante.

Le but de ce projet est de fournir une bilbliotheque minimale pour mettre en place un génome [diploïde](https://fr.wikipedia.org/wiki/Diploïde) transmissible et ses mécanismes génétiques associés : transmission d'un matériel génétique ( reproduction, méiose, crossing-over ... ) et donc de caractères héréditaires, de génération en génération, s'exprimant macroscopiquement sous la forme de traits ( _features_ ) ou phénotype. Lla reproduction peut se réaliser avec un partenaire (sexuée ou non), par clonage ou par auto-fécondation (comme certaines plantes).

Il serait inutile de complexifier le modèle avec l'ajout de mécanismes trop spécifiques alors que des mécanismes essentiels dans l'expression du génome ne sont pas pris en compte. L'auteur de la libraire en juge la complexité suffisante pour obtenir un brassage génétique qui permette à la fois d'explorer la variabilité des phénotypes, de _ressentir_ l'hérédité d'une génération à l'autre, et d'instaurer des mécanismes de sélection intéressants.

Le but est de fournir également une bibliothèque intéressante pour faire de la génération procédurale d'espèces et narrative ( via les mécanismes de descendance et de selection, ici _naturelles_, sans avoir recours a des méthodes aléatoires mal controlées ) .

## Description générale

La librairie modelise les caractères rudimentaires et simplifiés de la génétique: population initiale de genes ( et d'alleles), régles de codominance entre allèles d'un meme gene, transmission par méiose. 

Chaque trait phénotypique (taille, couleur des yeux ...) peut-être codé par un ou plusieurs gènes. Chaque gène peut posséder un ou plusieurs allèles. Les règles de codominance entre allèles peuvent être définies par l'utilisateur. 

Le phénotype est calculé selon les regles de co-dominance (expression du genome). Ce génome est ensuite transmis lorsque deux individus se dupliquent ( sans partenaire) ou procréent ( avec un partenaire ) . Dans le cas d'une reprodution, et non d'une duplication (mitose) un processus de [méiose](https://fr.wikipedia.org/wiki/Méiose) est simulé: une partie du génome (un chromosome au hasard sur les deux) est transmis par chaque parent a l'individu enfant. L'enfant dispose d'un genome hérité de ses parents et peut le transmettre à son tour. Le [crossing-over](https://fr.wikipedia.org/wiki/Enjambement_(génétique)) pourra être activé par l'utilisateur (si désactivé réduit la meiose a une recombinaison des chromatides) .

Pas d'épigénétique pour le moment (rétroaction des traits ou de l'environnement de l'individu sur son genome).

Un programme ( avec interface graphique ) sera développé en parallèle pour écrire le fichier de configuration ( contenant les features ) nécessaire au fonctionnement de la librairie.

## Modélisation du matériel génétique

### Généralités
Le matériel génétique est un ensemble de paires de chromosomes qui sont des collections de matériel codant (gènes) et non codants (séquences aléatoires pouvant servir à produire des mutations). Les chromosomes sont le support  des informations génétiques qui interviennent dans la détermination et la transmission des caractères héréditaires ou _features_. Les gènes sont une portion du chromosome et sont situés à un emplacement précis. Ce sont eux qui codent pour la _feature_, ou le phénotype ( résultat `macroscopique` de l'expression des gènes ). Un gène existe en deux exemplaires occupant la même position sur chacun des deux chromosomes d'une même paire. 

Un même gène peut exister sous différentes formes appelées _allèles_. Pour un même gène donné les deux chromosomes d'une même paire peuvent porter deux allèles identiques ou différentes. Les allèles peuvent être codominantes (expression des deux allèles de manière pondérée ), ou un seul des deux peut s'exprimer (dominant et récessif). 

### Dans la librairie
Chaque caractère héréditaire, ou _feature_ est codée par un ou plusieurs gènes présents en deux exemplaires sur la paire de chromosome (un sur chaque chromosome).  Chaque _gène_ existe sous la forme d'_allèles_ représentés par un *entier compris entre 0 et 9*.

Chaque _feature_ est mesurée macroscopiquement (expression des gènes) par un nombre flottant ( caractère continu comme la taille) ou par un entier (caractère discret comme l'absence de plumes), c'est sa _valeur_ . Cette _valeur_ est ensuite interprétable par l'utilisateur de la librairie.

## Déclaration des _features_

Une _feature_ est un trait phénotypique qui est codé par un ensemble de gènes (couleur des ailes, taille, absence ou non d'un organe etc.. ).
Deux natures de trait sont disponibles: continu (sa valeur est continue, elle peut prendre n'importe quelle valeur entre -1 et 1, comme la taille) et discret ( sa valeur est discrete et entiere, elle ne peut prendre que certaines valeurs spécifiques). Dans le cas d'une nature discrete l'expression des gènes contribuant à la feature renvoie un entier correspondant au numéro de l'allèle ( de 0 à 9 ) . Dans le cas d'une nature continue, l'expression des gènes contribuant à la feature renvoie un nombre flottant compris entre -1 et 1. 

Ensuite l'utilisateur à la charge de créer l'interface pour donner un sens à ces nombres dans le cadre de son programme. Une grandeur ( avec une unité associée ) comme une longeur, un temps ... pourra également être attribuée, pour remettre à l'échelle cette valeur, et lui donner une interprétation en fonction du contexte voulu par l'utilisateur.

### Fichier de configuration

Le fonctionnement de la librairie nécessite le chargement d'un fichier de config (par défaut nommé _abstractFeatures.glib_ ) qui contient plusieurs champs. La lecture du fichier de configuration utilise la bibliothèque [libconfig](https://github.com/hyperrealm/libconfig). 

#### Features abstraites 

Le setting ( voir libconfig ) *abstractFeatures* est obligatoire et permet de charger les _features_ définies par l'utilisateur. Le terme _abstrait_ se rapporte au fait que les _features_ écrites par l'utilisateur sont des templates de feature. Chaque feature abstraite peut être utilisée pour créer différentes features. Une feature abstraite se déclare à l'aide de plusieurs champs :

- **label** [obligatoire] : nom abstrait associé à la feature. Il permet à l'utilisateur de désigner la feature dans le programme. Un nom sera ensuite défini dans un second temps lorsque la feature sera utilisée. Ainsi une feature abstraite avec un label peut servir de base pour plusieurs features. 
- **nature** [obligatoire]  [`string`]: une feature peut etre discrète ("Discrete" ou "D" ), elle ne peut prendre que plusieurs valeurs définies par l'utilisateur, ou continue ("Continuous" ou "C" ), elle peut prendre n'importe qu'elle valeur sa valeur min et sa valeur max. Par exemple 
```
abstractFeatures=(
{ label = "body-size" ;
  nature = "Discrete" ;
}
```
indique que l'on déclare une feature abstraite codant pour la taille d'un individu.
- **nGenes** [obligatoire][`int`] : nombre de gènes sur lequel est codée la feature. Un minimum de trois gènes permet d'obtenir une bonne variété de phénotypes avec un jeu d'allèles réduit (ces points sont abordés dans la section Statistiques et analyse du modèle ).
- **alleles** [optionnel][`list int`] : énumération des allèles disponibles pour la feature. Les allèles sont des entiers allant de 0 à 9 (inclus). Par exemple `alleles = (0,3,9) ;` indique que chaque gène codant pour la feature pourra être une allèle 0, 3 ou 9.
- **codRules** [optionnel][`list string`] : déclaration des règles de co-dominance entre allèles d'une même paire. Si elles ne sont pas spécifiées les règles seront générées selon soit par un comportement par défaut ( aléatoires ) soit suivant une option définie par l'utilisateur. Par exemple `3-1=3`déclare que l'allèle `3`domine toujours l'allèle `1`.
- **options**[optionnel][`list string`] : TODO

Voici un exemple complet d'un fichier de configuration avec trois features, deux discrètes et une continue : 
```
abstractFeatures=(
 { label = "body-size" ;
   nature = "Discrete" ;
   nGenes = 1 ; },
   
{ label = "eye-color";
  nature = "D" ;
  nGenes = 1 ;
  alleles = (1 , 2 , 3 );
  codRules = ( "2-1=p0.2", "1-3=3", "3-2=3"); },

{ label = "foot-size" ;
  nature = "C" ;
  nGenes = 1 ;
  alleles = (0,3,9);
  codRules = ("0-9=0. ", "3-0=0.9", "3-9=0.3",); } );
```
Plusieurs syntaxes se retrouvent dans l'écriture des règles de co-dominance détaillées dans le paragraphe suivant.

#### Syntaxe des règles de codominance

Une règle s'écrit de la forme `alleleA-alleleB=?`où `?`est une syntaxe propre à chaque nature de feature. A gauche les deux allèles pour lesquelles on écrit la règle sont reliées par un `-` , et après le caractère `=`est écrit le résultat de l'expression si ces deux allèles se retrouvent dans une même paire. 

**Les règles de co-dominance, si elles sont écrites par l'utilisateur, doivent couvrir l'ensemble des combinaisons d'allèles possibles sinon un message d'erreur sera affiché et l'execution du programme arrêtée.**

##### Cas d'une feature Discrete
Dans le cas d'une feature discrete deux syntaxes sont possibles : 
``` 
alleleA-alleleB=alleleA
```
signifie que `alleleA`est dominante et que `alleleB`est récessive.  On peut également souhaiter voir `alleleA` dominer `alleleB` dans certains cas et non dans d'autres, avec une certaine probabilité. Dans ce cas on pourra écrire
``` 
alleleA-alleleB=p0.3
```
où `p0.3`signifie que `alleleA` domine `alleleB`dans 30% des cas, c'est à dire dans 30% des cas où l'expression de la feature est évaluée, c'est une expression probabiliste. **La probabilité s'applique toujours a l'allèle déclarée en premier.**

**Remarque** : la syntaxe n'est pas permissive. Si une règle est déclarée pour deux allèles qui ne sont pas présentes dans _alleles_ une erreur sera émise. 

##### Cas d'une feature Continue
Dans le cas d'une feature continue une seule syntaxe est possible : 
```
a-b=c(a,b)
```
où `c(a,b)`est un nombre flottant **strictement compris entre 0 et 1.** 
Par exemple `1-3=0.3`indique que l'allèle `1` contribue à 30% à l'expression de la feature, et que l' allèle`3` contribue à 70%.


#### Contribution des allèles et calcul de l'expression d'une _feature_

Chaque allèle, un entier compris entre 0 et 9, contribue de manière égale à leur propre valeur.

Les coefficients de codominance sont obligatoirement compris entre 0 et 1. 

Chaque _feature_ a une valeur (interprétée par l'utilisateur) comprise entre -1 et +1 si elle est continue, ou égale à un entier compris entre 0 et 9 si elle est discrète.

Par exemple, pour une feature codée uniquement sur un gene, et celui ci n'ayant que deux allèles `a` et `b`, le trait est donné par

`Valeur feature = (1-c(a,b)) * valeur_a + c(a,b) * valeur_b`

 Si l'on reprend l'exemple précédent d'une feature continue codée sur un gène avec deux allèles `1`et `3`ayant pour règle de co-dominance `1-3=0.3` , la `valeur` de la _feature_ est donnée par `valeur = 0.3 * 1 + (1 - 0.3) * 3 = 2.4` . Cette valeur est comprise entre 0 et 9, elle est ensuite normalisée pour être comprise entre -1 et 1.

Lorsqu'une feature est codée sur plusieurs gènes, la `valeur`de la feature s'exprime sous la forme


### Structure des gènes

Chaque gène est un tableau d'entiers de dix bases nucléiques en binaire. La contribution d'un gène a la valeur macroscopique est donnée par la somme de ces bases (chaque base apportant 1 ou 0 a la contribution totale). Par exemple l'allèle `6` peut être représentée sous la forme d'une séquence `1110110010`, où la position des `1`et des `0` est aléatoire. La contribution d'une allèle a l'expression d'une paire de gènes est donc égale à la somme des bases nucléiques qui composent le gène.


### Paramètres de la population initiale d'allèles  TODO

Notes : Controle de la gaullienne vers des valeurs extremes, poids associé a chaque allele (rareté, abondance)

## Fonctionnement global de la librairie

## Utilisation de la librairie



## Lois d'échelle et considérations statistiques du modèle génétique employé

La diversité d'un trait (nombre de combinaisons possibles) varie proportionnellement au nombre d'allèles par gene, en puissance avec la ploidie et en puissance avec le nombre de gènes pour un trait phénotypique. Le nombre de chromosomes sur lesquels sont répartis les genes contribue au brassage génétique. Il permet a un nombre fixé de variations pour chaque trait d'augmenter le nombre de phénotypes (ensemble des traits) accessibles à la descendance. Enfin le crossing over ayant lieu durant la meiose augmente encore la portée du brassage génétique et de la diversité phénotypique pour un genome donné. Pour augmenter rapidement le spectre des valeurs prises par un trait, et s'approcher d'une distribution continue, il est recommandé d'associer plusieurs gènes à un trait. Un billet de blog sera bientôt disponible dans lequel ces effets seront discutés.

TODO : arrivée au théorème central limit (nombre de genes par feature)

## Description des classes

Toute instanciation d'une classe héritant de *genome* peut se reproduire avec une instanciation de sa propre classe ou une instanciation d'une classe héritant du meme genome.

