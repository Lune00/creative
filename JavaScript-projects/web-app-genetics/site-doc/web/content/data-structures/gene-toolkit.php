<h3 id="support-génétique">Support génétique</h3>
<p>Un support génétique est une séquence en binaire (de 0 et de 1) </p>
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
            <td>\( N \ge 1\)</td>
        </tr>
        <tr>
            <td>Nombre de bits <code>n</code></td>
            <td>Nombre de bits sur lequel est encodé chaque gène du support : l’utilisateur
                pourra choisir d’encoder des gènes sur des structures allant de 1 à 8 bits
                (limite arbitraire). Ce paramètre défini par défaut le nombre de variations d’un
                même gène (allèles) accessibles. Par exemple, sur un support à 2 bits on a 4
                valeurs possibles : 00 (0), 01 (1), 10 (2) et 11 (3). On a donc, au maximum 4
                allèles pour ce gène dans notre « réservoir ». Sur 8 bits on a 256 valeurs
                possibles, donc 256 allèles possibles pour un même gène. La structure binaire
                est suffisante pour créer assez de variations (pas besoin de 4 caractères AGCT).
            </td>
            <td>Integer</td>
            <td>\( 1 \le n \le 8 \)</td>
        </tr>
        <tr>
            <td>Rareté d'une allèle \(r\)</td>
            <td>Sur les allèles disponibles on peut définir une rareté, un nombre qui sert au
                moment de la génération de populations. Ce nombre permettra de définir chance
                qu'un individu généré (non issu d'une reproduction) porte cet allèle
                initialement. </td>
            <td>Float</td>
            <td>\( 0 \le r \le 1 \)</td>
        </tr>
        </tr>
        <tr>
            <td>Allèles disponibles <code>n<sub>a</sub></code></td>
            <td>Le réservoir d'allèles disponibles est par définition définie par le nombre de
                bits sur lequel est encodé un gène. L’utilisateur pourra décider de n’utiliser
                qu'un sous-ensemble de ce réservoir s’il le souhaite. <strong>Une allèle est une
                    valeur</strong> possible d'un gène. Elle peut donc muter dans l'espace
                défini par le gène vers une autre valeur. </td>
            <td>(Integer...)</td>
            <td>\( 1 \le n_a \le N^{2} \)</td>
        </tr>
        <tr>
            <td>Relations entre allèles <code>U</code></td>
            <td>Tableau de coefficients dont chaque valeur permet de calculer la contribution de
                chacune des 2 allèles du même gène à l’évaluation du support génétique.
                L’utilisateur pourra générer ces coefficients de manière aléatoire ou suivant
                des règles prédéfinies, ou les écrire manuellement (il y a toujours le contrôle
                total si on le souhaite).</td>
            <td>[Float]</td>
            <td>
                \( n_a(n_a+1)/2\) coefficients nécessaires pour évaluer toutes les combinaisons
                possibles, voir <a href="#table-genetic-support-summary">ce tableau</a>
            </td>
        </tr>
    </tbody>
</table>

<p>Pour résumer, l’évaluation d’un support génétique (et la production d’une valeur) se fait en
    évaluant pour chacun de ses gènes la paire d’<a href="https://fr.wikipedia.org/wiki/All%C3%A8le">allèles</a> (une allèle sur chaque <a href="https://fr.wikipedia.org/wiki/Chromosome_homologue">chromosome homologue</a>)
    correspondante. Les relations entre allèles permettent de calculer la
    <strong>valeur</strong> du support génétique.
</p>



<h4>Dominat/Récessif, dominance incomplète et codominance</h4>
<p>
    <a href="https://fr.wikipedia.org/wiki/All%C3%A8le#Relations_entre_all%C3%A8les">Plusieurs relations entre allèles</a> existent. Le modèle se propose de modéliser 3 d'entre elles :

</p>


