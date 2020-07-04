set nocompatible
filetype off

set encoding=utf-8
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

"if !has("gui_running")
set timeout timeoutlen=1000 ttimeoutlen=100
set <M-n>=n
set <M-p>=p
set <M-r>=r
set <S-F3>=[25;*~
"endif

let g:go_list_type = "quickfix"
map <M-r> :GoReferrers<cr>
map <M-n> :cnext<cr>
map <M-p> :cprevious<cr>
"map <M-x> :echo "ALT-x pressed"<cr>
"noremap <S-F4> :echo "ALT-F2 pressed"<cr>
noremap <F5> :Continue<cr>
noremap <F7> :Step<cr>
noremap <S-F7> :Finish<cr>
noremap <F8> :Over<cr>

" run :GoBuild or :GoTestCompile based on the go file
function! s:build_go_files()
  let l:file = expand('%')
  if l:file =~# '^\f\+_test\.go$'
    call go#test#Test(0, 1)
  elseif l:file =~# '^\f\+\.go$'
    call go#cmd#Build(0)
  endif
endfunction
autocmd FileType go nmap <S-F9> :<C-u>call <SID>build_go_files()<CR>
"autocmd FileType go nmap <S-F9>  <Plug>(go-build)
autocmd FileType go nmap <C-F5>  <Plug>(go-run)

" key mapping for delete/paste
"let mapleader = "\<SPACE>"
let mapleader = ","
vnoremap <Leader>y "+y
nnoremap <Leader>y "+y
vnoremap <Leader>d "+d
nnoremap <Leader>d "+d
vnoremap <Leader>p "+p
nnoremap <Leader>p "+p
"inoremap <Leader>p <ESC>"ap
vnoremap <Leader>P "+P
nnoremap <Leader>P "+P
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
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'preservim/nerdtree'
Plugin 'Yggdroot/LeaderF'
Plugin 'fatih/vim-go'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

set nu

" Explorer
" let g:netrw_banner = 0
" noremap <Leader>be :Explore<CR>
noremap <Leader>t :NERDTreeToggle<CR>
nnoremap <Leader>d :bn<CR>:bd #<CR>
let NERDTreeMinimalUI=1
let NERDTreeShowHidden=1
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif

set completeopt=longest,menu
let g:ycm_key_invoke_completion = '<F9>'
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'
let g:ycm_always_populate_location_list = 1
let g:ycm_key_list_stop_completion = ['<C-y>', '<CR>']
nnoremap <Leader>j :YcmCompleter GoTo<CR>

let g:airline#extensions#tabline#enabled = 1
if has("gui_running")
    let g:airline_theme='silver'
else
    " let it work in tmux
    set background=dark
    set t_Co=256
endif
" map <C-Tab> :bn<CR>
" map <C-S-Tab> :bp<CR>
"

" LeaderF
let g:Lf_WindowPosition = 'popup'
let g:Lf_PreviewInPopup = 1
noremap <Leader>e :LeaderfMru<cr>
"<Leader>f by default
"let g:Lf_ShortcutF = '<Leader>o'
"let g:Lf_CommandMap = {'<C-K>': ['<C-P>'], '<C-J>': ['<C-N>']}

" debug
:packadd termdebug
let g:termdebug_wide=1
set makeprg=make\ -C\ build
noremap <silent> <F9> :make<CR><CR>:cw<CR>

" window layout
set sessionoptions=blank,winsize,tabpages,resize

" clang-format
" map <C-K> :py3f ./.vim/clang-format.py<cr>
map = :py3f ~/.vim/clang-format.py<cr>
autocmd FileType c,cpp,objc map <buffer> = :py3f ~/.vim/clang-format.py<cr>

function! Formatonsave()
  let l:formatdiff = 1
  py3f ~/.vim/clang-format.py
endfunction
autocmd BufWritePre *.h,*.c,*.cc,*.cpp call Formatonsave()


"set color scheme
if has("gui_running")
    colorscheme still
endif
set guifont=Monospace\ 11
set guioptions-=T
