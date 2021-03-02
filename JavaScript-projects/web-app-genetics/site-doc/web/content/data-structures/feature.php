<h3 id="features">Feature (ou trait, phénotype local)</h3>

<h4>Définition</h4>

<p>Une fois que les supports génétiques sont définis on peut commencer à designer le composant à l'étage du dessus : la feature. On peut aussi commencer par une feature et designer ensuite le génome.</p>

<p>Une feature est un trait (un phénotype) observable au niveau de l'individu. C’est à ce niveau qu’on va <em>donner un sens aux valeurs retournées par le support génétique</em>. La feature produit une <strong>observable</strong> que l'utilisateur va définir. </p>

<p>L’intérêt de découpler la valeur d'un support génétique de son interprétation c’est qu'ont peut réutiliser un même support pour plusieurs features (dans différents projets) et redéfinir l'interprétation qu'on en fait.</p>
<p>
    La feature est une fonction qui va prendre en entrée la valeur d'un support génétique, <a href="#features-coupling">ou d'une autre feature</a>, et retourner un phénotype, c'est à dire, une valeur et (possiblement) une grandeur et une unité de mesure. C'est une fonction au sens mathématique du terme : à chaque valeur de l'ensemble de départ (valeurs du support génétique) elle produira une valeur dans un ensemble d'arrivée (valeurs du phénotype).
</p>

<p>
    Le point important c'est qu'une feature <strong>ne possède pas d'état interne</strong>. Elle prend des valeurs en entrée et renvoie des valeurs en sortie. Les même valeurs en entrée produisent <em>toujours</em> les mêmes valeurs en sortie. Elle n'a aucun effet de bord, c'est à dire que lorsqu'elle est évaluée elle ne <em> modifie pas l'état du monde</em> (exception faite des <a href="#epigenetique"> features attachées à l'état épigénétique</a>). En d'autres termes ce sont des <a href="https://fr.wikipedia.org/wiki/Fonction_pure">fonctions pures</a>. L'état d'un individu est complètement encodé dans ses supports génétiques et son épigénetique. L'ensemble des features vient agir comme une fonction qui prend cet état et renvoie un phénotype macroscopique.
</p>

<img src="./../src/img/feature-function.png" alt="">

<p>Pour définir l'évaluation d'une feature, lui donner sens, nous allons avoir besoin d' </p>

<ul>
    <li>une valeur : nombre décimal, une chaîne de caractères, un ensemble de clé:valeur, voir même une fonction</li>
    <li>une grandeur: (ex: temps, longueur, grandeur personnalisée...) [OPTIONNEL]</li>
    <li>une unité de mesure: ‘m/s’, des ‘mols’, des ‘kg’, des ‘grade’, des ‘milipilpoils’ etc.. [OPTIONNEL]</li>
</ul>

<p>
    L'unité de mesure servira à faire de l'analyse dimensionnelle et valider la cohérence de certaines expressions. Elle pourra servir à faire des conversions automatiques. Par exemple si un phénotype représente une taille, on pourra demander à évaluer cette valeur en 'cm', en 'm' sans avoir besoin de faire la conversion nous même.
</p>

<p class="note">
    A noter : l'utilisateur s'il souhaite avoir directement accès à la valeur du support génétique peut le faire, il peut demander à la feature de retourner directement la valeur du support, par exemple <code>{A:1, B:2}</code>.
</p>


<h4>Paramètres</h4>

