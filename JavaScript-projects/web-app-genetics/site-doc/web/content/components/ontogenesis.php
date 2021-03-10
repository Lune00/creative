<h3 id="ontogenese">Ontogenèse</h3>
<p>
    Chaque individu au cours de sa vie possède une forme de programme de développement. Un trait peut commencer à s'exprimer qu'à partir du moment où un autre trait s'est exprimé jusqu'à un certain stade (ou a fini de s'exprimer). Un trait peut ensuite continuer à s'exprimer ou ne plus s'exprimer du tout (perte d'un membre, caractère juvénile par exemple).
</p>
<img src="../src/img/sequential-conditional-genetic-expression.png" alt="Ontogenese" style="width:80%;">


<h4>Le composant <code>if</code></h4>
<p>
    Dans le modèle il faut donc pouvoir facilement modéliser des phénotypes qui suivent un programme de développement, et conditionner l'expression d'un génome en fonction d'un autre
<ul>
    <li>soit de manière conditionelle: B s'exprime si A s'est exprimé (condition sur A), A et B s'expriment
    <img src="../src/img/component-conditional-expression.png" alt="component-conditional-expression.png" style="width:80%;">
    </li>
    <li>soit de manière séquentielle: B s'exprime si A s'est exprimé, A ne s'exprime plus si B s'exprime. Pour réaliser ce composant il suffit de reprendre le composant conditionnel et mettre la condition sur A à <code>A == {}</code>.
    <img src="../src/img/component-sequential-expression.png" alt="component-conditional-expression.png" style="width:80%;">
    </li>
</ul>
<p>
On rappelle qu'une feature s'exprime toujours dans le phénotype sauf si elle renvoie un objet nul symbolisé par <code>{}</code>. Dans le cas d'un enchaînement séquentiel B s'exprime mais ne peut plus prendre A en entrée (puisque A ne s'exprime plus)
</p>

<p>
Nous avons introduit un nouveau composant :  <code>if</code>. Il permet de déplacer les tests sur les entrées et surtout de <strong>tester si l'entrée est nulle</strong>. <strong>On rappelle que par défaut toute feature émettant une valeur nulle <code>{}</code> n'est pas évaluée dans le génome et que toutes ses dépendances sont automatiquement évaluées à nul</strong>. Ainsi elles ne remontent pas non plus dans le génome, et il n'est pas nécessaire à l'utilisateur de tester à chaque nouvelle dépendance si la feature précédente a renvoyé.
</p>

<p>
Ce composant <code>if</code> a un comportement très simple : il a une entrée et peut avoir un nombre indeterminé de sorties. Il est défini par une condition sur son entrée et peut tester si l'entrée est nulle. Il faut définir deux valeurs de retour possible (vraie ou faux). Les 3 retours disponibles sont 
<ul>
    <li>la valeur de la feature en entrée</li>
    <li>la valeur vide (qui permet de laisser active la feature dépendante) <code>{valeur:{}, dimension:'', unit:''</code> (doit respecter le schéma d'une valeur de feature)</li>
    <li>la valeur nulle <code>{}</code> qui éteind les dépendances</li>
</ul>
</p>

<h4>Borner la croissance d'un phénotype : définir une période et un taux de croissance pour une feature</h4>

<p>
Certains traits, comme la taille d'un orgrane, se développe jusqu'à arriver à maturité. Le temps joue ici un rôle important dans l'expression d'une feature. Nous allons voir comment créer un composant générique pour fabriquer un trait <code>développement</code>. Ce trait varie de 0 à 100 et servira de base pour calculer n'importe quel autre trait
</p>
<p>
    Pour y parvenir il nous faut 3 supports génétiques avec un seul gène et une allèle initiale, ainsi que 2 features.
</p>

<p>
    Un support génétique pour coder pour \(t_1\), \(t_2\) et \(\tau\) (le taux d'expression ou de croissance du trait). La feature A prend en entrée \(t_1\) et \(t_2\), ainsi que \(t\) le temps actuel et \(t_0\) la date de naissance de l'individu.
</p>

<h4>Borner la croissance d'un phénotype : définir un phénotype cible pour en déduire les paramètres de croissance (méthode inverse)</h4>
