<?php
include('helper.php');
require_once(get_url('header'));
require_once(get_url('navbar'));

if (empty($_GET))
    require_once('pages/home.php');

if (isset($_GET['target']) && 'home' === $_GET['target'])
    require_once('pages/home.php');

if (isset($_GET['target']) && 'models' === $_GET['target'])
    include(get_url('models'));

if (isset($_GET['target']) && 'modelisation' === $_GET['target'])
    include(get_url('modelisation'));

if (isset($_GET['target']) && 'components' === $_GET['target'])
    include(get_url('components'));
    
require_once(get_url('footer'));