<table>
    <thead>
        <tr>
            <th colspan="4">Feature</th>
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
            <td>Un nom donné à la feature</td>
            <td>String</td>
            <td>Unique</td>
        </tr>
        <tr>
            <td>Source</td>
            <td>D'où proviennent les entrées de la feature</td>
            <td>Support Génétique ou (Features...)</td>
            <td>Unique si support, MAX(à définir) si features</td>
        </tr>
        <tr>
            <td>Output</td>
            <td>Données en sortie de la feature</td>
            <td>Ensemble {clé:valeurs},<code>Object</code></td>
            <td>
                Doit respecter le schéma <code>{valeur: Object, dimension: String, unit: String}</code>. Ajouter peut être une contrainte sur le schéma de <code>value</code>
            </td>
        </tr>
        <tr>
            <td>Input</td>
            <td>Données en entrée de la feature. <ul>
                    <li>Si support génétique : évaluation du support [entrées possibles définies]</li>
                    <li>Si une ou plusieurs features : concaténation des évaluations des features</li>
                </ul>
            </td>
            <td>Ensemble {clé:valeurs},<code>Object</code></td>
            <td>

                <ul>
                    <li> Si source est support : structure passée en entrée doit contenir les clefs appartenant à l'ensemble des allèles définis sur le support</li>

                    <li>Si sources est features : voir contraintes à mettre. Chaque input doit respecter le schéma de données Output de la source. Chaque input doit respecter le schéma <code>{valeur: Object, dimension: String, unit: String}</code> </li>
                </ul>


            </td>
        </tr>
        <tr>
            <td>Log</td>
            <td>Historique de toutes les valeurs générées par la feature. A chaque évaluation, si l'évaluation est différente de la précédente valeur on la log.</td>
            <td>Stack (Last in First Out) { t: {valeur, dimension, unit}}, tableau d'Object</td>
            <td>
                Aucune
            </td>

        </tr>
    </tbody>
</table>


<h4>Écrire une feature</h4>

Pour qu'une feature fonctionne il faut définir :

<ul>
    <li>ce qu'elle prend en entrée (arguments): valeur d'un support génétique, valeur produite par une autre feature</li>
    <li>ce qu'elle retourne en sortie: quelle transformation j'opère pour produire une valeur "phénotype"</li>
</ul>

<h4>1) Mapper les valeurs des allèles</h4>

