<h3 id="epigenetique">Épigénétique</h3>

<p>
    On pourrait introduire ici une notion "épigénétique", avec des caractères héréditaires non encodés dans le génome sous la forme très simple d’un état transmissible (un ensemble de clé/valeurs) de génération en génération. Cet état mutable viendrait s'ajouter à l'état "génome" d'un individu.
</p>
<p>
    Cet état est accessible en écriture/lecture à des features spécifiques. Comme montré sur le schéma, une feature qui utiliserait cet état interne devrait le déclarer. En effet, on fait ici une exception à la règle d'or de notre design, que <a href="#immutability">les features sont des fonctions pures</a>. Une feature qui utiliserait l'état "épigénétique" cesserait d'être pure, elle produirait un effet de bord et changerait l'état du monde. Ce qui provoque des couplages indésirés entre features.
</p>
<p class="question">
    L'état épigénétique serait simplement une collection de clé:valeur mutables, et transmissible à la descendance. Quelles contraintes à mettre dessus ? Dans le cas d'une reproduction sexuée comment l'épigénétique de 2 parents se combinent pour être transmis ? Concaténation des clefs:valeurs? Est-ce vraiment une bonne idée (j'ai des doutes) ?
</p>