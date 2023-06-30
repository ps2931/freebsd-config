"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Plugins
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
call plug#begin('~/.config/nvim/plugged')
    Plug 'catppuccin/nvim', { 'as': 'catppuccin' }
    Plug 'ellisonleao/gruvbox.nvim'
    Plug 'echasnovski/mini.nvim', { 'branch': 'stable' }
    Plug 'rust-lang/rust.vim'
    Plug 'dense-analysis/ale'
    Plug 'ibhagwan/fzf-lua', {'branch': 'main'}
    Plug 'nvim-treesitter/nvim-treesitter'
call plug#end()

filetype plugin indent on

let mapleader="\<Space>"

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set hidden
set history=500
set autoread
set laststatus=2
set noshowmode
set clipboard=unnamed,unnamedplus

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => VIM user interface
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set scrolloff=5
set number relativenumber
set wildmenu
set ruler
set cmdheight=1
set hidden
set backspace=eol,start,indent
set whichwrap+=<,>,h,l
set ignorecase
set smartcase
set hlsearch
set incsearch
set lazyredraw
set magic
set showmatch
set mat=1
set pumheight=12
set cursorline

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Colors and Fonts
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
syntax enable
set background=dark

lua << EOF
require("gruvbox").setup({
    transparent_mode = true,
})
vim.cmd("colorscheme gruvbox")
EOF

" Change Color when entering Insert Mode
autocmd InsertEnter * set nocursorline
" Revert Color to default when leaving Insert Mode
autocmd InsertLeave * set nocursorline

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Files, backups and undo
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nobackup
set nowb
set noswapfile

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Text, tab and indent related
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set expandtab
set smarttab
set shiftwidth=4
set tabstop=4
set linebreak
set textwidth=500
set autoindent
set smartindent
set nowrap

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Faster grep
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
if executable("rg")
  set grepprg=rg\ --vimgrep\ --smart-case\ --hidden
  set grepformat=%f:%l:%c:%m
endif
nnoremap <Leader>g :silent lgrep<Space>
nnoremap <silent> [f :lprevious<CR>
nnoremap <silent> ]f :lnext<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Debugging
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
packadd termdebug
let g:termdebug_wide = 1
let g:TermDebugging = 0
au User TermdebugStartPre let g:TermDebugging = 1
au User TermdebugStopPost let g:TermDebugging = 0

let g:netrw_liststyle = 3

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Autocmds
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Return to last edit position when opening files
autocmd BufReadPost *
     \ if line("'\"") > 0 && line("'\"") <= line("$") |
     \   exe "normal! g`\"" |
     \ endif


function! <SID>StripTrailingWhitespaces()
  if !&binary && &filetype != 'diff'
    let l:save = winsaveview()
    keeppatterns %s/\s\+$//e
    call winrestview(l:save)
  endif
endfun

autocmd FileType * autocmd BufWritePre <buffer> :call <SID>StripTrailingWhitespaces()

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Useful utils
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
lua require('mini.comment').setup()
lua require('mini.indentscope').setup()
lua require('mini.pairs').setup()
lua require('mini.surround').setup()
lua require('mini.trailspace').setup()

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Autocompletion
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:rustfmt_autosave = 1
let g:rustfmt_emit_files = 1
let g:rustfmt_fail_silently = 0

set completeopt=menu,menuone,preview,noselect,noinsert
set omnifunc=ale#completion#OmniFunc
let g:ale_completion_enabled = 1
let g:ale_sign_column_always = 1

let g:ale_sign_error = '✗'
let g:ale_sign_warning = ''

let g:ale_cpp_cc_options='-std=c++17 -Wall'
let g:ale_cpp_clangcheck_executable='/usr/local/bin/clang-check'
let g:ale_cpp_clangd_executable='/usr/local/bin/clangd'

let g:ale_rust_cargo_use_clippy=1
let g:ale_rust_cargo_use_check=1

let g:ale_fixers = {
  \ '*': ['remove_trailing_lines', 'trim_whitespace'],
  \ 'rust': ['rustfmt'],
  \ 'cpp': ['clang-format'],
\}

let g:ale_linters = { 'rust': ['cargo', 'rustc'], 'c': ['clangd'], 'cpp': ['clangd'] }

inoremap <silent><expr><TAB> pumvisible() ? "\<C-n>" : "\<TAB>"

nmap <silent> gd :ALEGoToDefinition<CR>
nmap <silent> gr  :ALEFindReferences<CR>
nmap <silent> [g <Plug>(ale_previous_wrap)
nmap <silent> ]g <Plug>(ale_next_wrap)

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Syntax highlighting
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
lua << EOF

require'nvim-treesitter.configs'.setup {
  ensure_installed = { "c", "cpp", "java", "lua", "vim", "vimdoc", "query", "rust" },
  sync_install = false,
  auto_install = true,

  highlight = {
    enable = true,
    additional_vim_regex_highlighting = false,
  },
}

EOF

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Fuzzy finder
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
lua require "fzf-lua".setup { global_git_icons = false }
nnoremap <silent> <leader>fb :lua require"fzf-lua".buffers()<CR>
nnoremap <silent> <leader>ff :lua require"fzf-lua".files()<CR>
nnoremap <silent> <leader>fl :lua require"fzf-lua".live_grep_glob()<CR>
nnoremap <silent> <leader>fg :lua require"fzf-lua".grep_project()<CR>
nnoremap <silent> <leader>fk :lua require"fzf-lua".builtin()<CR>
nnoremap <silent> <F1>       :lua require"fzf-lua".help_tags()<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Key mappings
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Typos!
:command! W w
:command! Q q
:command! Wq wq
:command! WQ wq

" Fast save and quit
nmap <silent> <leader>w :w!<cr>
nmap <silent> <leader>qw :x!<cr>
nmap <silent> <leader>qq :qa<cr>
nmap <silent> <leader>fn :enew<cr>
nmap <silent> <leader>; :nohlsearch<Bar>diffupdate<Bar>normal! <C-L><CR>

" Easy navigation
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

" Search behaviour of n and N
nnoremap <expr> n  'Nn'[v:searchforward]
xnoremap <expr> n  'Nn'[v:searchforward]
onoremap <expr> n  'Nn'[v:searchforward]

nnoremap <expr> N  'nN'[v:searchforward]
xnoremap <expr> N  'nN'[v:searchforward]
onoremap <expr> N  'nN'[v:searchforward]

nmap j gj
nmap k gk

" Better indenting
vnoremap < <gv
vnoremap > >gv

nnoremap <leader>xl :lopen<cr>
nnoremap <leader>xq :copen<cr>