<ul>
    <li><strong>Dominant/récessif :</strong> un allèle récessif demande l'homozygotie d'un gène pour pouvoir s'exprimer. Autrement dit, soit \(a-B\) deux allèles du même gène, a est récessif (et B est dominant) si \(u(a,B)=0\). Ce gène est évalué à \(B\)</li>
    <li><strong> Dominance incomplète :</strong> aucun des allèles qui déterminent le caractère est dominant, les deux s'expriment et le caractère est un mélange des deux contributions. Autrement dit, soit \(a-b\) deux allèles du même gène, a et b ont une dominance incomplète si \( u(a,b) \in \left] 0 : 1\right[ \). Ce gène est évalué à {\(A: u(a,b), B: 1-u(a,b)\)}. En ce sens, le modèle Dominant/récessif n'est qu'un cas particulier de dominance incomplète.</li>
    <li><strong>Codominance :</strong> les deux allèles s'expriment en même temps, et le trait est l'expression conjointe des deux allèles.Autrement dit, soit \(A-B\) deux allèles du même gène, il faut donner au coefficient une valeur distincte pour prendre en compte ce cas. On pose par définition la valeur \(u(A,B)=-1\) pour symboliser ce cas. L'évaluation du gène retourne la valeur \(AB\). Dans ce cas, deux allèles peuvent produire 3 valeurs distinctes : A , B et AB </li>

    <li><strong>Allèle inerte :</strong>on verra à la section sur <a href="#mutations">les mutations</a> qu'une allèle peut devenir inerte, c'est à dire qu'elle n'exprime plus rien. Une allèle inerte est toujours récessive, si deux allèles inertes sont sur le même gène le gène ne renvoie aucune évaluation.</li>
    <li><strong>Allèle létale :</strong>: si cette allèle s'exprime l'individu meurt</li>
</ul>


<p>
    Voici un tableau résumant les valeurs prises par les coefficients pour chaque type de relation entre allèles, ainsi que le résultat de l'évaluation d'un gène \(A-B\). L'évaluation produit un ensemble clé:valeur noté \( \{ A: w_A , B: w_B \} \) où \(A\) est l'identifiant de l'allèle A et \(w_A\) son poids dans l'expression du gène. Si le poids est nul l'allèle n'est pas exprimé, s'il est égal à 1 on écrira \( \{ A: 1 \} \equiv \{ A\} \equiv A \). S'il n'y qu'un gène on pourra écrire \( \{ A\} \equiv A \)
</p>
<table id="table-genetic-support-summary">
    <thead>
        <tr>
            <th colspan="5">Supports génétiques</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Relation</td>
            <td>Valeurs du coefficient</td>
            <td>Evaluation</td>
        </tr>
        <tr>
            <td>Dominant/Récessif</td>
            <td>\(u(A,B) \in \{0 , 1\}\)</td>
            <td>\( A \) ou \( B \) </td>
        </tr>
        <tr>
            <td>Dominance incomplète</td>
            <td>\(u(A,B) \in \left]0:1\right[\)</td>
            <td>\( \{ A: u(A,B) , B: 1-u(A,B) \} \)</td>
        </tr>
        <tr>
            <td>Codominance</td>
            <td>\(u(A,B) = -1\)</td>
            <td>\( \{ AB: 1 \}\)</td>
        </tr>
        <tr>
            <td>Allèle inerte \(A\)</td>
            <td>\(u(A,B) = 0, \forall B\)</td>
            <td>\( \{ B: 1 \}\)</td>
        </tr>
        <tr>
            <td>Allèles inertes \(A\) et \(B\) </td>
            <td>\(u(A,B) = u(B,A) = 0\)</td>
            <td>\( \{ \}\)</td>
        </tr>
    </tbody>
</table>

<p>
    La valeur d'un allèle est son code binaire (ou un alias pour ce code). La valeur et le sens seront défini au niveau d'une <a href="#features">feature</a>. Soit un gène codé sur 1 bit avec \(A \equiv 0\) et \(B \equiv 1\). Si le gène mute de 0 à 1, la valeur du gène passe de A à B.
</p>


<h4 id="exemple--support-génétique-continu">Exemple 1 :</h4>
<p>Prenons un support génétique :</p>
<ul>
    <li>codé sur 3 gènes</li>
    <li>chaque gène est codé sur 2 bits</li>
    <li>Allèles disponibles : toutes, soit
        <ul>
            <li>00 ( A )</li>
            <li>01 ( B )</li>
            <li>10 ( C )</li>
            <li>11 ( D )</li>
        </ul>
    </li>
