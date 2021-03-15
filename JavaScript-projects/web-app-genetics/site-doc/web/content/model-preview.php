<h2 id="ce-quon-fabrique">Qu'est ce qu'on cherche à faire ?</h2>
<p>Construire une bibliothèque que n’importe qui peut installer et utiliser dans ses propres
    projets informatiques. Cette bibliothèque est constituée d’un moteur (un ensemble de
    fonctions implémentant le modèle) ainsi que de données (avec un format bien défini)
    exportables. Ainsi, les utilisateurs pourront partager leurs design entre
    eux (features, especes) et une communauté
    <em>pourrait</em> se former construisant par itération des designs de plus en plus élaborés.
</p>
<p>Pour permettre cela tout en étant <em>user-friendly</em> des éditeurs avec interface
    graphique seront développés. Il y aura un éditeur pour :</p>
<ul>
    <li>les <a href="./models.php#genome">support génétique</a></li>
    <li>les <a href="#features">traits phénotypiques</a></li>
    <li>les  <a href="#mutations">mutations</a></li>
    <li>les <a href="#esp%C3%A8ces">lignées</a></li>
    <li>les <a href="#environment">environnement</a></li>
    <li>Un bac à sable pour tester et explorer rapidement ses designs</li>
    <li>Un générateur de documentation desenvironment allèles et features de chaque espèce dans lequel il
        sera facile de chercher (nom, données retournées par une feature etc...)</li>
</ul>
<p>Les éditeurs permettront d’éditer, importer, exporter, dupliquer, supprimer, ces 3 type de
    données facilement. Ces données seront ensuite importées dans le projet informatique de
    l’utilisateur et celui-ci, après import du moteur, pourra faire tourner le modèle dans le
    but qu’il s’est fixé.</p>
<h2 id="objectifs">Objectifs</h2>
<p>S’amuser. Fournir un moteur permettant de simuler des entités (biologiques ou non) possédant
    des phénotypes <strong>interprétables par
        l’utilisateur</strong>. Le phénotype de chaque individu résulte de l’évaluation d’un
    support génétique (principalement). Les entités pourront se reproduire et transmettre à leur
    descendance leur génome pour créer de l’hérédité, de la filiation (et de
    l’histoire). Ce génome pourra également être soumis à des mutations et évoluer.
    L’utilisateur pourra alors facilement simuler de la sélection et des populations au cours du
    temps dans son propre projet. Les espèces pourront muter, les populations évoluer etc. En
    somme, un gros bac à sable. Ce modèle pourrait avoir des ambitions plus générales. Car s’il
    vise principalement à simuler <em>de la vie</em>, le moteur pourrait être appliqué à
    d’autres <em>objets</em>. On peut penser par exemple à faire une filiation de langues (en
    utilisant des méthodes de <a href="https://fr.wikipedia.org/wiki/Philologie">philologie
        comparée</a> comme a pu le faire (sérieusement) Tolkien : utiliser des règles
    spécifiques de mutation qui permette de passer d’un mot ancêtre à un mot descendant et vice
    versa). En fait tout ce qui est sujet à itérations successives, tout objet qui« produit du
    nouveau a partir de lui même » pourrait être simulé.</p>
<h2 id="contraintes">Contraintes</h2>
<p>La contrainte forte du modèle c’est qu’il faut définir à l’avance des traits phénotypiques
    auxquels l’utilisateur pourra donner <strong>du sens</strong>. J’insiste là dessus car le
    but est de pouvoir <strong>interpréter fonctionnellement le phénotype pour prendre des
        décisions.</strong> Ce que j’entends par là c’est que si une espèce possède un trait
    phénotypique qui renvoie la valeur ‘foo’ il faut que cette valeur <strong>puisse</strong>
    (pas nécessairement) avoir un sens pour l’utilisateur dans son programme, qu'elle puisse être anticipée. En ce sens, le réservoir de phénotypes
    possibles doit <em>pouvoir</em> être contrôlé.</p>
<h2 id="composants-à-développer">Composants à développer</h2>
<p><img src="../src/img/project-components.png" alt="Composants" style="width:80%;"><br>
    Le projet se compose des composants suivants à concevoir et développer :</p>
<ul>
    <li>Le moteur (engine) :
        <ul>
            <li>Les structures de données (modèles) :
                <ul>
                    <li>Support génétique</li>
                    <li>Feature (traits phénotypiques)</li>
                    <li>Mutation</li>
                    <li>Espèce</li>
                    <li>Environnements</li>
                </ul>
            </li>
            <li>
                Ensemble de fonctions pour lire et interpréter les données
            </li>
        </ul>
    </li>
    <li>Les éditeurs graphiques (web) pour manipuler et lier les structures de données facilement</li>
    <li>Un bac à sable pour aider à prototyper et tester ses designs</li>
</ul>
<p>Les structures de données seront complexes et un éditeur graphique pour les manipuler sera
    indispensable. Ces éditeurs permettront d’importer et d’exporter les données
    facilement, de les éditer, dupliquer, supprimer. Le modèle est <em>piloté par les
        données</em>, ces structures sont capitales et doivent être manipulées et définies de
    manière rigoureuses.</p>
<h2 id="aperçu-général-du-modèle-génétique--du-génome-au-phénotype">Aperçu général du moteur</h2>
<p>L’utilisateur de la bibliothèque pourra faire évoluer des populations d’individus et
    évaluer les traits de chaque individu afin d'appliquer le traitement qu’il souhaite. Ces
    traits seront l’expression d’un génome <strong>diploïde</strong> porté par chaque individu,
    transmissible par reproduction sexuée, auto-fécondation ou clonage de génération en génération.</p>
<p>Le <em>support génétique</em> (encodé en binaire) lorsqu’il est évalué produit une valeur.
    Cette valeur est ensuite interprétée par une <em>feature</em> qui produit à son tour une
    valeur auquel l’utilisateur donne une dimension et une unité de mesure (une signification). Cette expression est à la fois le produit du génome mais aussi possiblement d'un <em>environnement</em>, notamment le temps.
    
    </p><p>
     L’expression de la feature est ensuite
    remontée au niveau du phénotype d'un <em>individu</em>. La valeur en sortie d’une feature peut servir d’entrée à une autre
    <em>feature</em> et ainsi de suite. Ainsi, le phénotype est le résultat de l’évaluation d'un réseau de features (possiblement)
    interdépendantes, fondé sur un support génétique. Le temps, des <em>environnements</em> ou directement l'utilisateur (à la manière d'un horloger) peuvent déclencer des mutations du matériel génétique, qui auront des répercusions sur les individus. A leur tour, les individus peuvent modifier les environnements.
</p>


<img id="general-model" class="modele-img" src="./../src/img/engine-overview.png" alt="Modèle général">


<p>Lors de la reproduction ou du clonage, le support génétique est transmis à l’aide de
    mécanismes connus de la biologie (mais nécessairement simplifiés) : mitose, méiose.</p>
<h2 id="notations">Notations</h2>
<ul>
    <li> \(a-B\) : allèles a et B sur le même locus d’une paire de chromosomes analogues. a est
        récessif et B est dominant</li>
    <li> \((a-B)(a-c)(B-B)\) : ensemble de couples d'allèles sur 3 gènes d’une paire de
        chromosomes analogues. L'ordre des couples n'a pas d'importance</li>
</ul>