# Documentation : Modèle génétique / démographique
22/02/2021
version 1

## Préambule


## Ce qu'on fabrique

Construire une bibliothèque que n’importe qui peut installer et utiliser dans ses propres projets informatiques. Cette bibliothèque est constituée d’un moteur (un ensemble de fonctions implémentant le modèle) ainsi que de données (avec un format bien défini) exportables et importables. Ainsi, les utilisateurs pourront partager leurs données entre eux (design du génome, des traits phénotypiques et des espèces) et une communauté *pourrait* se former construisant petit à petit des designs de plus en plus élaborés. L'idée c'est qu'on pourra construire à partir de ce qu'on a construit.

Pour permettre cela tout en étant _user-friendly_ des éditeurs avec interface graphique seront développés :

 - Un éditeur de [support génétique](#support-génétique)
 - Un éditeur de [traits phénotypiques](#features)
 - Un éditeur d’[espèces](#espèces)
 - Un bac à sable pour tester et explorer rapidement ses designs
    
Les 3 éditeurs permettront d’éditer, importer, exporter, dupliquer, supprimer, ces 3 type de données facilement. Ces données seront ensuite importées dans le projet informatique de l’utilisateur et celui-ci, après import du moteur, pourra faire tourner le modèle dans le but qu’il s’est fixé.

## Objectifs

S’amuser. Fournir un moteur permettant de simuler des entités (biologiques ou non) possédant des caractéristiques (traits phénotypiques) **interprétables par l’utilisateur**. Ces caractéristiques sont le résultat de l’évaluation d’un support génétique (principalement). Les entités pourront se reproduire et transmettre à leur descendance une part de leur génome pour créer de l’hérédité, de la filiation (et de l’histoire). Ce génome pourra également être soumis à des mutations et évoluer. L’utilisateur pourra alors facilement simuler de la sélection et des populations au cours du temps dans son propre projet. Les espèces pourront muter, les populations évoluer etc. En somme un gros bac à sable. Ce modèle pourrait avoir des ambitions plus générales. Car s'il vise principalement à simuler *de la vie*, le moteur pourrait être appliqué à d’autres *objets*. On peut penser par exemple à faire une filiation de langues (en utilisant des méthodes de [philologie comparée](https://fr.wikipedia.org/wiki/Philologie) comme a pu le faire (sérieusement) Tolkien : utiliser des règles spécifiques de mutation qui permette de passer d’un mot ancêtre à un mot descendant et vice versa). En fait tout ce qui est sujet à itérations successives, tout objet qui« produit du nouveau a partir de lui même » pourrait être simulé.

## Contraintes

La contrainte forte du modèle c’est qu’il faut définir à l’avance des traits phénotypiques auxquels l’utilisateur pourra donner **du sens**. J’insiste là dessus car le but est de pouvoir **interpréter fonctionnellement les évaluations des phénotypes pour prendre des décisions.** Ce que j’entends par là c’est que si une espèce possède un trait phénotypique qui renvoie la valeur ‘foo’ il faut que cette valeur **puisse** (pas nécessairement) avoir un sens pour l’utilisateur dans son programme. En ce sens, les traits phénotypiques doivent être définis dès le départ et le réservoir de phénotypes possibles doit pouvoir être contrôlé. 
## Composants à développer
![Composants](https://drive.google.com/uc?id=1LiLkUmuycQITKunBMoSPpDgZOITIaVWd)
Le projet se compose des composants suivants à concevoir et développer :

 - Les structures de données :
	 - Support génétique
	 - Feature (traits phénotypiques)
	 - Espèce
 - Les éditeurs graphiques (web) pour les éditeurs de données:
 - Un bac à sable pour aider à prototyper et tester ses designs
 - Le moteur (toutes les fonctions, dépendances qui implémentent le modèle)

Les structures de données seront complexes et un éditeur graphique pour les manipuler sera (quasi) indispensable. Ces éditeurs permettront d'importer et d'exporter les données facilement, de les éditer, dupliquer, supprimer. Le modèle est *piloté par les données*, ces structures sont capitales et doivent être manipulées et définies de manière rigoureuses.

## Aperçu général du modèle génétique : du génome au phénotype

L'utilisateur de la bibliothèque pourra faire évoluer des populations d'individus possédant un phénotype, ou un ensemble de traits observables et mesurables. L'utilisateur pourra évaluer les traits de chaque individu et leur appliquer le traitement qu'il souhaite. Ces traits seront l'expression d'un génome **diploïde** porté par chaque individu, transmissible par reproduction ou clonage de génération en génération.

Le *support génétique* (encodé en binaire) lorsqu'il est évalué produit une valeur. Cette valeur est ensuite interprétée par une *feature* qui produit à son tour une valeur auquel l'utilisateur donne une unité de mesure. L'expression de la feature est alors remontée dans le phénotype, le résultat de l'évaluation de toutes les *features* de l'individu. La valeur en sortie d'une feature peut servir d'entrée à une autre *feature* et ainsi de suite. Ainsi, l'expression du phénotype forme une collection de couples {valeur, unité} produite par l'évaluation successive du support génétique puis des features.

Lors de la reproduction ou du clonage, le support génétique est transmis à l'aide de mécanismes connus de la biologie (mais nécessairement simplifiés) : mitose, méiose.

Le support génétique pourra être exposé à des mutations. Chaque individu disposera en plus de son support génétique d'un état interne modélisant les effets *épigénétiques*. Cet état supplémentaire, non encodé dans le génome, pourra modéliser la transmission de caractères acquis.

## Notations
(...) : collection non ordonnée
[ ] : tableau
[a-b] : allèles a et b sur le même locus d'une paire de chromosomes analogues 

## Les modèles de données

### Support génétique 

Un support génétique est une séquence en binaire (de 0 et de 1) qui peut être évalué pour **produire des valeurs** entières. 

<table>
    <thead>
        <tr>
            <th colspan="4">Support génétique</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th>Paramètre</th>
            <th>Description</th>
             <th>Type</th>
              <th>Contraintes</th>
        </tr>
    <tr>
            <td>Nom</td>
            <td>Un nom donné au support</td>
            <td>String</td>
             <td>Unique</td>
        </tr>
        <tr>
            <td>Nombre de gènes <code>N</code></td>
            <td>Nombre de gènes contribuant à la valeur du support</td>
             <td>Integer</td>
               <td>>= 1</td>
        </tr>
          <tr>
            <td>Nombre de bits <code>n</code></td>
            <td>Nombre de bits sur lequel est encodé chaque gène du support : l’utilisateur pourra choisir d’encoder des gènes sur des structures allant de 1 à 8 bits (limite arbitraire). Ce paramètre défini par défaut le nombre de variations d’un même gène (allèles) accessibles. Par exemple, sur un support à 2 bits on a 4 valeurs possibles : 00 (0), 01 (1), 10 (2) et 11 (3). On a donc, au maximum 4 allèles pour ce gène dans notre « réservoir ». Sur 8 bits on a 256 valeurs possibles, donc 256 allèles possibles pour un même gène. La structure binaire est suffisante pour créer assez de variations (pas besoin de 4 caractères AGCT). </td>
             <td>Integer</td>
              <td><code>n</code>>=1 et <code>n</code>< 8</td>
        </tr>
                  <tr>
            <td>Allèles disponibles <code>n<sub>a</sub></code></td>
            <td>La population d'allèles est par définition produite par le nombre de bits sur lequel est encodé un gène. C’est le réservoir par défaut. L’utilisateur pourra décider de n’utiliser qu'un sous-ensemble de ce réservoir s’il le souhaite. <strong>Une allèle est une valeur</strong> possible d'un gène. Elle peut donc muter dans l'espace défini par le gène vers une autre valeur. </td>
             <td>(Integer...)</td>
              <td><code>n<sub>a</sub></code> >=1 et <code>n<sub>a</sub></code> < N<sup>2</sup> </td>
        </tr>
         <tr>
            <td>Relations entre allèles <code>U</code></td>
            <td>Tableau de coefficients dont chaque valeur permet de calculer la contribution de chacune des 2 allèles du même gène à l’évaluation du support génétique. L’utilisateur pourra générer ces coefficients de manière aléatoire ou suivant des règles prédéfinies, ou les écrire manuellement (il y a toujours le contrôle total si on le souhaite).</td>
             <td>[Float]</td>
              <td>
              <ul>
              <li>Nombre de coefficients = n<sub>a</sub> (n<sub>a</sub> +1)/2 pour évaluer toutes les combinaisons possibles
              </li>
              <li>valeurs comprises entre 0 et 1</li>
              </ul>
              </td>
        </tr>
         <tr>
            <td>Nature</td>
            <td>
 <ul>
              <li><strong>Discret : </strong> une seule allèle s'exprime (remonte), l'évaluation produit uniquement des valeurs discrètes. Utile pour modéliser une expression booléenne ou un ensemble prédéfini de valeurs (ex: une liste de couleurs, absence ou présence etc...) 
              </li>
              <li><strong>Continu : </strong>toutes les valeurs s'expriment, l'évaluation du support produit des valeurs dans un spectre continu (ex : taille d’un membre). En fonction des contributions de chaque allèle l’évaluation pourra prendre n’importe qu’elle valeur dans l'intervalle défini par le nombre de bits</li>
              </ul>
		</td>
             <td>String</td>
              <td>2 valeurs possibles : 'discrete' ou 'continuous'</td>
        </tr>
    </tbody>
</table>

Pour résumer, l'évaluation d'un support génétique (et la production d'une valeur) se fait en évaluant pour chacun de ses gènes la paire d'[allèles](https://fr.wikipedia.org/wiki/All%C3%A8le) (une allèle sur chaque [chromosome homologue](https://fr.wikipedia.org/wiki/Chromosome_homologue)) correspondante. Les règles de codominance et la nature permettent de calculer la **valeur** du support génétique.

#### Exemple : support génétique continu
Prenons un support génétique :

 - codé sur 3 gènes
 - chaque gène est codé sur 2 bits
 - nature : 
 - Allèles disponibles : toutes, soit 
	 - 00 ( a )
	 - 01 ( b )
	 - 10 ( c )
	 - 11 ( d )

Initialisons le tableau des relations entre allèles :

<table>
    <tbody>
        <tr>
            <td></td>
            <td>a</td>
             <td>b</td>
            <td>c</td>
             <td>d</td>
        </tr>
        <tr>
            <td>a</td>
            <td>1</td>
             <td>0.3</td>
            <td>0.7</td>
             <td>1</td>
        </tr>
          <tr>
            <td>b</td>
            <td>-</td>
             <td>1</td>
            <td>0.2</td>
             <td>0.4</td>
        </tr>
        <tr>
            <td>c</td>
            <td>-</td>
             <td>-</td>
            <td>1</td>
             <td>0.5</td>
        </tr>
         <tr>
            <td>d</td>
            <td>-</td>
             <td>-</td>
            <td>-</td>
             <td>1</td>
        </tr>
    </tbody>
</table>

avec <code>u(i,j)</code> le coefficient de codominance entre l'allèle i et j. Par exemple <code>u(a,b) = 0.3</code> signifie (dans le cas continu) que les allèles a et b d'un même locus (d'une paire de chromosomes analogues) vont contribuer respectivement à 30% et à 70% de l'évaluation du gène. 

Notons <code>a-b</code> deux allèles sur le même locus, son évaluation donne <code>u(a,b)0 + u(b,a)1 = 0.7</code> (*a*=0 et *b*=1)

On a par définition (normalisation)

    u(j,i) = 1 - u(i,j) 

Évaluons à présent un individu qui posséderait un support génétique initialisé comme suit :

<code>(a-b)(c-b)(a-b)</code>

L'individu est [hétérozygote](https://fr.wikipeda.org/wiki/H%C3%A9t%C3%A9rozygote) pour chacun des 3 gènes.

### Features

code pour une _feature_ (ou trait phénotypique, même chose), qui sera définie ultérieurement par l’utilisateur. Un même support peut être réutilisé pour plusieurs features. 

### Espèces
