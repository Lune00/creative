# GENOMLIB

## Objectifs

**Ce projet n'a pas pour but de simuler les mécanismes génétiques mais de les modéliser**, en reproduisant les mécanismes généraux ayant lieu lors de la reproduction afin d'obtenir une variété de phénotypes satisfaisante.

Le but de ce projet est de fournir une bilbliotheque minimale pour mettre en place un génome [diploïde](https://fr.wikipedia.org/wiki/Diploïde) transmissible et ses mécanismes génétiques associés: transmission d'un matériel génétique, de generation en generation, s'exprimant en "traits" (_features_) ou phénotype.

Le **genome** peut-être hérité par une classe qui disposer d'un matériel génétique avec des regles d'expression définies par l'utilisateur. 

## Description

La librairie modelise les caractères rudimentaires et simplifiés de la génétique: population initiale de genes ( et d'alleles), régles de codominance entre allèles d'un meme gene, transmission par méiose. 

Toute instanciation d'une classe héritant de *genome* peut se reproduire avec une instanciation de sa propre classe ou une instanciation d'une classe héritant du meme genome. La reproduction peut se réaliser avec un partenaire (sexuée ou non), par clonage ou par auto-fécondation (comme certaines plantes). 

Chaque trait phénotypique (taille, couleur des yeux ...) peut-être codé par un ou plusieurs gènes. Chaque gène peut posséder un ou plusieurs allèles.

Les règles de codominance entre allèles peuvent être initialisés par l'utilisateur. 

Le phénotype est calculé selon les regles de codominance (expression du genome). Ce génome est ensuite transmis lorsque deux individus se dupliquent ( sans partenaire) ou procréent (avec un partenaire) . Dans le cas d'une reprodution, et non d'une duplication (mitose) un processus de [méiose](https://fr.wikipedia.org/wiki/Méiose) est simulé: une partie du génome (un chromosome au hasard sur les deux si diploide) est transmis par chaque parent a l'individu enfant. L'enfant dispose d'un genome hérité de ses parents et peut le transmettre à son tour. Le [crossing-over](https://fr.wikipedia.org/wiki/Enjambement_(génétique)) pourra être activé par l'utilisateur. 

Pas d'épigénétique pour le moment (rétroaction des traits ou de l'environnement de l'individu sur son genome).

Il serait inutile de complexifier le modèle avec l'ajout de mécanismes trop spécifiques alors que des mécanismes essentiels dans l'expression du génome ne sont pas pris en compte. Aussi nous restreindrons le modèle aux propositions suivantes. L'auteur de la libraire en juge la complexité suffisante pour obtenir un brassage génétique qui permette à la fois d'explorer la variabilité des phénotypes, de ressentir l'hérédité d'une génération à l'autre, et d'instaurer des mécanismes de sélection intéressants:

- Chaque trait est codé macroscopiquement par une valeur dans un intervalle [-1:1]. Une valeur min et max seront définies par l'utilisateur,une unité (m, kg) pourra également etre atribuée, pour remettre à l'échelle cette valeur et lui donner une interprétation en fonction du contexte voulu par l'utilisateur.
- Deux natures de trait sont disponibles: continu (sa valeur est continue, elle peut prendre n'importe quelle valeur entre -1 et 1, comme la taille) et discret ( sa valeur est discrete et entiere, elle ne peut prendre que certaines valeurs spécifiques)
- Chaque trait sera codé par un ensemble de gènes (pouvant etre égal à 1 jusqu'à 50).
- Les ensembles de genes codant pour un trait seront placés aléatoirement sur les chromosomes. Le nombre de chromosomes doit être égal ou inférieur au nombre total de gènes (de sorte qu'il y ait au moins un gène par chromosome).
- Chaque gène est un tableau de 20 bases nucléiques binaires (0 ou 1). La contribution d'un gène a la valeur macroscopique est donnée par la somme de ces bases (chaque base apportant 0.1 a la contribution totale). Ensuite on soustrait 1 à la somme pour obtenir une contribution au trait macroscopique dans l'intervalle [-1:1] 
- le crossing-over pourra être désactivé ou activé (si désactivé réduit la meiose a une recombinaison des chromatides)
- a compléter

Un programme (avec interface graphique) sera fourni pour générer les propriétés de la base génétique dans un fichier .gnm


### Fonctionnement des genes et regles d'expression:

Chaque **trait** (phénotypique) a une valeur comprise entre -1 et +1. Chaque allèle a une contribution au trait, un effet, compris entre -1. et 1. Les coefficients de codominance sont obligatoirement compris entre 0 et 1. Par exemple, pour un gene ayant 2 allèles *a* et *b*, le trait est donné par

trait = (1-c(a,b)) * effet allèle a + c(a,b) * effet allèle b

où c(a,b) est le coefficient de codominance entre a et b. Quand c est égal à 0, a est dominant et b est récessif. Dans le cas où plusieurs gènes contribuent à un seul trait leurs contributions sont sommées.


## Diversité phénotypique : lois d'échelle et considérations statistiques

La diversité d'un trait (nombre de combinaisons possibles) varie proportionnellement au nombre d'allèles par gene, en puissance avec la ploidie et en puissance avec le nombre de gènes pour un trait phénotypique. Le nombre de chromosomes sur lesquels sont répartis les genes contribue au brassage génétique. Il permet a un nombre fixé de variations pour chaque trait d'augmenter le nombre de phénotypes (ensemble des traits) accessibles à la descendance. Enfin le crossing over ayant lieu durant la meiose augmente encore la portée du brassage génétique et de la diversité phénotypique pour un genome donné. Pour augmenter rapidement le spectre des valeurs prises par un trait, et s'approcher d'une distribution continue, il est recommandé d'associer plusieurs gènes à un trait. Un billet de blog sera bientôt disponible dans lequel ces effets seront discutés.

## Contenu / classes
Le programme se compose des classes suivantes:

- **Gene** : un gene est défini par sa position sur le **Chromsome**. Il a une valeur *allele* qui correspond à sa version et un *trait* qui correspond à la valeur qu'il attribue (compris entre -1. et 1.), s'il domine (coefficient de codomination de 1) au trait phénotypique associé. 
- **Chromosome**: un chromosome est un conteneur de gènes. La position de chaque gène sur le chromosome determine pour quel trait phénotypique il code.
- **Geneticien**: contient le nombre de chromosomes dans le génome, la population de genes (leurs version, ou alleles) ainsi que les regles de codominance entre alleles (qui **doivent** etre spécifiées).
- **Genome** : le genome peut-être instancié en soi, il fonctionne comme un *sac à gênes* indépendant. Il contient l'ensemble des chromosomes, un sexe, des informations sur les parents et descendants, et un phénotype. 
- **rng** : un simple générateur aléatoire de nombres entier et flottants.
