Je n'ai pas encore bien compris comment fonctionne vimwiki avec les paths pour les templates, et les dossiers du type [dossier:entree].
A piger. Le .vimrc definit le path comme suit:

let g:vimwiki_list = [{
    \ 'path': '~/tmp_game_mechanics/game/Orba/vimwiki/',
    \ 'template_path': '~/tmp_game_mechanics/game/Orba/vimwiki/templates/',
    \ 'template_default': 'default',
    \ 'template_ext': '.html'}]

Il faut que le wiki sur lequel on travaille soit dans le dossier path sinon le plugin n'arrive pas a trouver les templates.
