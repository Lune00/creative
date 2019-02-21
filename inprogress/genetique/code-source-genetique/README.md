# GENOMLIB

## Objectifs

Le but de ce projet est de fournir une bilbliotheque minimale pour mettre en place un génome transmissible et ses mécanismes génétiques associés: transmission d'un matériel génétique, de generation en generation, s'exprimant en "traits" ou phénotype.

Le **genome** peut-être hérité par une classe qui disposer d'un matériel génétique avec des regles d'expression définies par l'utilisateur. 

La librairie modelise les caractères rudimentaires et simplifiés de la génétique: population initiale de genes ( et d'alleles), régles de codominance entre allèles d'un meme gene, transmission par méiose. 

Toute instanciation d'une classe héritant de *genome* peut se reproduire avec une instanciation d'une autre classe pourvu qu'ils partagent le même génome. La reproduction peut etre définie sexuée ou non. Le nombre n de chromosomes peut etre défini par l'utilsateur. La ploïdie peut être choisie entre trois types: haploide (n chromosomes), diploide (2n chromosomes), triploides (3n chromosomes).

Chaque trait du phénotype peut-être codé par un ou plusieurs gènes. Chaque gène peut posséder un ou plusieurs allèles.

L'ensemble du matériel génétique (gènes et allèles) ainsi que les règles de codominance entre allèles doivent être initialisés par l'utilisateur une fois.

Le phénotype est calculé selon les regles de codominance (expression du genome). Ce génome est ensuite transmis lorsque deux individus se dupliquent ( sans partenaire) ou procréent (avec un partenaire) . Dans le cas d'une repdocution, et non d'une duplication (mitose) un processus de [méiose](https://fr.wikipedia.org/wiki/Méiose) est simulé: une partie du génome (un chromosome au hasard sur les deux si diploide) est transmis par chaque parent a l'individu enfant. L'enfant dispose d'un genome hérité de ses parents et peut le transmettre à son tour.

Pas d'épigénétique pour le moment (rétroaction des traits ou de l'environnement de l'individu sur son genome).


## Contenu / classes
Le programme se compose des classes suivantes:

- **Gene** : un gene est défini par sa position sur le **Chromsome**. Il a une valeur *allele* qui correspond à sa version et un *trait* qui correspond à la valeur qu'il attribue (compris entre -1. et 1.), s'il domine (coefficient de codomination de 1) au trait phénotypique associé. 
- **Chromosome**: un chromosome est un conteneur de gènes. La position de chaque gène sur le chromosome determine pour quel trait phénotypique il code.
- **Geneticien**: contient le nombre de chromosomes dans le génome, la population de genes (leurs version, ou alleles) ainsi que les regles de codominance entre alleles (qui **doivent** etre spécifiées).
- **Genome** : le genome peut-être instancié en soi, il fonctionne comme un *sac à gênes* indépendant. Il contient l'ensemble des chromosomes, un sexe, des informations sur les parents et descendants, et un phénotype. 
- **rng** : un simple générateur aléatoire de nombres entier et flottants.

## Fonctionnement des genes et regles d'expression:

Chaque **trait** (phénotypique) a une valeur comprise entre -1 et +1. Chaque allèle a une contribution au trait, un effet, compris entre -1. et 1. Les coefficients de codominance sont obligatoirement compris entre 0 et 1. Par exemple, pour un gene ayant 2 allèles *a* et *b*, le trait est donné par

trait = (1-c(a,b)) * effet allèle a + c(a,b) * effet allèle b

où c(a,b) est le coefficient de codominance entre a et b. Quand c est égal à 0, a est dominant et b est récessif. Dans le cas où plusieurs gènes contribuent à un seul trait leurs contributions sont sommées.


# Diversité phénotypique : lois d'échelle

La diversité phénotypique (nombre de combinaisons possibles) varie propoprtionnellement au nombre d'allèles par gene, en puissance avec le nombre de chromosomes et en puissance avec le nombre de gènes pour un trait phénotypique. Pour augmenter rapidement le spectre d'un trait, et approcher d'une distribution continue, il est recommandé d'associer plusieurs gènes à un trait. Un billet de blog sera bientôt disponible dans lequel ces effets seront discutés.

