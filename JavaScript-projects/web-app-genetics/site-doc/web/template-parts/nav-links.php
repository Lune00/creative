<?php require_once('helper.php'); ?>

<li class="nav-item <?php if ($active === 'home') echo "active" ?> "><a class="page-scroll" href="<?php echo '?target=home' ?>">Home</a></li>
<li class="nav-item <?php if ($active === 'models') echo "active" ?> "><a class="page-scroll" href="<?php echo '?target=models' ?>">Structure de données</a></li>
<li class="nav-item <?php if ($active === 'modelisation') echo "active" ?> "><a class="page-scroll" href="<?php echo '?target=modelisation' ?>">Modélisations</a></li>
<li class="nav-item <?php if ($active === 'components') echo "active" ?> "><a class="page-scroll" href="<?php echo '?target=components' ?>">Bibliothèque composants</a></li>