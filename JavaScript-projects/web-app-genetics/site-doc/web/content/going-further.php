<h2 id="environment">Aller plus loin: créer des Environnements (pour finir le boulot)</h2>

<p>
    Le système fournit aux features une valeur temps (en lecture seule). Et comment faire intervenir des paramètres environnementaux, comme une température ? Chez des lapins, la couleur du pelage dépend de certainez enzymes. Ceux qui ont des couleurs claires sauf aux extrémités indique que des enzymes s'expriment davantage aux basse températures qu'aux hautes températures (reste du corps).
</p>
<p>
    On peut donc imaginer intégrer une autre structure de données (dépendance d'une feature) <code>Environnement</code> qui injecte dans les arguments de la feature une valeur (comme le temps) pour permettre d'évaluer la feature. Si on fait ça, il suffit de rajouter dans le <code>LOG</code> de la feature la valeur l'environnement, par exemple : {date, temperature, valeur}. Ainsi on peut reconstruire toute l'histoire comme avant.
</p>
<p>
    Les Environnements fonctionneraient sur le même mode que les mutations, sauf qu'ils ne font pas muter directement le génome, mais conditionne l'expression du phénotype, au même titre que le temps ! Par contre, on peut coupler une mutation à un environnement. Par exemple "si la température dépasse telle valeur déclenche cette mutation". Ainsi, chaque composant a sa responsabilité, la mutation est enregistrée, le génome change, la feature produit une nouvelle valeur (ou non). Et on a toute l'information pour reconstruire l'histoire.
</p>
<p>
    Et enfin, pour finir la boucle, faire en sorte qu'une population puisse influencer l'environnement ! Voilà un usage de l'entité population intéressant. Par exemple, pression démographique pousse l'environnement dans un nouvel état, ce qui provoque une mutation ou l'expression du génome. Et la boucle est bouclée ! On peut enfin voir une population s'autoexterminer par destruction de son environnement (tout ça intégré nativement dans le modèle). C'est plus un modèle en fait maintenant, c'est un moteur, un framework.
</p>

<h2>Hacker le modèle</h2>

<p>Il y aurait plein de façons de hacker, de détourner de son usage principal, le modèle pour créer des nouveaux mécanismes au delà des phénotypes et du génome. On pourrait imaginer des features qui ne prennent pas du tout en compte le génome (même indirectement). Et étendre le système d'évaluation dans le temps et de mémoire à des traits non génétiques (opinion politique, goût, caractère, état d'esprit...)</p>


<h2 id="engine">Moteur : reproduction et transmission du génome</h2>

<h3>Auto-fertilisation</h3>
<h3>Clonage</h3>
<h3>Reproduction Sexuée</h3>
<h3>Reproduction entre espèces</h3>

<h2>Modèle reproduction</h2>
<h3>Méiose</h3>
<h3>Cross-over</h3>
<h3>Mitose</h3>

<h3>Modéliser l'hétérochronie</h3>

<p>
    <a href="https://fr.wikipedia.org/wiki/H%C3%A9t%C3%A9rochronie#:~:text=L'h%C3%A9t%C3%A9rochronie%20est%20la%20modification,%C3%A0%20celles%20de%20ses%20anc%C3%AAtres.">L’hétérochronie</a> est la modification de la durée et de la vitesse du développement d’un organisme par rapport à celles de ses ancêtres.
</p>

<h4>Ontogenèse et phylogenèse</h4>

