set backspace=2
filetype indent on
set autoindent
set shiftwidth=2
set number
set nobackup

set laststatus=2
colorscheme darkblue
set nocompatible
filetype plugin on
syntax on

noremap <Up> <NOP>
noremap <Down> <NOP>
noremap <Left> <NOP>
noremap <Right> <NOP>

"smart indent when entering insert mode whith i on enpty lines
function! IndentWithI()
    if len(getline('.')) == 0
        return "\"_ccO"
    else
        return "i"
    endif
endfunction

nnoremap <expr> i IndentWithI()

"Default configuration quand vimwiki et vimwiki_html sont a la racine:
"let g:vimwiki_list = [{
"  \ 'path': '~/vimwiki/',
"  \ 'template_path': '~/vimwiki/templates/',
"  \ 'template_default': 'default',
"  \ 'template_ext': '.html'}]

let g:vimwiki_list = [{
  \ 'path': '~/tmp_game_mechanics/game/Orba/vimwiki/',
  \ 'template_path': '~/tmp_game_mechanics/game/Orba/vimwiki/templates/',
  \ 'template_default': 'default',
  \ 'template_ext': '.html'}]

