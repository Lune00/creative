<h2 id="analyse">Considérations démographiques</h2>

<h3>Le modèle a une mémoire</h3>

<p>
    L'intérêt de designer le modèle sous forme d'aggrégations de valeurs, et de composition de fonctions pures, c'est qu'on peut garder mémoire de tout ce qui s'est passé au cours du temps.
</p>
<p>
    On peut reconstruire <em>toute l'histoire</em> d'un individu à partir de son état initial (son génome), du temps et des logs des mutations ! En effet, vu que tout est valeur et que rien n'est remplacé sur place (sauf le génome mais le log des mutations nous permet de retrouver toutes ses valeurs), et que toutes les features sont des fonctions pures, le système garde la mémoire de toutes les informations nécessaires pour re-dérouler le fil de l'histoire. On peut même obtenir des valeurs à des instants par lesquels n'est pas passée notre simulation.
</p>
<p>
    Regardons la puissance de cette approche (que je n'ai pas du tout inventé, beaucoup inspiré par Rich Hickey et notamment cette <a href="https://www.youtube.com/watch?v=V6DKjEbdYos&t=3043s">conférence absolument géniale</a>) sur un exemple concret, un pseudo-code (je ne vais pas détailler pour le moment comment tout ça <em>exactement</em> va être implémenté mais c'est possible !)
</p>
<code class="pseudo-code">
    <pre>
    //At time t = 102
    history = getPhenotypes(t-50, t, t, individu)
    //history contient tous les phénotypes depuis t-50 à t
    //Say this individual is born at time t=10 of our simulation
    print(history) // = [ {t:101, phenotype:{...}}, 
                          {t:100, phenotype:{...}} 
                          ...
                          {t:10, phenotype:{...}} 
                          ]

    ...
    //All phenotype history between t-50 and t-10
    history = getPhenotypes(t-50, t-10, t, individu)
    //All phenotype history
    history = getPhenotypes(individu)
    //Phenotype at time t-30 only
    history = getPhenotype(t-30, t, individu)</pre>
</code>
<p>
    Imaginons qu'on n'ai jamais évalué une seule fois notre individu, aucun phénotype n'a été mesuré et mis en entrée dans les logs. Mais est ce un problème ? Comme on a logé toutes les mutations sur son génome (s'il y'en a eu), a partir du temps, de sa date de naissance et des dates et effets des mutations on peut <em>reconstruire toute son histoire</em> jusqu'au présent !
</p>
<p>
    Évidemment cette propriété est vraie aussi pour chaque feature. On peut tracer l'histoire des valeurs mesurées d'une feature de la même manière
</p>
<code class="pseudo-code">
    <pre>
//At time t = 102. Get feature history from t-50 to now
featureHistory = getFeatureHistory(t-50, t, t, 
    individu, 'featureName')
        </pre>
</code>

<p>
    On n'est pas obligés de re-dérouler tout le fil de l'histoire jusqu'à la naissance de l'individu. On peut optimiser cette approche. On peut par exemple regarder s'il y a une évaluation de la feature à <code>t-50</code>. S'il y'en a une, c'est ok, s'il n'y en a pas, on reconstruit l'histoire. On remonte un pas de temps en arrière <code>t-51</code> jusqu'à ce qu'on tombe sur une valeur. Une fois qu'on a trouvé la valeur inférieure la plus proche (qui au minimum correspond à la naissance) on reproduit les valeurs manquantes jusqu'à <code>t-50</code> (en reproduisant le génotype de cette époque à partir des mutations au cours du temps). Ensuite on log cette valeur de la feature et on passe à la suivante, jusqu'à <code>t-50</code>. Et ainsi de suite. Comme ça, si on la redemande, elle sera déjà prête et il sera inutile de refaire le calcul.
</p>

<p>
    Si l'on souhaite utiliser le modèle pour faire des simulations et s'amuser à faire de la démographie, on aura naturellement accès à toute l'histoire de notre simulation
</p>
<ul>
    <li>Chaque feature log toutes ses évaluations</li>
    <li>Chaque support génétique log les mutations qu'il a subi et chaque mutation est loguée par le système quand elle a lieu</li>
    <li>Chaque individu généré disposera de ces logs et la simulation gardera en mémoire sa date de naissance et de mort</li>
</ul>

<p>
    Maintenant on peut faire cette remarque supplémentaire. On peut re-dérouler le fil de l'histoire mais on peut aussi décider, à un moment dans le passé de changer l'histoire ! Comme dans <em>La Vie est Belle</em> de Stephen Jay Gould on peut se poser la question "Est-si on avait mis une petite pichenette ici, est ce que ces espèces seraient encore là aujourd'hui ?" et y répondre ! Car on dispose de tout ce qu'il faut pour re-dérouler le fil de l'histoire et changer une chose, mettre une pichenette, et regarder les deux <em>mondes</em> évoluer vers leurs propres attracteurs.
</p>
<p>
    On pourrait faire ça dans n'importe quel modèle heuristique, aléatoire. Mais ici, l'intérêt c'est qu'on peut décider <em>exactement</em> quelle pichnette mettre, et déterminer <em>la cause précise</em> d'une divergence de l'histoire.
</p>
<p>
    Comment c'est possible ? Et bien c'est très simple : il suffit de récupérer un phénotype dans le passé d'un individu comme on l'a vu précédemment. On dispose non seulement de son phénotype mais également de son génome, sa valeur à cet instant ! Il suffit alors de dupliquer notre individu et de lui assigner ce phénotype <em>du passé</em>. Du point de vue de notre modèle, nous avons là un clone parfait de l'individu à un instant dans le passé. Si l'environnement peut être reproduit à l'identique, on peut lui faire subir une mutation, le mettre un peu plus à gauche ou à droite que sais-je, et observer la divergence des deux lignes de vie. Les possibilités sont grandes ! Et on peut évidemment faire tout ça à l'échelle d'une population : )
</p>

<p>
    Ce qui est intéressant avec ce système de mémoire, c'est qu'on va pouvoir répondre à des questions intéressantes dans notre programme, prendre des décisions sur le passé. Par exemple on pourra écrire une fonction qui dira "si tel individu, entre telle année et telle année n'a pas dépassé cette taille là, n'a pas eu cette couleur, n'a pas synthétisé 10L de telle molécule... alors...".
</p>