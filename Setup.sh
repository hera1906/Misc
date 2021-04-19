#!/usr/bin/bash
MISCDIR=~/misc
DOTDIR=$MISCDIR/DotFiles
cd ~

ln $DOTDIR/.bash_aliases .
ln $DOTDIR/.bash_git .
ln $DOTDIR/.bash_logout .
ln $DOTDIR/.bash_profile .
ln $DOTDIR/.bashrc .
ln -s $DOTDIR/.config .
ln $DOTDIR/.gdbinit .
ln $DOTDIR/.gitconfig .
ln $DOTDIR/.gtkrc-2.0 .
ln $DOTDIR/.inputrc .
ln $DOTDIR/.profile .
ln $DOTDIR/.spectrwm.conf .
ln -s $DOTDIR/.tmux .
ln $DOTDIR/.tmux.conf .
ln -s $DOTDIR/.vim .
ln -s $DOTDIR/.xmonad .
ln $DOTDIR/.Xresources .
ln -s $DOTDIR/.fonts .
ln -s $MISCDIR/bin .
ln -s $MISCDIR/vimwiki .
