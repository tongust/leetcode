set cursorline!
nnoremap <C-J> <C-W>j
nnoremap <C-K> <C-W>k
nnoremap <C-H> <C-W>h
nnoremap <C-L> <C-W>l

au BufNewFile *.cpp 0r ~/.vim/cpp.skeleton | let IndentStyle = "cpp"
au BufNewFile *.h 0r ~/.vim/cpp.skeleton | let IndentStyle = "cpp"

set tabstop=2 softtabstop=0 expandtab shiftwidth=4 smarttab
