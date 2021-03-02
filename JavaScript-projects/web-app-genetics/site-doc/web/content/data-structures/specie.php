
<h3 id="espèces">Espèce</h3>


<p>
    Une espèce est définie par un ensemble de features designées préalablement. Une feature peut être utilisée pour plusieurs espèces. A cela s’ajouteront des paramètres (à définir), des caractères irréductibles (non codés par du support génétique). Ces « méta paramètres »seront utiles pour le modèle (pour simplifier des choses).
</p>




<p class="question">
    Tout ce modèle est très «génétique centré», est ce qu’on pourrait imaginer des caractères non réductibles à l’expression du génome, à définir directement sur l’espèce (des méta caractères, épigénétique...)?
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
            <td>Un nom donné à l'espece</td>
            <td>String</td>
            <td>Unique</td>
        </tr>
        <tr>
            <td>Features (nombre \(n_f\))</td>
            <td>Liste de features caractérisant l'espece. Chaque feature sélectionnée embarque avec elle son support génétique et ses dépendances</td>
            <td>Liste Features</td>
            <td>Aucune</td>
        </tr>
        <tr>
            <td>Nombre de paires de chromosomes \(n_p\)</td>
            <td>Toutes les espèces sont diploïdes mais le nombre de paires de chromosomes peut être défini pour chaque espèce (brassage)</td>
            <td>Integer</td>
            <td>Au moins un gène par chromosome, \(n_p \leq \sum_{i=1}^{n_f} N_i\)</td>
        </tr>
        <tr>
            <td>Placement des gènes sur les chromosomes</td>
            <td>Quel gène va sur quel chromosome. Éditeur permet de placer automatiquement, possibilité de le faire à la main, avec un éditeur Drag&Drop graphique.</td>
            <td>-</td>
            <td>-</td>
        </tr>
        <tr>
            <td>Gènes non codant</td>
            <td>En plus des gènes codants, générer des séquences génétiques non codantes aléatoires (%, disposition etc..)</td>
            <td>-</td>
            <td>-</td>
        </tr>
        <tr>
            <td>Type de reproduction</td>
            <td>Auto-fertilisation, clonage, reproduction sexuée</td>
            <td>String</td>
            <td>Appartenir aux types de reproduction définie par le système</td>
        </tr>
        <tr>
            <td>Peut se reproduire avec d'autres espèces?</td>
            <td class="question">
                Sous quelles conditions, comment ça marcherait ? Je ne souhaite pas que la notion d’espèce soit trop « cloisonnante », mais plutôt comme c’est en vrai, un concept aux contours évoluant avec le temps, « un flux ». C’est pratique pour programmer. En soi le modèle est piloté par des données donc tout est imaginable. On voudrait bien que des individus d’espèces différentes se croisent ! Sous quelles conditions (proximité génétique : valeur seuil de % génome commun ?) ? Quel génome résultant (chaque individu apporte tout ou une partie de ses features) ? Là ton regard pour être très précieux sur ces aspects pour imaginer des mécanismes.
            </td>
            <td>{booléan, proximité : Float}</td>
            <td>??</td>
        </tr>
        <tr>
            <td>Autoriser Mutations</td>
            <td>
                Choisir si le génome de l'espèce peut muter
            </td>
            <td>Boolean</td>
            <td>Aucune</td>
        </tr>


    </tbody>
</table>