<p>La première étape est donc de <em>maper</em> (d'associer) à chaque allèle exprimée du support génétique une valeur. Comme les allèles sont définies au niveau du support génétique on peut facilement proposer une liste de valeurs à maper à l'utilisateur. On peut associer à la valeur de l'allèle n'importe quelle valeur de notre choix</p>
<p>Prenons un exemple de valeur produite par le support génétique encodé sur 3 gènes</p>
$$(c-B)A(A-B) $$
<p>qui est évalué à</p>
$$ S =\{ AB: 1, A:1, B:0.5, C:0.5 \} $$
On doit proposer à l'utilisateur d'associer à chaque allèle une valeur. Prenons \(A\), voici les possibilités :

<ul>
    <li>Associer un entier : \(A \mapsto 1 \)</li>
    <li>Associer un nombre décimal : \(A \mapsto 0.1 \)</li>
    <li>Associer une chaine de caractères : \(A \mapsto \text{'foo'}\)</li>
    <li>Associer un tableau : \(A \mapsto \left[1, \text{'foo'}, 0.5, \left[1, \text{'foo'}, 0.5, \right]\ \right]\)</li>
    <li>Associer une association clé:valeur : \(A \mapsto \{a: 1, b: \text{'foo'}\}\)</li>
    <li> <a href="#fonctionnal-feature">Associer une fonction</a> : \(A \mapsto f(S)\)</li>
</ul>

<p>On pourra évidemment proposer ici de mapper des valeurs de manière automatique (pattern, aléatoire etc..)</p>

<p>On pourrait imaginer ne pas contraindre l'utilisateur à définir la valeur de chaque allèle. Ainsi, une valeur non mappée aurait la valeur de son code binaire, nom et une dimension dédiée, par exemple <code>{value: {A:1, B:1}, dimension: 'gene', unit: 'none'}</code></p>

<code class="pseudo-code">
    <pre>
x = evaluate(individu, feature) // acceder au phénotype retourné par la feature
//Allèle inconnue (mutation, non définie par l'utilisateur)
if(isGene(x)){
    //Do stuff
    valeur = ....
    // retrouve l'allèle non mappée et lui assigne valeur,dimension, unité
    setValue(feature, 'valeur', dimension, unité) 
}
        </pre>
</code>

<p>Nous reviendrons sur la possibilité de tomber sur des allèles dont l'évaluation est inconnue dans la section <a href="mutations">mutations</a> </p>

<h4>Cas d'un support codé sur un gène</h4>

<p>
    Dans le cas où la feature prend en entrée l'évaluation d'un support encodé sur un seul gène, la question ne se pose pas, on retourne la valeur mappé à la valeur qui s'est exprimée.
</p>

<h4>Cas d'un support codé sur plusieurs gènes</h4>
<p>
    Reprenons notre exemple précédent,
    $$ S =\{ AB: 1, A:1, B:0.5, C:0.5 \} $$
    Ici, un support génétique est s'exprime sur plusieurs gènes. Pour interpréter cette valeur, plusieurs stratégies d'interprétation peuvent être définies par l'utilisateur.
    On peut :
<ul>
    <li>Renvoyer toutes les valeurs avec leurs poids (information transparente, l'utilisateur en fera quelque chose soit dans une feature à l'étage supérieur, soit directement dans son projet)</li>
    <li>Filtrer : ne renvoyer qu'une valeur, envoyer des valeurs dont le poids normalisé respecte une condition</li>
    <li>mapper automatiquement à un type et une valeur (aléatoire, regex...)</li>
</ul>
</p>

<p>
    Si on associe à chaque valeur du support un nombre (entier ou décimal) alors on peut faire une combinaison linéaire.
</p>

<h5>Combinaison linéaire</h5>

<p> <strong>Si et seulement si l'utilisateur map chacune des allèles à un nombre (entier ou décimal) </strong>on peut proposer à l'utilisateur d'en faire un combinaison linéaire se servant du poids caractérisant la contribution de chaque allèle. Par exemple ici, définissons cette association : </p>
<ul>
    <li>\(AB \mapsto 1 \)</li>
    <li>\(A \mapsto 0 \)</li>
    <li>\(B \mapsto 5 \)</li>
    <li>\(C \mapsto -1 \)</li>
</ul>
<p>On peut facilement fabriquer de la variation continue en faisant la combinaison linéaire de l'expression de chaque allèle (notamment dans le cas de dominance incomplète)</p>

$$ \frac{1}{3} (v_{AB} + v_A + 0.5v_B + 0.5v_C) $$
<p>en utilisant le poids de l'expression de chaque allèle. La feature sera évaluée ici à \(1\). L'évaluation en combinaison linéaire d'un support génétique encodé sur \(N\) gènes est donné par



    $$ V = \frac{1}{N}\sum_{i=1}^{N} u(i_a,i_b)v_a + (1-u(i_a,i_b))v_b $$

    Soit
    $$ V = \frac{1}{N}\sum_{i=1}^{N} u(i_a,i_b)\left[v_a -v_b\right] + v_b $$
</p>

<p>avec \(i_a\) et \(i_b\) les allèles a et b du gène \(i\).</p>

<p>
    L'utilisateur peut ensuite <strong>metre à l'échelle (rescale)</strong> les valeurs obtenues vers un nouvel intervalle. En effet, en fonction des valeurs qu'il a associé à chaque allèle, il a défini un domaine de départ (les bornes min et max), ici \( \left[ -1 : 5 \right]\). Il peut interpoler chaque valeur de cet intervalle vers un autre intervalle. Pour cela il a juste à définir un min, un max et une fonction d'interpolation. Par exemple, il définit l'intervalle d'arrivée à \( \left[ 10 : 300 \right]\) et une fonction d'interpolation linéaire.
</p>
<p>
    On peut faire une interpolation linéaire ou avec n’importe quel polynôme. Le choix de l'interpolation est un paramètre intéressant car ainsi, une variation infime du génome (brassage, mutation) peut conduire à des variations phénotypiques plus fortes (et non directement proportionnelle ou graduelle)
</p>

<img src="../src/img/interpolation.png" alt="" style="width:80%">


<p class="question">Comment ça se passe pour un trait phénotypique encodé sur plusieurs gènes en vrai? Quelles stratégies peut on mettre en place pour fabriquer une interprétation d'un support génétique s'exprimant sur plusieurs gènes ? Dans ce cas, quel rôle donner aux <em>poids d'expression</em> ?</p>


<h5>Ultime possibilité (et la plus forte) : écrire soi même sa fonction !</h5>

<p>
    L'idéal est de pouvoir écrire soi même une fonction qui renverra le phénotype. Cette fonction permet de couvrir toutes les autres stratégies définies précédemment (celles-ci ne sont que des aides pour l'utilisateur, lui proposer des stratégies clés en main sur des patterns courants). Ainsi on peut donner à l'utilisateur un éditeur pour qu'il écrive soi même sa fonction
