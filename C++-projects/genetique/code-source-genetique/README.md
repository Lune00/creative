# geneticsLib

## Objectifs

*geneticsLib* est une librairie C++. Elle utilise elle même la libraire libconfig pour l'interface avec le fichier de configuration.

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
Le matériel génétique est un ensemble de paires de chromosomes qui sont des collections de matériel codant (gènes) et non codants (séquences aléatoires pouvant servir à produire des mutations). Les chromosomes sont le support  des informations génétiques qui interviennent dans la détermination et la transmission des caractères héréditaires ou _features_. Les gènes sont une portion du chromosome et sont situés à un emplacement précis, le locus. Ce sont eux qui codent pour la _feature_, ou le phénotype ( résultat _macroscopique_ de l'expression des gènes ). Un gène existe en deux exemplaires occupant la même position sur chacun des deux chromosomes d'une même paire. 

Un même gène peut exister sous différentes formes appelées _allèles_. Pour un même gène donné les deux chromosomes d'une même paire peuvent porter deux allèles identiques ou différentes. Les allèles peuvent être codominantes (expression des deux allèles de manière pondérée ), ou un seul des deux peut s'exprimer (dominant et récessif). 

### Dans la librairie
Chaque caractère héréditaire, ou _feature_ est codée par un ou plusieurs gènes présents en deux exemplaires sur la paire de chromosome (un sur chaque chromosome).  Chaque _gène_ existe sous la forme d'allèles représentés par un *entier compris entre 0 et 9*.

Chaque paire de gènes (dont les versions ou allèles peuvent être différents) est évaluée au moment de la détermination de la valeur de la _feature_ pour laquelle elle code. La détermination de l'expression d'une paire de gènes nécessite l'adjonction d'une règle d'expression ou `Rule`. Elle spécifie la relation de domination (complète, partielle ou probabiliste) entre les deux allèles présents. Par exemple, si un gène a deux allèles `1`et `7`il faut spécifier une règle de co-domination entre elles: est ce que l'allèle `1` est dominante ou récessive ? Est ce que l'allèle `1` et `7` s'expriment toutes les deux ? Et si c'est le cas, dans quelles proportions ? La règle permet d'établir l'évaluation. C'est un nombre flottant appelé `domination`et donne la contribution de chaque gène (chaque paire d'allèles) a la _feature_. Dans cet exemple, on l'écrit sous la forme `c(1,7)=domination`.
 
Chaque _feature_ est mesurée macroscopiquement (expression des gènes) par un nombre flottant (caractère continu comme la taille) ou par un entier (caractère discret comme l'absence de plumes), c'est sa valeur, ou `value` . La `value` est ensuite interprétable par l'utilisateur de la librairie.

## Déclaration et fonctionnement des _features_

Une _feature_ est un trait phénotypique qui est codé par un ensemble de gènes (couleur des ailes, taille, absence ou non d'un organe etc.. ).

Deux natures de trait sont disponibles: continu (sa valeur est continue, elle peut prendre n'importe quelle valeur entre -1 et 1, comme la taille) et discret ( sa valeur est discrete et entiere, elle ne peut prendre que certaines valeurs spécifiques). Dans le cas d'une nature discrete l'expression des gènes contribuant à la feature renvoie un entier correspondant au numéro de l'allèle ( de 0 à 9 ) . Dans le cas d'une nature continue, l'expression des gènes contribuant à la feature renvoie un nombre flottant compris entre -1 et 1. 

Ensuite l'utilisateur à la charge de créer l'interface pour donner un sens à ces nombres dans le cadre de son programme. Une grandeur ( avec une unité associée ) comme une longeur, un temps ... pourra également être attribuée, pour remettre à l'échelle cette valeur, et lui donner une interprétation en fonction du contexte voulu par l'utilisateur.

### Fichier de configuration

Le fonctionnement de la librairie nécessite le chargement d'un fichier de config (par défaut nommé _abstractFeatures.glib_ ) qui contient plusieurs champs. La lecture du fichier de configuration utilise la bibliothèque [libconfig](https://github.com/hyperrealm/libconfig). 

#### Features abstraites 

Le `setting` ( voir libconfig ) *abstractFeatures* est obligatoire et permet de charger les _features_ définies par l'utilisateur. Le terme _abstrait_ se rapporte au fait que les _features_ écrites par l'utilisateur sont des templates de feature. Chaque feature abstraite peut être utilisée pour créer différentes features. Une feature abstraite se déclare à l'aide de plusieurs champs :

- **`label`** [**obligatoire**] [`string`] : nom abstrait associé à la feature. Il permet à l'utilisateur de désigner la feature dans le programme. Un nom sera ensuite défini dans un second temps lorsque la feature sera utilisée. Ainsi une feature abstraite avec un label peut servir de base pour plusieurs features. 
- **`nature`** [**obligatoire**]  [`string`]: une feature peut etre discrète (`"Discrete"` ou `"D"` ), elle ne peut prendre que plusieurs valeurs définies par l'utilisateur, ou continue (`"Continuous"` ou `"C"` ), elle peut prendre n'importe qu'elle valeur sa valeur min et sa valeur max. Par exemple 
```
abstractFeatures=(
{ label = "color" ;
  nature = "Discrete" ;
}
```
indique que l'on déclare une feature abstraite "color" qui ne peut prendre que des valeurs discretes.
- **`nGenes`** [**obligatoire**][`int`] : nombre de gènes sur lequel est codée la feature. Un minimum de trois gènes permet d'obtenir une bonne variété de phénotypes avec un jeu d'allèles réduit (ces points sont abordés dans la section Statistiques et analyse du modèle ).
- **`alleles`** [**optionnel**][`list int`] : énumération des allèles disponibles pour la feature. Les allèles sont des entiers allant de 0 à 9 (inclus). Par exemple `alleles = (0,3,9) ;` indique que chaque gène codant pour la feature pourra être une allèle 0, 3 ou 9.
- **`codRules`** [**optionnel**][`list string`] : déclaration des règles de co-dominance entre allèles d'une même paire. Si elles ne sont pas spécifiées les règles seront générées selon soit par un comportement par défaut ( aléatoire ) soit suivant une option définie par l'utilisateur. Par exemple `3-1=3`déclare que l'allèle `3`domine toujours l'allèle `1`. Cinq options existent pour définir les règles entre allèles de manière automatique : 
     - `random` : tous les coefficients sont des tirages aléatoires dans une distribution uniforme dans l'intervalle [0:1]
     - `increase:gradual`: les allèles les plus élevées dominent toujours les allèles les plus faibles (voir tableaux ci-dessous)
     - `increase:strict`: les allèles les plus élevées dominent toujours les allèles les plus faibles de manière stricte, si `a<b`alors `c(a,b)=0`
     - `decrease:gradual`: les allèles les plus faibles dominent toujours les allèles les plus élevées (voir tableaux ci-dessous)
     - `decrease:strict`: les allèles les plus élevées dominent toujours les allèles les plus faibles de manière stricte, si `a<b`alors `c(a,b)=1`
     
    
Voici résumés sous forme de tableaux les valeurs des coefficients de codominance générés avec les options disponibles. Les tableaux sont générés pour une _feature_ continue avec les allèles `(1,2,3,4)`, avec la syntaxe 

|   | `b` 
| - | - |
 | `a` | `c(a,b)` |
 
 et `c(a,b)=1-c(b,a)`par définition.
 
Option : `codRules=("increase:strict")`, ci-dessous

|   | `1` | `2` | `3` | `4` |
| - | - | - | - | - | 
| **`1`** | 1 | 0 | 0 | 0 |
| **`2`** | - | 1 | 0 | 0 |
| **`3`** | - | - | 1 | 0 |
| **`4`** | - | - | - | 1 |

Option : `codRules=("increase:gradual")`, ci-dessous

|   | `1` | `2` | `3` | `4` |
| - | - | - | - | - | 
| **`1`** | 1 | 0.2 | 0.1 | 0 |
| **`2`** | - | 1 | 0.1 | 0 |
| **`3`** | - | - | 1 | 0 |
| **`4`** | - | - | - | 1 |

Option : `codRules=("decrease:gradual")`, ci-dessous

|   | `1` | `2` | `3` | `4` |
| - | - | - | - | - | 
| **`1`** | 1 | 0.8 | 0.9 | 1 |
| **`2`** | - | 1 | 0.9 | 1 |
| **`3`** | - | - | 1 | 1 |
| **`4`** | - | - | - | 1 |

Option : `codRules=("decrease:strict")`, ci-dessous

|   | `1` | `2` | `3` | `4` |
| - | - | - | - | - | 
| **`1`** | 1 | 1 | 1 | 1 |
| **`2`** | - | 1 | 1 | 1 |
| **`3`** | - | - | 1 | 1 |
| **`4`** | - | - | - | 1 |


Dans le cas d'une _feature_ discrète, les options `increase:gradual`et `decrease:gradual` fournissent des coefficients de co-domination à interpréter comme une probabilité de domination d'une allèle sur l'autre. Par exemple, dans l'exemple ci-dessus de `codRules=("decrease:gradual")` `c(1,2)=0.8`signifie que l'allèle `1` domine l'allèle `2`dans 80% des cas où l'évaluation est faite. 


Plusieurs syntaxes se retrouvent dans l'écriture des règles de co-dominance détaillées dans le paragraphe suivant.

#### Syntaxe des règles de codominance

Une règle de codominance, ou `Rule`, détermine le rapport entre deux allèles du même gène lorsque celui-ci est évalué pour calculer la `value` de la _feature_.

Chaque `Rule` a un nombre flottant appelé **`domination`** . Dans le cas d'une feature de nature discrete `domination` est équivalent à _probabilité d'expression_ ,  dans le cas d'une feature de nature continue `domination` est équivalent à _contribution (en % ) a l'expression totale_. Dans les deux cas, `domination` est un nombre flottant strictement compris entre 0 et 1. Seule son interprétation est différente selon la nature. 

Une `Rule` s'écrit de sous la forme `alleleA-alleleB=expression`où `expression`est une syntaxe propre à chaque nature de feature. Le terme de gauche correspond aux deux allèles pour lesquelles on déclare la règle, ils sont reliées par un caractère `-` . Le terme de droite donne le résultat de l'expression des deux allèles si elles se retrouvent dans une même paire. 

**Les règles de co-dominance, si elles sont écrites par l'utilisateur, doivent couvrir l'ensemble des combinaisons d'allèles possibles sinon un message d'erreur sera affiché et l'execution du programme arrêtée.**

#### Cas d'une feature Discrete
Dans le cas d'une feature discrete deux syntaxes sont possibles : 
``` 
alleleA-alleleB=alleleA
```
signifie que `alleleA`est dominante et que `alleleB`est récessive.  On peut également souhaiter voir `alleleA` dominer `alleleB` dans certains cas et non dans d'autres, avec une certaine probabilité. Dans ce cas on pourra écrire
``` 
alleleA-alleleB=p0.3
```
où `p0.3`signifie que `alleleA` domine `alleleB`dans 30% des cas, c'est à dire dans 30% des cas où l'expression de la feature est évaluée, c'est une expression probabiliste. **La probabilité s'applique toujours a l'allèle déclarée en premier.**

La première syntaxe permet une écriture plus intuitive des règles de domination entre allèles. Lorsque l'on écrit `alleleA-alleleB=alleleA` cela est ensuite traduit en `alleleA-alleleB=p1`. 

#### Cas d'une feature Continue
Dans le cas d'une feature continue une seule syntaxe est possible : 
```
a-b=c(a,b)
```
où `c(a,b)`, ou `domination`, est un nombre flottant **strictement compris entre 0 et 1.** 
Par exemple `1-3=0.3`indique que l'allèle `1` contribue à 30% à l'expression de la feature, et que l' allèle`3` contribue à 70%.



**La syntaxe n'est pas permissive. Si une règle est déclarée pour deux allèles qui ne sont pas présentes dans _alleles_ une erreur sera émise.**

## Contribution des allèles et calcul de l'expression d'une _feature_

Chaque allèle, un entier compris entre `0` et `9`, contribue de manière égale à leur propre valeur.

Les coefficients de codominance, ou `domination` sont obligatoirement compris entre 0 et 1. 

Chaque _feature_ a une valeur (interprétée par l'utilisateur) , `value` comprise entre -1 et +1 si elle est continue, ou égale à un entier compris entre 0 et 9 si elle est discrète.

Par exemple, pour une _feature_ continue codée uniquement sur un gène, et celui ci n'ayant que deux allèles `a` et `b`, la valeur de la feature est donné par

` value = (1-c(a,b)) * valeur_a + c(a,b) * valeur_b`

 Si l'on reprend l'exemple précédent d'une feature continue codée sur un gène avec deux allèles `1`et `3`ayant pour règle de co-dominance `1-3=0.3` , la `value` de la _feature_ est donnée par `value = 0.3 * 1 + (1 - 0.3) * 3 = 2.4` . Cette valeur est comprise entre 0 et 9, elle est ensuite normalisée pour être comprise entre -1 et 1.

Lorsqu'une feature est codée sur plusieurs gènes, la `value`de la feature s'exprime sous la forme

TODO : WRITE EQUATION Latex???


Pour le cas d'une _feature_ discrète ... TODO


Voici un exemple complet d'un fichier de configuration avec trois features, deux discrètes et une continue : 
```
abstractFeatures=(
 { label = "size" ;
   nature = "Discrete" ;
   nGenes = 1 ; 
   codRules = ("random") },
   
{ label = "color";
  nature = "D" ;
  nGenes = 1 ;
  alleles = (1 , 2 , 3 );
  codRules = ( "2-1=p0.2", "1-3=3", "3-2=3"); },

{ label = "plumage" ;
  nature = "C" ;
  nGenes = 1 ;
  alleles = (0,3,9);
  codRules = ("0-9=0. ", "3-0=0.9", "3-9=0.3",); } );
```

## Structure des gènes

Chaque gène est un tableau d'entiers de dix bases nucléiques en binaire. La contribution d'un gène a la valeur macroscopique est donnée par la somme de ces bases (chaque base apportant 1 ou 0 a la contribution totale). Par exemple l'allèle `6` peut être représentée sous la forme d'une séquence `1110110010`, où la position des `1`et des `0` est aléatoire. La contribution d'une allèle a l'expression d'une paire de gènes est donc égale à la somme des bases nucléiques qui composent le gène.


## Paramètres de contrôle de la population initiale d'allèles  TODO

Notes : Controle de la gaussienne vers des valeurs extremes, poids associé a chaque allele (rareté, abondance)

## Fonctionnement de la librairie TODO

### Description des classes 

## Utilisation de la librairie : exemple TODO

## Analyse du modèle génétique TODO

### Lois d'échelle 
La diversité d'un trait (nombre de combinaisons possibles) varie proportionnellement au nombre d'allèles par gene, en puissance avec la ploidie (ici seulement diploide), et en puissance avec le nombre de gènes pour un trait phénotypique. 

Le nombre de chromosomes sur lesquels sont répartis les genes contribue au brassage génétique. Il permet a un nombre fixé de variations pour chaque trait d'augmenter le nombre de phénotypes (ensemble des traits) accessibles à la descendance.

Enfin le crossing over ayant lieu durant la méïose augmente encore la portée du brassage génétique et de la diversité phénotypique pour un genome donné. Pour augmenter rapidement le spectre des valeurs prises par un trait, et s'approcher d'une distribution continue, il est recommandé d'associer plusieurs gènes à un trait (voir paragraphe suivant)

### Considérations statistiques
#### Influence du nombre de gènes
TODO : arrivée au théorème central limit (nombre de genes par feature)
#### Influence du nombre d'allèles et des coefficients

