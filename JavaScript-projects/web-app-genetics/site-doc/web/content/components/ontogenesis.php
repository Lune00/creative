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
    Nous avons introduit un nouveau composant : <code>if</code>. Il permet de déplacer les tests sur les entrées et surtout de <strong>tester si l'entrée est nulle</strong>. <strong>On rappelle que par défaut toute feature émettant une valeur nulle <code>{}</code> n'est pas évaluée dans le génome et que toutes ses dépendances sont automatiquement évaluées à nul</strong>. Ainsi elles ne remontent pas non plus dans le génome, et il n'est pas nécessaire à l'utilisateur de tester à chaque nouvelle dépendance si la feature précédente a renvoyé.
</p>

<p>
    Ce composant <code>if</code> a un comportement très simple : il a une entrée et peut avoir un nombre indeterminé de sorties. Il est défini par une condition sur son entrée et peut tester si l'entrée est nulle. Il faut définir deux valeurs de retour possible (vraie ou faux). Les 3 retours disponibles sont
<ul>
    <li>la valeur de la feature en entrée</li>
    <li>la valeur vide (qui permet de laisser active la feature dépendante) <code>{valeur:{}, dimension:'', unit:''</code> (doit respecter le schéma d'une valeur de feature)</li>
    <li>la valeur nulle <code>{}</code> qui éteind les dépendances</li>
</ul>
</p>

<h4>Composant <code>développement</code>, fournir à une feature une expression modulée dans le temps</h4>

<p>
    Certains traits, comme la taille d'un orgrane, se développe jusqu'à arriver à maturité. Le temps joue ici un rôle <code>fondamental</code> dans l'expression du phénotype. Nous allons voir comment créer un composant générique pour modéliser <code>des gênes de développement</code>. Pour cela il faut définir 3 paramètres :
<ul>
    <li>\(t_1\) : la date à partir de laquelle le trait s'exprime, commence à se développer</li>
    <li>\(t_2\) : la date à partir de laquelle le trait est complètement exprimé</li>
    <li>\(\tau\) : le taux de variation, de croissance </li>
</ul>
</p>

<img src="../../src/img/component-development.png" alt="">

<p>
    Soit \(h(t)\) l'expression d'une feature H dépendante du temps, on pourra facilement <a href="https://fr.wikipedia.org/wiki/Calcul_num%C3%A9rique_d%27une_int%C3%A9grale"><em>intégrer</em> \(h\)</a> au cours du temps en utilisant une simple méthode d'Euler explicite ici (ou une méthode plus avancée au besoin)
</p>

$$ h(t) = h(t-1) + \tau \delta t$$

<p>
    où \(\delta t\) est un petit intervalle de temps.
</p>

<p>
    Pour développer ce composant il nous faut 3 supports génétiques (un pour chaque paramètre \(t_1\), \(t_2\) et \(\tau\)) avec un seul gène et une allèle initiale, ainsi que 2 features.
</p>


<img src="../../src/img/composant-developpement2.png" alt="">

<p>
    Comme on peut le voir sur le schéma ci-dessus la feature A prend en entrée \(t_1\) et \(t_2\), ainsi que \(t\) le temps actuel et \(t_0\) la date de naissance de l'individu. Elle renvoie vrai si la feature s'exprime, faux sinon. La feature B, en fonction du retour de A renvoie soit la valeur de \(tau\) soit \(tau=0\). Le résultat est que
<ul>
    <li>si \( t < t_1\) : la feature reste égale à sa valeur initiale, elle est au repos</li>

    <li>si \( t_1< t < t_2\) : la feature reste est activée et se développe ( \( \tau \ne 0\) )</li>
    <li>si \( t > t_2\) : la feature reste a la même valeur pour toujours ( \( \tau = 0\) )</li>
</ul>
</p>

<p>
    On a donc ici une proposition de design pour un composant qui encapsule un développement dans le temps. L'API du composant <code>développement</code> (son interface) est :
<ul>
    <li>Une valeur initiale pour l'unique allèle de chaque support génétique codant pour \(t_1\), \(t_2\) et \(\tau\)</li>
</ul>
</p>

<p>
    Une fois ce composant designé, il peut être réutilisé partout et n'importe quand, <em>le chemin n'est plus à refaire</em>. Il est <em>plug and play</em> et peut être branché facilement sur n'importe quelle autre feature qui aurait besoin d'avoir une dimension temporelle dans son évaluation, sans encombrer cette dernière avec toute la logique du temps.
</p>

<h4>Borner la croissance d'un phénotype : définir un phénotype cible pour en déduire les paramètres de croissance (méthode inverse)</h4>

<p>
    Dans le composant précédent on a définit une période d'expression et un taux. En somme on a controlé l'aspect temporel de l'expression. On pourrait également voir le développement de manière inversée et considérer le développement terminé quand on a atteint une valeur cible.
</p>