</p>
<code class="pseudo-code">
    <pre>
function evaluate(args){
    //Write your own function that returns a phenotype (data)
    //...
    return {}
}
        </pre>
</code>
<p>où <code>args</code> est une variable d'entrée de la fonction que l'utilisateur peut utiliser. Elle aurait toutes les infos nécessaires pour écrire la fonction : les valeurs de départ du support, les poids et les valeurs mappés (si elles l'ont été). Par exemple ici :</p>
<pre>
    <code>args = {
        genetic: { 
          AB: {
            // poids expression de la valeur retournée par le support
            weight: 1, 
            // la valeur assignée par l'utilisateur
            map: 1 
          },
          A: {
            weight: 1,
            map: 0  
          },
          B: {
            weight: 0.5,
            map: 5  
          },
          C: {
            weight: 0.5,
            map: undefined  
          },
         }
        featureB: {}
        ...
    }
    </code>
</pre>

<p> Le code sera à écrire en JavaScript (ou langage de script transpilable vers JS). Il permettra de faire tout ce qu'on veut. Justement, tout ce qu'on veut peut amener à des gros problèmes de sécurité. Il faudra songer à ce point : accès au DOM, Web API du navigateur? Émettre des requêtes? Il faudra proposer un environnement où on peut contrôler les autorisations qu'on donne à ce code.</p>

<h5>Contrainte sur la valeur retournée?</h5>

<p>Si l'utilisateur écrit sa propre fonction (dans les autres cas ça sera fait automatiquement) il devra fournir un schéma de données pour la valeur retournée par la feature. Par exemple </p>
<pre>
    <code>phenotype = [
        {
            value: String,
            dimension: String,
            unit: String,
        },
        {
            value: Integer,
            dimension: String,
            unit: String,
        },
        ...
       ]
    }
    </code>
</pre>
<p>Ainsi il sera beaucoup plus simple dans l'étape de design de coupler les features, car on saura exactement quelles données on recevra en entrée. Il est peut être même possible qu'on puisse récupérer les valeurs possibles retournées (on peut imaginer créer un bouton <code>Test</code> dans l'éditeur qui testerait la fonction (vérification entrées, vérification du retour conforme au schéma) et qui l'évaluerait sur toutes les valeurs d'entrées possibles pour produire tous les outputs possibles. On disposerait d'une liste de valeurs retournées pour aider le design d'une autre feature qui la prendrait en argument. </p>
<p>Ici j'ai mis un tableau de structure phénotype {value, dimension, unit}, on pourrait restreindre encore davantage à une seule structure phénotype. Et demander un schéma de données pour la valeur. On peut contraindre pas mal je pense car si on met trop de libertés ça va compliquer le design. Si une feature peut renvoyer deux <em>schémas</em> (structure de données) de phénotypes différents c'est qu'elle peut probablement être découpée en deux features qui retourne chacune un seul. Ces questions seront tranchées par la pratique.</p>


<p>Prenons un exemple simple ici j'écris ma fonction, je veux, par exemple, retourner la valeur de \(AB\) si elle existe, sinon je renvoie 'toto'</p>
<code class="pseudo-code">
    <pre>
function evaluate(args, phenotypes = []}){
    if( 'AB' in args.genetic){
        // valeur du phénotype retourné
        phenotype.value =  args.genetic['AB'].map
        phenotype.dimension = 'Length'
        phenotype.units = 'm'
        return phenotypes.push(phenotype)
    }
    //Si AB n'est pas présent
    phenotype.value = 'toto'
    phenotype.units = 'none'
    phenotype.units = 'none'
    return phenotypes.push(phenotype)
}
    </pre>
</code>

<p>Ici on contraint la réponse à respecter le schéma suivant : la valeur retourné doit contenir 3 clés: value, dimension et units. Si une clé manque (ou si une autre clé est ajoutée) une erreur est émise. Un <em>template</em> de phénotype est imposé. </p>


