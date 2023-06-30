" -----------------------------------------------------------------------------
"     - General settings -
" -----------------------------------------------------------------------------
set textwidth=99
set nospell

" -----------------------------------------------------------------------------
"     - Key mappings -
" -----------------------------------------------------------------------------
nmap <C-b> :Compile<CR>
nmap <Leader>x :Cargo run<CR>
nmap gv <Plug>(rust-def-vertical)

nmap <leader>d :DebugMain<CR>
nmap <leader>b :DebugAndBreak<CR>
nmap ; :Over<CR>
nmap <leader>; :Step<CR>

nmap <leader>rt :RustTest<CR>
nmap <leader>tt :DebugTest<CR>

" -----------------------------------------------------------------------------
"     - Abbreviations -
" -----------------------------------------------------------------------------
ia cmt cmt<Leader>t<Left>
ia dd #[derive(Debug)]

let g:rustfmt_command = "rustfmt"

" -----------------------------------------------------------------------------
"     - Find references to ident -
" -----------------------------------------------------------------------------
command! References execute "lua vim.lsp.buf.references()"
command! Rename execute "lua vim.lsp.buf.rename()"
