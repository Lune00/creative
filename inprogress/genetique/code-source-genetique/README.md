# GENETIK

## Objectifs

Le but de ce code est de fournir une bilbliotheque minimal pour mettre en place des mécanismes génétiques, a savoir la transmission, de generation en generation de "traits", un phénotype, a partir d'un materiel génétique.

Les **individus** ont un génome qui se compose de deux **chromosomes**, ils sont diploides. Sur chaque chromosome il existe un certain nombre de genes qui peuvent avoir des alleles différentes. Chaque trait phénotypique est codé par un gène qui existe sous la forme de deux alleles (un sur chaque chromosome). Des règles de codominance viennent pondérer l'expression des gènes correspondant au même trait. 

Il est possible de choisir le nombre de gènes et le nombre de traits. Il faut seulement écrire les regles de codominance correspondantes. Une base d'alleles pour chaque gène est initialisée au début du programme. La population de genes est initialement écrite puis elle sera transmise.

Le phénotype est ensuite calculé selon les regles de codominance (expression du genome). Ce génome est ensuite transmis lorsque deux individus de sexe opposé procreent. Comme dans un processus de [méiose](https://fr.wikipedia.org/wiki/Méiose) la moitié du génome (un chromosome au hasard sur les deux) est transmis par chaque parent a l'individu enfant. L'enfant dispose d'un genome hérité de ses parents et peut le transmettre à son tour.

A l'avenir une classe **Vivant** sera créee qui contiendra toute l'information génétique, qui sera héritée par une classe qu'un utilisateur veut voir etre dotée d'un systeme génétique.


## Contenu / classes
Le programme se compose des classes suivantes:

- **Gene** : un gene est défini par sa position sur le **Chromsome**. Il a une valeur *allele* qui correspond à sa version et un *trait* qui correspond à la valeur qu'il attribue, s'il domine (coefficient de codomination de 1) au trait phénotypique associé. 
- **Chromosome**: un chromosome est un conteneur de gènes. La position de chaque gènes sur le chromosome determine pour quel trait phénotypique il code.
- **Geneticien**: contient la population de genes (leurs version, ou alleles) ainsi que les regles de codominance entre alleles (qui doivent etre spécifiées). Le Geneticien fixe le nombre de gene. C'est une classe interface où les regles de la génétique sont regroupées.
- **Individu**: les etres diploides (possedent deux chromosomes). Ils héritent d'un génome, qui determine leur phénotype,peuvent le transmettre et avoir une filiation. Ils ont un sexe. Ils ont un nom et un prénom tirés au hasard dans des fichiers textes présents dans le dossier **data**. Pour l'instant un individu a un phénotype constitué de 5 traits psychologiques (voir section suivante). Ils seront remplacés par une classe générique **Vivant** par la suite dont l'utilisateur pourra hériter pour faire des invidius *génétisés* comme bon lui semble)
- **rng** : un simple générateur aléatoire de nombres entier et flottants.

Pour l'instant chaque trait est codé par un seul gène (qui peut exister sous differentes versions ou alleles). A titre d'exemple, 5 traits avec 5 genes correspondants, avec 3 alleles differents pour chaque gène, donne 6x6x6x6x6 combinaises possibles, soit un peu plus de 7600 phénotypes.

## Fonctionnement des genes et regles d'expression:

Chaque trait a une valeur comprise entre -1 et +1.

## Phénotype intégré (amené a changer)

Les traits (ou phénotype) de chaque individu sont au nombre de 5. Utilisation du modele [**OCEAN**](https://fr.wikipedia.org/wiki/Modèle_des_Big_Five_)


Modele 0: l'ensemble des genes sera sur un seul chromosome. Relation de dominance entre alelles

 Modele 0.a: un meme trait phénotypique (O) peut etre codé par 3 genes (avec chacun leur allele) : Oa(allele Oa1 Oa2...) Ob Oc
 Trait = (1-coeffDominance)*effet allele A(gene1) + coeffDImance*effet allele B(gene1)  
       + (1-coeffDominance)*effet allele A(gene2) + coeffDImance*effet allele B(gene2)
       / par nombre de genes impliques
 -> Approche de distribution + continue

Modele 1: introduire des mutations

Modele 2: mettre les genes sur differents chromosomes pour enrichir le brassage

1: Generer des couples homme/femme avec chacun : un nom,un prenom, un chromosome avec genes aleatoires (voir dans le dossier data)

  // Attribuer a chaque allele un coefficient de dominance vis a vis d'un autre (allele C1 face a C2 peut se comporter autrement)
  // L'expression d'un gene ne serait plus "dominant" ou "recessif" (un booleen) mais une valeur flottante comprise entre [0:1]
  // Si un trait est codé par un gene et 
  // une relation de dominance entre allele A et B : Trait(valeur) = (1 -coeff dominance)* Effet allele A + (Coeff dominance)* Effet allele B
  // Faire une table de coeff dominance. Ex gene C: allele C1 C2 C3 CoeffDominance(C1,C2)=0 -> C1 domine C2 completement. CoeffDominance(C1,C3)=1 -> C3 domine C1 completement