<p class="note">On peut imaginer encore beaucoup de choses dans les contraintes à imposer ici. Plus on met de contraintes plus c'est long d'éditer mais plus on peut proposer des tests automatiques pour avertir l'utilisateur en cas de bug. Autant de temps à débugger en moins dans son projet</p>

<h4 id="fonctionnal-feature">Features <em>fonctionnelles</em></h4>

<p>
    Jusqu’ici on a parlé d’associer aux valeurs remontées par le support génétique d'autres valeurs qui <em>font sens</em>. On fait correspondre des valeurs à des valeurs, on map. Une feature est une simple <em>fonction</em> au sens mathématique qui, à chaque valeur fait correspondre une autre valeur. Pourquoi s’arrêter là ? Pourquoi ne pas donner la possibilité d’associer à chaque valeur d’un support génétique directement une fonction ? En effet, une fonction est <em>une valeur comme les autres</em> (dans une approche <a href="https://en.wikipedia.org/wiki/First-class_function">first-class function</a>), au même titre que 1 ou ‘toto’.
</p>

<p>
    Cette possibilité est <strong>extrêmement intéressante</strong> car elle permet de produire des phénotypes qui sont non plus juste des états (une valeur interprétée du support génétique) mais des <strong>comportements</strong>.
</p>

<p>Reprenons un exemple où notre support génétique est codé sur un gène avec deux allèles A et B, avec \(u(A,B)=1\), soit A dominant et B récessif. On a donc deux valeurs possibles , A ou B, pour ce support. Associons une fonction(une valeur) à chaque allèle dans notre feature que nous appellerons <code>'FeatureA'</code> :</p>
<ul>
    <li>\(A \mapsto f_A(x,y) \{ \text{return x + y} \} \)</li>
    <li>\(B \mapsto f_B(x,y) \{ \text{return x - y} \} \)</li>
</ul>

<p>où \(x\) peut être n'importe quoi (y compris une fonction !) C'est à l'utilisateur de le définir. Attention ici on est pas dans le cas où on va appliquer \(f_A\) quand A s'exprime et renvoyer le résultat. Ici, on <strong>retourne</strong>\(f_A(x)\)</p>

<p>Par exemple, un extrait de pseudo-code de l'utilisateur dans son projet</p>

<code class="pseudo-code">
    <pre>
value = evaluate(individu,'FeatureA')
x = value(1,2) // = 3 si A s'exprime, -1 si B s'exprime
        </pre>
</code>

<p>Le fait de pouvoir retourner directement des fonctions est une propriété très intéressante et utile au modèle pour créer des phénotypes riches, faits d'états mais aussi de comportements. Cela ouvre énormément de possibilités.</p>


