
<h3 id="espèces">Lignée</h3>


<p>
    Une lignée est définie par un ensemble de features designées préalablement. Une feature peut être utilisée pour plusieurs lignées. Une lignée est également définie par des méta-caractères, seulement utiles pour le modèle. En effet, dans la nature il n'y a <em>que des individus</em>. Ces paramètres sont définis dans le tableau ci-dessous.
</p>

<p>
    Deux individus appartenant à la même lignée peuvent se reproduire ensemble selon certaines conditions définies par l'utilisateur. S'inspirant du darwinisme, le concept d'espèce n'est pas <em>first-class</em> dans le modèle au sens où les <em>espèces n'existent pas dans la nature</em>. En effet, une espèce n'est rien d'autre qu'une boîte conceptuelle, un chausse-pied, qui définit les contours d'un flux généalogique à un instant donné. C'est une photographie a un instant t d'un flux d'individus partageant des caractéristiques communes et notamment la capacité de se reproduire entre eux.
</p>

<p>
    La notion d'espèce, utile pour raisonner, n'est donc pas inclus dans le modèle sinon en tant que label pour regrouper des individus entre eux, mais ce n'est pas un concept opérant. Il est laissé au soin de l'utilisateur de le définir selon ses propres besoins.
</p>
<p>
    Deux individus appartenant à des lignées différentes pourront également se reproduire entre eux en précisant des règles pour l'hérédité du génome et des features (addition, aléatoire, si features déjà en commun...).
</p>
<p>
    Il conviendra donc de définir des <em>barrières à la reproduction entre deux individus</em> pour que le modèle puisse proposer des ruptures dans le flux généalogique et donc une phylogénie. 
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
            <td>Un nom donné à la lignée</td>
            <td>String</td>
            <td>Unique</td>
        </tr>
        <tr>
            <td>Features (nombre \(n_f\))</td>
            <td>Liste de features caractérisant la lignée. Chaque feature sélectionnée embarque avec elle son support génétique et ses dépendances</td>
            <td>Liste Features</td>
            <td>Aucune</td>
        </tr>
        <tr>
            <td>Nombre de paires de chromosomes \(n_p\)</td>
            <td>Toutes les lignées sont diploïdes mais le nombre de paires de chromosomes peut être défini pour chaque espèce (brassage)</td>
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
            <td>Barrières à la reproduction</td>
            <td>
               Les barrières à la reproduction sont des features spéciales, qui permet à l'utilisateur de définir si deux individus peuvent encore se reproduire. On pourra y définir des règles automatiques (% génome en commun seuil etc...) Indiquer aussi barrière reproduction entre lignées et quelles conséquences de la reproduction
            </td>
            <td>Bloc spécial, voir plus bas. chaque individu devra implémenter ce bloc. Par défaut deux individus de la même lignée peuvent se reproduire ensemble et pas avec une autre lignée</td>
            <td>??</td>
        </tr>
        <tr>
            <td>Autoriser (activer) Mutations</td>
            <td>
                Choisir si le génome de la lignée peut muter
            </td>
            <td>Boolean</td>
            <td>Aucune</td>
        </tr>


    </tbody>
</table>