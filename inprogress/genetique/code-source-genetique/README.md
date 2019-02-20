---------------------------  BUT DU PROGRAMME --------------------------------

Heritage de traits personnels encodés par des genes Un couple de personnages donnera naissance a des enfants qui heriteront de leurs genes.  Pour definir les traits on utilisera le modele OCEAN (5 traits de personalité) => 5 genes

source : https://fr.wikipedia.org/wiki/Modèle_des_Big_Five_



Chaque trait a une valeur comprise entre -1 et +1.

La transmission se fait 
---------------------------  BUT DU PROGRAMME --------------------------------

Modele 0: l'ensemble des genes sera sur un seul chromosome. Relation de dominance entre alelles

 Modele 0.a: un meme trait phénotypique (O) peut etre codé par 3 genes (avec chacun leur allele) : Oa(allele Oa1 Oa2...) Ob Oc
 Trait = (1-coeffDominance)*effet allele A(gene1) + coeffDImance*effet allele B(gene1)  
       + (1-coeffDominance)*effet allele A(gene2) + coeffDImance*effet allele B(gene2)
       / par nombre de genes impliques
 -> Approche de distribution + continue

Modele 1: introduire des mutations

Modele 2: mettre les genes sur differents chromosomes pour enrichir le brassage

1: Generer des couples homme/femme avec chacun : un nom,un prenom, un chromosome avec genes aleatoires (voir dans le dossier data)

//--------------
  // Il faut que chaque allele ait un effet fixe (rapport de domination avec l'autre)
  // Attribuer a chaque allele un coefficient de dominance vis a vis d'un autre (allele C1 face a C2 peut se comporter autrement)
  // L'expression d'un gene ne serait plus "dominant" ou "recessif" (un booleen) mais une valeur flottante comprise entre [0:1]
  // Si un trait est codé par un gene et 
  // une relation de dominance entre allele A et B : Trait(valeur) = (1 -coeff dominance)* Effet allele A + (Coeff dominance)* Effet allele B
  // Faire une table de coeff dominance. Ex gene C: allele C1 C2 C3 CoeffDominance(C1,C2)=0 -> C1 domine C2 completement. CoeffDominance(C1,C3)=1 -> C3 domine C1 completement


//Variable global, tmp
//Le caractere est defini seulement par la position dans le vecteur de genes "genes_" de l'objet Chromosome
//               0  1  2  3  4
//Seul des genes de meme caractere peuvent etre mis en rapport (correspond a la position dans le chromosome)

//enum Caractere { O, C, E, A, N } ;

