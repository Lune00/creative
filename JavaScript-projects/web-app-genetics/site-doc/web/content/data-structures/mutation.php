<h2 id="mutations">Mutations</h2>

<h3>Définition d'une mutation dans le modèle</h3>

<p>
    Une mutation est une modification rare, accidentelle ou provoquée de l'information génétique dans le génome. Dans le modèle une mutation pourrait être
</p>
<ul>
    <li>code génétique d'une allèle : transition vers une autre allèle, vers une allèle mutante ou vers une allèle inerte (code inconnu)</li>
    <li class="question">relation entre deux allèles. Est ce raisonnable ? Dans la vraie vie il peut y avoir une mutation qui rend une allèle jusque la récessive tout d'un coup dominante?</li>
    <li>Apparition d'un nouveau gène codant pour une feature</li>
    <li>Disparition d'un gène codant pour une feature</li>
    <li>Disparition d'un allèle</li>
    <li class="question">Autre idée?</li>
</ul>


<p>
    Le support génétique peut muter : par exemple un bit pourrait se décaler vers la gauche. Prenons un gène codé sur 8bits qui vaut initialement <code>00000001</code> (correspond à une allèle). Une mutation est déclenchée et un bit se décale) à <code>00000010</code> :

<ul>
    <li>soit j'ai défini une allèle mutante en amont, pris en compte dans ma feature</li>
    <li>soit je n'ai pas associé de valeur. L'allèle sera évaluée à <code>'unknown'</code> ou sera inerte.</li>
</ul>
</p>


<h3>Rôle des gènes non codants</h3>

<p>
    On peut imaginer introduire des gènes non codants sur les chromosomes. Par exemple :
    $$...\color{grey}0000000\color{red}10000100\color{blue}11011110\color{grey}11001100... $$

<ul>
    <li><span style="color:red;">Gène codant 1 allèle A </span></li>
    <li><span style="color:blue;">Gène codant 2 allèle B </span></li>
    <li><span style="color:grey;">Gène non codant </span></li>
</ul>



</p>

<p>
    Maintenant on peut imaginer une forme de mutation où chaque bit se décale de 1 pas sur la gauche. Le résultat serait cette séquence (me suis peut être trompé c’est chiant à faire)
</p>

$$...\color{grey}0000001\color{red}00010011\color{blue}01111011\color{grey}10011001... $$
<ul>
    <li><span style="color:red;">Gène codant 1 allèle C (par exemple) </span></li>
    <li><span style="color:blue;">Gène codant 2 allèle inconnu (par exemple) </span></li>
    <li><span style="color:grey;">Gène non codant </span></li>
</ul>
L'allèle du gène 1 est maintenant l'allèle <code>C</code> dans le modèle. On pourrait ainsi donner naturellement un rôle sympa aux séquences non codantes. Après je te laisse imaginer les opérations cools de mutation qu’on peut faire par des opérations très simples sur les bits.
</p>


<p>
    Si l'on souhaite faire une simulation plus bas niveau de brassage génétique et de mutations, en analysant le génome d'un individu sans lui donner du sens, on pourrait remplir utiliser uniquement du matériel non codant. Et appliquer des mutations dessus.
</p>

<h3>Paramètres (à compléter/modifier)</h3>

<p>
    Les mutations seront designées comme les supports génétiques, features et espèces.
</p>

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
            <td>Un nom donné à la mutation</td>
            <td>String</td>
            <td>Unique</td>
        </tr>
        <tr>
            <td>Cible</td>
            <td>Qui vise-t-elle, Liste de support génétique, Chromosome entier</td>
            <td>Support génétique (Liste de gènes) ou Gène (codant ou non)</td>
            <td>Au moins 1 gène visé</td>
        </tr>
        <tr>
            <td>Action</td>
            <td>Que fait elle sur sa cible</td>
            <td>Proposer des actions : décalage, substitution(nombre de bits concernés), aléatoire, éteindre/allumer (en faisant muter vers une allèle du système défini comme 'unknown') etc..</td>
            <td></td>
        </tr>
        <tr>
            <td>Déclenchement</td>
            <td>Proposer des déclenchements automatiques</td>
            <td>Chaque reproduction, aléatoire, fréquence etc...</td>
            <td></td>
        </tr>
        <tr>
            <td>Agressivité</td>
            <td>Permettre à la cible de résister ou non à la mutation. On définit un nombre de 0 à 100. On jette un dé, si le résultat est en dessus de ce nombre la mutation n'a pas lieu.</td>
            <td>Integer</td>
            <td>Entre 0 et 100 (arbitraire)</td>
        </tr>

    </tbody>
</table>

<p>
    Chaque mutation définie pourra être déclenchée automatiquement si elle a été configurée ainsi. Sinon l'utilisateur pourra toujours la déclencher manuellement quand il veut, en fonction des conditions de sa propre simulation (s'il simule un environnement par exemple), du genre
</p>

<code class="pseudo-code">
    <pre>
    //Déclenche manuellement une mutation
    mutation = triggerMutation('nomMutation')
    //Tous les individus concernés verront leur génome muter
        </pre>
</code>

<p>
    Chaque mutation sera loguée par le système.
</p>