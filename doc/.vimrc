set nocompatible
filetype off

set backspace=indent,eol,start
set incsearch
set hlsearch

set showcmd		" Show (partial) command in status line.
" set showmatch		" Show matching brackets.
set ignorecase		" Do case insensitive matching
set smartcase		" Do smart case matching
set autowrite		" Automatically save before commands like :next and :make
set hidden		" Hide buffers when they are abandoned

set number

" set tab width
set tabstop=4
set expandtab
set softtabstop=4

" set auto shift width
set shiftwidth=4

" set smart indent
set autoindent
set smartindent

" set title
set titlestring=%t

"turn syntax
syntax on

" key mapping for delete/paste
"let mapleader = "\<SPACE>"
let mapleader = ","
vnoremap <Leader>y "ay
nnoremap <Leader>y "ay
vnoremap <Leader>d "ad
nnoremap <Leader>d "ad
vnoremap <Leader>p "ap
nnoremap <Leader>p "ap
"inoremap <Leader>p <ESC>"ap
vnoremap <Leader>P "aP
nnoremap <Leader>P "aP
"inoremap <Leader>P <ESC>"aP

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'a.vim'
" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

set nu
set completeopt=longest,menu
let g:ycm_key_invoke_completion = '<F9>'
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'

" debug
:packadd termdebug

" window layout
set sessionoptions=blank,winsize,tabpages,resize

" clang-format
" map <C-K> :py3f ./.vim/clang-format.py<cr>
map = :py3f ./.vim/clang-format.py<cr>

function! Formatonsave()
  let l:formatdiff = 1
  py3f ./.vim/clang-format.py
endfunction
autocmd BufWritePre *.h,*.cc,*.cpp call Formatonsave()

