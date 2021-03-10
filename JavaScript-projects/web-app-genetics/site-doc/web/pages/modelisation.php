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

<?php
require_once('../content/components/ontogenesis.php');
require_once('../content/components/heterochrony.php');
require_once('../template-parts/footer.php');