<h4 id="fonctionnal-feature">Features <em>récursives</em></h4>
<p>
    Des features qui se prennent elle même en argument (possible de le faire déjà à partir d'une feature fonctionnelle récursive non?)
</p>


<h4>Sur les dimensions et unités de mesure</h4>
<p>
    La bibliothèque embarquera avec elle les dimensions et unités de mesure répandues (sûrement en utilisant une library tierce). L'utilisateur pourra également définir lui même ses propres grandeurs et unités associées.
</p>

<h4>Sur le temps</h4>
<p>
    Pour le moment nous n'avons pas parlé du temps, les features produisent des phénotypes statiques pour un matériel génétique donné. <strong>Le temps sera accessible par défaut à chaque feature en argument</strong> pour permettre à l'utilisateur de produire des évaluations dynamiques du phénotype. En effet, pour faire évoluer un système (un individu par exemple) il faut une notion de temps d'une manière ou d'une autre. L'horloge interne d'un individu (à sa naissance) \(t_0\) sera accessible à chaque individu.
</p>

<p>
    Il faudra définir un temps bien caractérisé (unité) qui sera utilisable par toutes les features et défini/initialisé à l'échelle du projet comme une variable globale. A réfléchir...
</p>


<h4 id="features-coupling">Coupler les features (et donc l'expression des gènes)</h4>

<p>Une feature peut prendre en entrée (en argument)</p>
<ul>
    <li> <strong> un et un seul support génétique</strong></li>
    <li>un support génétique et une ou plusieurs features, voir <a href="#general-model">ce schéma</a></li>
    <li>une ou plusieurs valeurs d'<a href="#environment">environnement</a> (inclus le temps)</li>
</ul>

<p>
    Voici une notion un peu plus avancée du modèle mais qui permet, je crois, de lui donner beaucoup d’intérêt et de puissance.
</p>
<p>
    Pour le moment, on peut définir des features, chacune interprétant l'expression d'un support génétique. C’est cool déjà, mais c’est embêtant car toutes ces features sont sagement <em>les unes à coté des autres, à s’ignorer mutuellement et à vivre leur vie</em> . En soi on peut laisser au soin de l’utilisateur de combiner les effets des features pour fabriquer de nouveaux mécanismes lui-même. Mais on peut aussi intégrer nativement cette possibilité dans notre bibliothèque, et créer de manière récursive et <em>infinie</em> des features à partir d’autres features.
</p>
<p>
    Créer un réseau de features pour fabriquer des nouvelles features, pour fabriquer des nouvelles features. Ainsi on peut créer du couplage entre supports génétiques et produire des phénotypes beaucoup plus intéressants. Voyons cela plus en détails, à partir d’un exemple concret.
</p>

<img src="./../src/img/features-coupling-time.png" alt="" style="width: 100%;">

<p>
    Sur le schéma ci dessus on a un cas de couplage qui fait intervenir le temps. On a une feature qui nous renvoie la taille de l'individu. Cette taille est fonction du temps (accessible en lecture et donnée par le système à toutes les features). Pour évaluer la taille d'un individu il faut évaluer cette feature <code>taille</code>. Cette feature est couplée à trois autres features : <code>taille min</code> qui donne une taille minimale (à la naissance) encodée sur son support génétique, <code></code> idem, et <code>taux de croissance</code> .
</p>

<p>
    On a donc une feature <code>taille</code> qui, pour être évaluée, doit évaluer avant tout ses dépendances (on pourra optimiser cette étape, avec un cache et n'évaluer que si l'évaluation de cette feature a changé, notamment grâce à la gestion des mutations). Avec la fonction définie pour la feature <code>taille</code>, quand je l'évaluerai j'aurai toujours la bonne valeur, même si taux de croissance mute entre deux évaluations.
</p>
<p>
    Voici comment on peut coupler les features entre elles pour produire des nouvelles features, et créer autant de complexité qu'on le souhaite. On peut imaginer ici reproduire des features à la manière de composants informatiques, qui viennent éteindre et allumer l'expression d'autres features.
</p>
<p>
    Comme on peut le voir dans l'exemple, pour évaluer <code>taille</code> on se sert de la dernière valeur renvoyée par la feature. On accède à son<code>LOG</code>, son historique, et on récupère la dernière entrée avec <code>popValue()</code> et <code>popTime()</code>. Le <code>LOG</code> est une <a href="https://fr.wikipedia.org/wiki/Pile_(informatique)">pile</a>, c'est une structure de données "Last In First Out". C'est une collection de <code>valeurs immutables</code> (on ne peut pas les changer!). Chaque entrée du <code>LOG</code> a la structure <code>{date, value}</code> . Il est temps d'aborder un point important sur l'évaluation et les états d'un individu.
</p>


<h4 id="immutability">Les états et l'évaluation</h4>

<p>C'est sans doute l'un des points les plus importants dans le design de ce modèle. Le phénotype d'un individu <strong>est une valeur, elle est donc immutable</strong>.</p>
<p>
    Quand on veut connaître la taille d'un individu par exemple, on ne vient pas écraser ou mettre à jour la taille qu'on avait noté avant. La taille d'un individu ne change pas dans le temps (votre taille change bien sûr mais pas dans un système d'informations, si elle change c'est une nouvelle entrée) : quand on la mesure on obtient des valeurs différentes à chaque instant. Quand on mesurait notre taille enfant en mettant une petite marque sur le mur, on n'effaçait pas la marque d'avant pour mettre la suivante, plus haute. On faisait une nouvelle marque ! Il sera toujours vrai, qu'à un moment donné vous étiez plus petit qu'aujourd'hui. Prenez une personne que vous connaissiez enfant et qui est devenue adulte, vous vous souvenez d'elle quand elle était petite, vous n'êtes pas allés dans notre cerveau chercher la cellule qui stocke sa taille pour la remplacer par sa taille adulte ! Les deux cohabitent, les informations s'accumulent, de manière associative. Et c'est ce qui vous permet de dire "Oh, ce que tu as grandi!". En ce sens, du point de vue du système d'information, la taille n'est pas un état mutable.
</p>

<p>
    C'est la même chose pour notre phénotype. Le phénotype n'a pas à être un état mutable, qu'on viendrait mettre à jour à chaque pas de temps. Non ! Le phénotype est <strong>un instantanée de l'évaluation de toutes les features d'un individu</strong>. Si je veux connaître la taille d'un individu, j'évalue sa feature <code>taille</code> et elle me renvoie une valeur. Cette valeur dépend du temps (mesurer deux fois la taille au même instant produit la même valeur).
</p>
<p>
    Chaque feature, comme dans l'exemple ci-dessus, conserve un journal, un historique (un <code>LOG</code>) de toutes les valeurs qu'elle a produite par le passées. Ainsi, j'accède naturellement à l'histoire complète de mon individu. Je ne remplace pas la valeur taille, j'en créée un nouvelle à chaque fois que je fais la mesure. Ce <code>LOG</code> permet de calculer le présent en fonction du passé. Le présent (ou le futur) ne vient pas écraser le passé.
</p>

<p>
    Pour ces raisons, il est hors de question pour notre feature d'avoir un état mutable (qui change sur place). Le <code>LOG</code> change non, on ajoute des valeurs. Oui, mais une collection de valeurs immutables, qui s'agrandit peut être vue comme une valeur.
</p>
<p>
    Dans ce modèle, l'état mutable est le support génétique, sujet à des <em>mutations</em>. Dans toute cette bibliothèque le seul état mutable est le génome (exception faite de l'épigénétique, qui est d'ailleurs peut-être une mauvaise idée, ça peut être utile mais déconseillée à n'utiliser que dans des cas où c'est nécessaire)
</p>

<p>
    Pour résumer, <strong>le phénotype d'un individu est une valeur</strong> produite par les features à un instant donné. Les features n'ont pas d'état mutable (qui change sur place). Elles peuvent produire une valeur à partir d'une valeur produite dans le passé, c'est bien normal. Mais <strong>elles ne peuvent pas modifier le passé</strong>, elles peuvent juste y accéder en lecture, <strong>ce sont des faits</strong>. Chaque nouvelle entrée s'ajoute aux précédentes sans les modifier, aucune entrée ne peut être modifiée ou supprimée par la feature.
</p>


<h5>Quelques exemples</h5>

<h5>Phénotype dormant</h5>


<p>Prenons l'exemple d'un individu <em>serpent</em>. Il possède des gènes pour coder un pied, et d'autres gènes pour lui donner forme (nombre de doigts, pied palmé etc...). Dans la plupart du temps (phénotype dominant à l'état sauvage) il ne s'exprime pas. Dans son phénotype on ne trouve aucune expression du pied, et des traits propres au pied. </p>
<img src="./../src/img/coupling-feature-on-off-ex2.png" style="width: 100%;" alt="">
<p> Ici, l'allèle B (la plus courante) s'exprime. La feature renvoie une valeur vide \(\{\}\). Toutes les features qui en dépendent ne peuvent plus s'exprimer et renvoient une valeur vide à leur tour. Le résultat net est que le génome concerné ne s'exprime pas et que le phénotype n'est pas observé </p>
<p>Ces gènes ne s'activent que si l'allèle A s'exprime, comme ci-dessous. Si c'est le cas l'intégralité du génome du pied s'exprime et on trouve un phénotype</p>
<img src="./../src/img/coupling-feature-on-off-ex1.png" style="width: 100%;" alt="">
<p>L'activation en cascade de toutes les features dépendantes est alors automatique dans le modèle.</p>


<h5>Les features sont des API</h5>

<p>Les features sont des fonctions pures qui prennent en entrée une valeur et retourne une valeur. En ce sens tout leur comportement est défini par les arguments en entrée. Aussi on pourra fournir pour chacune d'entre elle, en fonction des contraintes qu'on imposera, une documentation des arguments acceptés et des sorties produites. Elles seront alors facilement testables de manière unitaire (isolées). Elles ont donc une <a href="https://fr.wikipedia.org/wiki/Interface_de_programmation">API</a> et il n'est pas utile de regarder dans le détail de leur code source pour s'en servir. La documentation pourra nous dire ce que chaque feature fait, de quelle feature elle dépend etc.. Et une fois définie (ou récupérée) on pourra l'utiliser comme une boîte noire dans notre projet, sans avoir à soulever le capot. </p>

<h5>Une feature "Groupe de features"</h5>

<p>
    Comme on l’a vu, on peut coupler des features pour faire des nouvelles features. Cela crée des dépendances entres features. Pour simplifier la vie de l’utilisateur on pourrait rajouter quelque chose de simple : faire des paquets de features. Au lieu d’évaluer chacune d’entre elles on en évalue qu’une qui renverra l ‘évaluation de toutes les features dont elle dépend. C’est juste une fonctionnalité pour faciliter la vie de l’utilisateur et simplifier l’usage de la bibliothèque.
</p>
<p>
    Par exemple, je crée tout un ensemble de features relatives à la possibilité de voler d’un animal : absence/présence d’ailes, taille des ailes, types ailes (a plume, mammifère), forme des ailes, couleurs des plumes, bruit que fond les ailes, vitesse en vol, vitesse de pointe etc... Toutes ces features sont reliées les unes aux autres. Par exemple s’il n’y a pas de plumes, il n'y a pas de couleur des plumes. Au lieu d’avoir à interroger manuellement chacune de ces features je pourrais créer une « méta-feature » qui s’appelle « vol » par exemple. Elle les comprendrait toutes. Cela donnerait une paquet prêt à l’emploi ds n’importe quel projet où je veux voir ce trait phénotypique exister. Ainsi dans le code au lieu d’avoir un truc du genre :
</p>

<code class="pseudo-code">
    <pre>
hasPlumage = evaluate(individu, ‘hasPlumage’)
plumageColors = evaluate(individu, ‘plumageColors’)
wingsSize = evaluate(individu, ‘wingsSize’)
etc.
//Then do logic
...
//A la place on aurait
vol = evaluate(individu, ‘vol’)
//vol contiendrait toutes les données :
//par ex : vol = {
    hasWings : true,
    hasPlumage : false,
    plumageColor : undefined,
    wingSize : {
        value : 52,
        dimension: 'length'
        unit : ‘cm’
    },
    speed : {
        value : 60 ,
        dimension: 'speed'
        unit : ‘km/h’
    }
    //Etc...
} 
        </pre>