</ul>
<p>Initialisons le tableau des relations entre allèles :</p>
<div class="center-container">
    <table>
        <tbody>
            <tr>
                <td></td>
                <td>A</td>
                <td>B</td>
                <td>C</td>
                <td>D</td>
            </tr>
            <tr>
                <td>A</td>
                <td>1</td>
                <td>0.3</td>
                <td>0.7</td>
                <td>1</td>
            </tr>
            <tr>
                <td>B</td>
                <td>-</td>
                <td>1</td>
                <td>0.2</td>
                <td>0.4</td>
            </tr>
            <tr>
                <td>C</td>
                <td>-</td>
                <td>-</td>
                <td>1</td>
                <td>0.5</td>
            </tr>
            <tr>
                <td>D</td>
                <td>-</td>
                <td>-</td>
                <td>-</td>
                <td>1</td>
            </tr>
        </tbody>
    </table>
</div>

<p>On a par définition</p>
$$u(A,B) = 1 - u(B,A) $$
<p>si A et B ne sont pas codominants ou tous les deux inertes. Pour le cas de codominance on a défini une valeur arbitraire</p>
$$u(A,B) = u(B,A) = -1 $$

<p>On peut noter que l'allèle D est récessif vis à vis de A qui est dominant. Dans tous les autres rapports d'allèles nous sommes dans un cas de dominance incomplète. Évaluons à présent un individu qui posséderait un support génétique initialisé comme suit :</p>
$$(a-b)(c-b)(a-d)$$

<p>L’individu est <a href="https://fr.wikipeda.org/wiki/H%C3%A9t%C3%A9rozygote">hétérozygote</a> pour chacun des 3 gènes. L'évaluation du support génétique donne </p>

$$ v = \{ A:1.3, B:0.9, C:0.8 \}$$

<p>On peut voir que si le support génétique est constitué de plusieurs gènes il suffit d'ajouter les contributions de chaque gène.</p>

<h4>Exemple 2</h4>

<p>Reprenons le même support génétique :</p>
<ul>
    <li>codé sur 3 gènes</li>
    <li>chaque gène est codé sur 2 bits</li>
    <li>Allèles disponibles : 3 sur les 4 disponibles, soit
        <ul>
            <li>00 ( A )</li>
            <li>01 ( B )</li>
            <li>10 ( C )</li>
        </ul>
    </li>
</ul>
<p>Construisons un autre tableau de relations entre allèles :</p>
<div class="center-container">
    <table>
        <tbody>
            <tr>
                <td></td>
                <td>A</td>
                <td>B</td>
                <td>C</td>
            </tr>
            <tr>
                <td>A</td>
                <td>1</td>
                <td>-1</td>
                <td>1</td>
            </tr>
            <tr>
                <td>B</td>
                <td>-</td>
                <td>1</td>
                <td>0.5</td>
            </tr>
            <tr>
                <td>C</td>
                <td>-</td>
                <td>-</td>
                <td>1</td>
            </tr>
        </tbody>
    </table>
</div>

<p> Évaluons à présent un individu qui posséderait un support génétique initialisé comme suit :</p>
$$ (C-B)(A-C)(A-B) $$


<p>L’individu est <a href="https://fr.wikipeda.org/wiki/H%C3%A9t%C3%A9rozygote">hétérozygote</a> pour chacun des 3 gènes. L'évaluation du support génétique donne </p>
$$ v = \{ AB: 1, A:1, B:0.5, C:0.5 \}$$

<p>Les allèles A et B sont codominantes, elles s'expriment donc toutes les deux mais leurs effets ne se combinent pas, elles produisent une nouvelle valeur \(AB\), un nouveau phénotype.</p>

<h3>Sur les allèles</h3>

<p>
    Un allèle est un code binaire, une variation d'un gène. Son code binaire est son identifiant, qu'on pourra surcharger avec un nom. Un allèle peut être déclaré :
</p>

<ul>
    <li>Disponible : l'allèle est accessible lors de l'initialisation d'une population d'individus</li>
    <li>Mutant : non accessible par défaut, seulement par mutation de son code génétique</li>
</ul>
<p>Un allèle pourra muter </p>

<ul>
    <li>vers un allèle existant (Disponible), équivalent à du brassage génétique</li>
    <li>vers un allèle mutant (Mutant), introduction d'un nouvel allèle dans la population</li>
</ul>