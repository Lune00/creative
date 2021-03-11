<?php
$active = 'modelisation';
require_once('../template-parts/header.php');
require_once('../template-parts/navbar.php');
?>

<h2>Composants et modèlisations</h2>

<ul class="toc">
    <li><a href="#ontogenese">Ontogenèse</a></li>
    <li><a href="#heterochrony">Hétérochronies</a></li>
    <li><a href="#features">Reproduction</a></li>
</ul>


<p>
    On discute ici des façons de modéliser des phénomènes courants et intéressants d'un point de vue de la phylogénie ou de l'ontogénie. On montre également l'approche <em>composant</em> du modèle. L'idée est de pouvoir construire des composants et les réutiliser ensuite sans avoir besoin de soulever le capot. Ainsi la bibliothèque s'enrichit et permet de monter facilement en complexité, pour créer des individus de plus en plus complexes et intéressants à <em>étudier</em>. Les composants et leurs APIS seront décrits en détail dans le wiki, voir la page <a class="page-scroll" href="../pages/components.php">Bibliothèque composants</a>
</p>

<?php
require_once('../content/components/ontogenesis.php');
require_once('../content/components/heterochrony.php');
require_once('../template-parts/footer.php');
