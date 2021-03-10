<h3>Hétérochronie</h4>


    <p>
        L’<a href="https://fr.wikipedia.org/wiki/H%C3%A9t%C3%A9rochronie#:~:text=L'h%C3%A9t%C3%A9rochronie%20est%20la%20modification,%C3%A0%20celles%20de%20ses%20anc%C3%AAtres.">hétérochronie</a> est la modification de la durée et de la vitesse du développement d’un organisme par rapport à celles de ses ancêtres. Ces modifications sont la conséquence de la mutation de certains gènes du développement qui contrôlent le développement et la mise en place des organes. Ainsi, de grands changements au point de vue du phénotype peuvent survenir dans l’organisme grâce à l’hétérochronie, sans pour autant qu’il y ait de modifications génétiques importantes.
    </p>
    <p>
        Les hétérochronies sont divisées en deux grandes catégories : les changements qui impliquent un sous-développement par rapport à l’ancêtre sont regroupés dans la catégorie de la <em>pédomorphie</em> et ceux qui impliquent un surdéveloppement dans la catégorie de la <em>péramorphie</em>.
    </p>

    <p>
        Chacune de ces deux catégories peut ensuite être divisée en trois catégories qui nous informent sur la nature de l’hétérochronie. Soit l’hétérochronie provient d’un changement de vitesse dans le développement, d’un déplacement du début du développement ou d’un déplacement de la fin du développement.
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
    <figure>
        <img src="../src/img/heterochrony-cartoon.webp" alt="Cartoon" style="width:80%;">
        <figcaption style=" background-color: #fff;
    color: black;
    font: italic smaller sans-serif;
    padding: 3px;
    text-align: center;">A hypothetical animal which, during its ontogeny, undergoes a number of morphological changes. Peramorphic descendants develop “beyond” the ancestor; padomorphic descendants retain juvenile ancestral features. In hypermorphosis, growth stops later; in acceleration, the horns and tails grow faster; in predisplacement, the horns and tail start growing earlier. In progenesis, growth stops earlier; in neoteny, the horns and tail grow at a slower rate; in postdisplacement, the horns and tail start their growth relatively later. Reproduced with permission from McNamara (<a href="https://evolution-outreach.biomedcentral.com/articles/10.1007/s12052-012-0420-3">source</a>) </figcaption>
    </figure>

    <p>
        Ces différents types d'hétérochronie sont représentés sur le graphe ci dessous, où l'on compare pour un trait, le phénotype d'un descendant par rapport à celui de son ancêtre.
    </p>

  

    <figure>
        <img src="../src/img/heterochrony-graph.png" alt="Graphe des hétérochronies">
        <figcaption style="
    font: italic smaller sans-serif;
    padding: 3px;
    text-align: center;"> Graphe représentant les différentes hétérochronies dans le temps. Le développement du trait de l'ancêtre, entre \(t_1\) et \(t_2\) est représenté en noir </figcaption>
    </figure>

    <p>
    Ces six hétérochronies peuvent être combinées pour rendre compte de n'importe quelle modification du processus de développement chez le descendant.
    </p>

    <h4>Composant général</h4>

    <p>Voici dans le moteur comment pourrait être designé ce composant. Pour cela nous nous appuyons sur le composant de gène de développement discuté dans la section précédente. Pour rendre compte de n'importe quelle hétérochronie il nous faut ajouter au composant gène de développement 3 mutations possibles. </p>

    <p>
   
    </p>

    <img src="../src/img/heterochrony-component-general.png" alt="Néotenie" style="width:120%;">

   
    
    <h4>Déplacement du développement : </h4>


    <h4>Deceleration et Accélération du développement</h4>

    <p>
        La néoténie et l'accélération se manifestent sous la forme d'une décélération ou accélération du développement d'un trait, d'une génération à la suivante. Le génome s'exprime pour produire, au final, le même effet (phénotype), mais le taux de développement (par exemple un taux de croissance) est plus faible chez le descendant (néoténie) ou plus fort chez le descendant (accélération). L'effet cumulé (le phénotype final) est identique pour chaque génération donc par définition
    </p>

    $$\int_{t_1}^{t_2} \tau dt = \int_{t_1'}^{t_2'} \tau' dt$$


    <p>
        où \(\tau\) est le taux de croissance du trait chez le parent, \(\tau'\) chez le descendant. \(t_1\) et \(t_2\) définissent la période de l'expression du gènome chez l'ancêtre, \(t_1'\) et \(t_2'\) chez le descendant. Dans le cas de la néoténie ou l'accélération \( t_1 \equiv t_1'\). En effet, le début du développement n'est pas décalé. Pour conserver l'égalité ci dessus (le même développement) on a donc nécessairement
    </p>

    $$t_2' = \frac{\tau}{\tau'}(t_2 - t_1) + t_1 $$
    <ul>
        <li>Néoténie :

            \(\tau' < \tau \) soit \( t_2'>t_2\). Le développement arrive jusqu'au même stade que l'ancêtre, sauf qu'il prend beaucoup plus de temps. Ainsi, un trait jusque là exprimé seulement avant la maturité sexuelle peut se retrouver exprimé tout au long de la vie de l'individu
        </li>
        <li>
            Accélération :
            \(\tau' > \tau \) soit \( t_2'< t_2\). Le développement arrive jusqu'au même stade que l'ancêtre, sauf qu'il prend beaucoup moins de temps. Le descendant a des caractères adultes avant d'avoir atteint la maturité sexuelle </li>
    </ul>

    <p>
        Pour modéliser la néoténie et l'accélération il faut que si une mutation opère sur le taux de développement elle agisse également sur le temps \(t_2'\), pour conserver la même expression cumulée du génome que chez l'ancêtre.
    </p>

    <img src="../src/img/neoteny-component.png" alt="Néotenie" style="width:80%;">