<p>
    Chaque individu au cours de sa vie possède une forme de programme de développement. Un trait commence à s'exprimer qu'à partir du moment où un autre trait s'est exprimé jusqu'à un certain stade (ou a fini de s'exprimer).
</p>
<p>
    Dans le modèle il faut donc conditionner l'expression d'une feature en fonction d'une autre.
</p>

<h4>Les types d'hétérochronie</h4>
<p>
    Tout d’abord, il existe deux catégories qui nous informent sur l’effet de l’hétérochronie: les changements qui impliquent un sous-développement par rapport à l’ancêtre sont regroupés dans la catégorie de la <em>pédomorphie</em> et ceux qui impliquent un surdéveloppement dans la catégorie de la <em>péramorphie</em>. Chacune de ces deux catégories peut ensuite être divisée en trois catégories qui nous informent sur la nature de l’hétérochronie. Soit l’hétérochronie provient d’un changement de vitesse dans le développement, d’un déplacement du début du développement ou d’un déplacement de la fin du développement.
</p>

<table>
    <thead>
        <tr>
            <th colspan="3" style="text-align: center;">Types d'hétérochronie</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Nature/Effet</td>
            <td>Pédomorphie(Sous-développement)</td>
            <td>Péramorphie
                (surdéveloppement)</td>
        </tr>
        <tr>
            <td>Vitesse du
                développement</td>
            <td>
                Néoténie (ralentissement)
            </td>
            <td>
                Accélération
            </td>
        </tr>
        <tr>
            <td>
                Déplacement du début
                du développement
            </td>
            <td>
                Post-déplacement
            </td>
            <td>
                Pré-déplacement
            </td>
        </tr>
        <tr>
            <td>Déplacement de la fin
                du développement</td>
            <td>Progenèse/Hypomorphisme
                (fin prématurée)</td>
            <td>
                Hypermorphose
                (fin retardée)
            </td>
        </tr>
    </tbody>
</table>

<h4>Déplacement du développement</h4>


<img src="../src/img/heterochronie.png" alt="Schémas hétérochronie">

<h4>Deceleration et Accélération du développement</h4>

<p>
    La néoténie et l'accélération se manifestent sous la forme d'une décélération ou accélération du développement d'un trait, d'une génération à la suivante. Le génome s'exprime pour produire, au final, le même effet (phénotype), mais le taux de développement (par exemple un taux de croissance) est plus faible chez le descendant (néoténie) ou plus fort chez le descendant (accélération). L'effet cumulé est identique soi
</p>

$$\int_{t_1}^{t_2} \tau_{1} dt = \int_{t_1'}^{t_2'} \tau_{0} dt$$


<p>
    où \(\tau_0\) est le taux de croissance d'un autre trait chez le parent, \(\tau_1\) chez le descendant, \(t_1\) et \(t_2\) sont les ages de l'individu définissant la période de l'expression du gènome chez l'ancêtre, \(t_1'\) et \(t_2'\) chez le descendant. Dans le cas de la néoténie ou l'accélération \( t_1 \equiv t_1'\). En effet, le début du développement n'est pas décalé.
</p>
<ul>
    <li>Néoténie :

        \(\tau_1 < \tau_0\), \(t_2\) recalculé pour que l'effet cumulé soit identique. Le développement arrive jusqu'au même stade que l'ancêtre, sauf qu'il prend beaucoup plus de temps. Ainsi, un trait jusque là exprimé seulement avant la maturité sexuelle peut se retrouver exprimé tout au long de la vie de l'individu </li>
    <li>
        Accélération :
        \(\tau_1 > \tau_0\), \(t_2\) recalculé pour que l'effet cumulé soit identique. Le développement arrive jusqu'au même stade que l'ancêtre, sauf qu'il prend beaucoup moins de temps.
    </li>
</ul>


<h4>Dans le modèle</h4>

<p>

</p>


<h2>Génération d'une documentation interactive automatique</h2>

<p>Générer une documentation automatiquement décrivant l'API de chaque Feature dans un projet donné. Cette documentation aidera grandement l'utilisateur a designer ses modèles de données et aussi à les utiliser dans son propre programme.</p>


<h2>Usage de la bibliothèque (dans les grandes lignes)</h2>
<p>La bibliothèque sera open-source (évidemment). Le code sera accessible depuis un dépot public. Le code source sera découpé en au moins deux composants:</p>
<ul>
    <li>code source moteur de la lib (tout ce qui fera tourner le modèle)</li>
    <li>code source des éditeurs, générateur doc, bac à sable</li>
