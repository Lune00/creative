<?php

function get_url($filename)
{
    $root = realpath($_SERVER["DOCUMENT_ROOT"]);
    $dir_iterator = new RecursiveDirectoryIterator('.');
    $iterator = new RecursiveIteratorIterator($dir_iterator, RecursiveIteratorIterator::SELF_FIRST);
    foreach ($iterator as $file) {
        if (basename($filename, '.php') === basename($file, '.php'))
            return $file;
    }
    return null;
}

function url($filename){
    echo get_url($filename);
}