</code>

<p>
    En ce sens, le phénotype global d'un individu (l'ensemble de ses traits), est la <em>méta feature</em> la plus globale. A voir. On peut aussi décider qu'une feature dépendante d'une autre feature est embeded dans celle-ci. Si la feature parente ne s'exprime pas, celle-ci ne s'exprime pas et ne remonte pas dans le phénotype. Ainsi la méta-feature est explicite.
</p>
<code class="pseudo-code">
    <pre>
//evalue toutes les features d'un coup
phenotype = evaluate(individu)
    </pre>
</code>


<h4>Pour résumer :</h4>

<p>Pour créer une feature l'utilisateur doit</p>
<ul>
    <li>Lui donner un nom</li>
    <li>Lui donner ses sources/arguments (un support génétique, une ou plusieurs features). Ca définit ce qu'elle prend en entrée</li>
    <li>Si une source est un support génétique, il peut associer une valeur à chaque allèle. Si la source est une feature, il n'a rien à faire (l'entrée est définie par le retour de cette feature)</li>
    <li>Définir ce que la feature retourne (soit une stratégie, soit il implémente sa propre fonction)</li>
    <li>Si la valeur retournée est définie par une fonction écrite par l'utilisateur il doit en plus renseigner le schéma de la réponse(la structure des données renvoyée)</li>
</ul>