</ul>
<p>On pourra imaginer à terme de faire des éditeurs et du bac à sable une web app: éditeur en ligne, création d'une store où les gens peuvent partager leur design et les télécharger (création d'une communauté). Chaque design aura sa doc.</p>

<p>En tant qu'utilisateur je veux intégrer cette library pour mon projet :</p>
<ul>
    <li>Je l'installe (avec ses dépendances) dans mon projet (sûrement via npm ou yarn). J'importe seulement le moteur dans mon projet</li>
    <li>Soit:
        <ul>
            <li>j'ai envie de créer mes propres design ou éditer design existants, je lance les éditeurs et je travaille dessus. Quand je suis satisfait, que j'ai testé dans le bac à sable j'exporte les données (sous format d'un fichier). Les données comprennent: les supports génétiques, les features, les espèces, les mutations etc...</li>
            <li>j'ai pas envie d'en faire moi même, d'autres gens en ont peut etre fait des mieux qui me correspondent ou pourraient me servir de base. Je récupère un design de quelqu'un (un fichier) (téléchargable en ligne sur le store), je l'importe, je l'édide et je l'exporte.</li>
        </ul>
    </li>
    <li>J'importe mes fichiers de design dans mon projet</li>
    <li>Je fabrique sûrement un fichier de configuration global demandé par la bibliothèque pour initialiser des choses (sécurité, gestion du temps, gestion des erreurs, generation pop, blabblabla...)</li>
    <li>J'utilise le tout pour fabriquer mon programme !</li>
</ul>

<p>Voici un pseudo code de l'utilisation de la bibliothèque (juste pour donner une idée)</p>


<code class="pseudo-code">
    <pre>
 import * as glib from "moteur"

 //Je crée une population initiale  de 50 individus, 
 //de l'espece 'espece#1' que j'ai designé
 const population = glib.generatePopulation('espece#1', 50)
 ...
 //Mon programme arrive à un point
 //où je veux déclencher une mutation designée
 const result = glib.triggerMutation('nomMutation') 
 ...
 //Deux individus se reproduisent et donnent une descendance de 10 individus:
 const offspings = glib.reproduce(individu1,individu2, 10)
 ...
 //Une fleur s'autoféconde pour fabriquer un nombre aléatoire de descendants
 const flowers = glib.reproduce(flower, random(10,100))
 ...
 //Deux individus se reproduisent, le nombre de descendant 
 //est borné par une feature 'capaciteGestation'
 const offspings = glib.reproduce(individu1,individu2, 
 random(1, get_phenotype(individu2,'capaciteGestation')))
 ...
 const killed = glib.kill(population)
 ...
//j'ai déjà ma propre structure de données/objet
//Fish avec son comportement
const fish = new Fish('toto')
console.log(fish) // = {foo:'toto'}
//je veux qu'il puisse se reproduire, le rendre
//genetique
fish = glib.setSpecie(fish, 'espece#1')
//fish dispose maintenant de toutes les features
//de l'espce#1 et peut se reproduire
const babyFish = glib.reproduce({fish, args: {'bar'}},fish2)
//babyFish a conservé tout ce dont il hérite
//de sa structure originelle
console.log(babyFish) // = {foo:'bar', phenotype: {....}} 

//Je veux savoir si mon parent a subi une mutation (provoquée par un accident nucléaire)
//et a commencé à développer un 3e bras
parent = glib.getParent(individu)
troisiemeBras = glib.getPhenotypes(parent,'troisiemeBras')
if(troisiemeBras)
    //Do stuff

        </pre>
</code>




<h2>Exemples : reproduction de cas connus</h2>

<h3>Lapins</h3>
<h3>Snapdragons (dominance incomplète)</h3>
<h3>Groupe sanguin chez l'Homme (codominance)</h3>