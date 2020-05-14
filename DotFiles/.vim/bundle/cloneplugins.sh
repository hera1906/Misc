#
# This script clones the VIM plugin repositories needed by the vimrc setup
#

# Vundle, the plug-in manager for Vim
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

# A tree explorer plugin for vim.
git clone https://github.com/scrooloose/nerdtree.git

# A plugin of nerdtree showing git status
git clone https://github.com/Xuyuanp/nerdtree-git-plugin.git

# Asynchronous build and teset dispatcher
#git clone https://github.com/tpope/vim-dispatch.git

# Extend % matching for HTML, LaTex and many other languages
#git clone https://github.com/tmhedberg/matchit.git

# Paste in Vim with indentation adjusted to destination context
#git clone https://github.com/sickill/vim-pasta.git

# Syntax checking hacks for vim
#git clone https://github.com/scrooloose/syntastic.git

# Perform all your vim insert mode completions with Tab
#git clone https://github.com/ervandew/supertab.git

# Zoom in/out of windows (toggle between one window and multi-window)
#git clone https://github.com/vim-scripts/ZoomWin.git

# An extensible & universal comment vim-plugin that also handles embedded filetypes
#git clone https://github.com/vim-scripts/tComment.git

# Fuzzy file, buffer, mru, tag, etc finder
#git clone https://github.com/ctrlpvim/ctrlp.vim

# Vim plugin for tmux.conf
#git clone git://github.com/tmux-plugins/vim-tmux.git

# A vim plugin for communicating with a language server
# Install language server: ccls
# Build with cmake option: -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
# Remember to symlink compile_commands.json to project root e.g. ln -s buildx86/compile_commands.json .
#git clone https://github.com/natebosch/vim-lsc.git

# Viewer & Finder for LSP symbols and tags
#git clone https://github.com/liuchengxu/vista.vim.git

# Vim plugin for the ccls language server
git clone https://github.com/m-pilia/vim-ccls.git

# Simplify Doxygen documentation in C, C++, Python
git clone https://github.com/vim-scripts/DoxygenToolkit.vim.git

# Comment stuff out
git clone https://github.com/tpope/vim-commentary.git

# Vim plugin for clang-format, a formatter for C, C++, ....
git clone https://github.com/rhysd/vim-clang-format.git

# Directory viewer for Vim
git clone https://github.com/justinmk/vim-dirvish.git

# Ease your git workflow within Vim
git clone https://github.com/jreybert/vimagit.git

# A Git wrapper so awesome, it should be illegal
git clone https://github.com/tpope/vim-fugitive.git

# The undo history visualizer for vim
git clone https://github.com/mbbill/undotree.git

# Fuzzy finder
git clone https://github.com/junegunn/fzf.git
git clone https://github.com/junegunn/fzf.vim.git

# Fuzzy menu (requires fzf and fzf.vim)
git clone https://github.com/laher/fuzzymenu.vim.git

# Check syntax in Vim asyncrhonously and fix files, with Language Server Protocol (LSP) support
git clone https://github.com/dense-analysis/ale.git

# Vim Wiki
git clone https://github.com/vimwiki/vimwiki.git
vim +PluginInstall +qall

# Vim CMake
git clone https://github.com/vhdirk/vim-cmake.git

# Gutentags
#git clone https://github.com/ludovicchabant/vim-gutentags.git
# Gutentags_Plus (requires vim-gutentags.git)
#git clone https://github.com/skywind3000/gutentags_plus.git
#
# YouCompleteMe.
git clone https://github.com/ycm-core/YouCompleteMe.git
echo Follow YouCompleteMe installation at https://github.com/ycm-core/YouCompleteMe
