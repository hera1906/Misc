#
#WebXi
#
#dw='cd ~/src/NExT/webxi'
#alias cdse='cd ~/src/NExT/webxi/libWebXiServer/Server'
#alias cdpa='cd ~/src/NExT/webxi/libWebXiServer/Parser'
#alias cdca='cd ~/src/NExT/webxi/libWebXiServer/Cache'
#alias cdli='cd ~/src/NExT/webxi/libWebXi'
#alias cdin='cd ~/src/NExT/webxi/libWebXi/WebXi'
#alias cdco='cd ~/src/NExT/webxi/Command'
#alias cdbk='cd ~/src/NExT/bk_common_library'

#
#NExT
#
alias cdne='cd ~/src/NExT'
alias cdbr='cd ~/src/NExT/opc-ua-jet-bridge'
alias cdwr='cd ~/src/NExT/opc-ua-jet-bridge/open62541-wrapper'
alias cdfu='cd ~/src/NExT/functionblocks'
#alias cdex='cd ~/src/NExT/opc-ua-set-up-interfac/opc-ua-server/src'
alias ..='cd ..'
alias ...='cd ../..'
alias ....='cd ../../..'

alias ll='ls -AlF'
alias la='ls -A'
alias l='ls -CF'

alias cmk="nice cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
alias cmkd="nice cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON"
alias mk="nice make -j 5"

# Aliases for compating in git:
#
# assumes that
#  Set up diff tool for text and gui environment:
#    git --gloval diff.tool vimdiff
#    git --global diff.guitool kdiff3
#  Define git aliases
#    git config --global alias.vd difftool
#    git config --global alias.gv 'difftool -g'
#  Stop prompting:
#    git config --global difftool.prompt 0
#
#   Compare using vim:
alias gitv="git difftool"
#  Compare using kdiff3
alias gitg="git difftool -g"

alias uae="nohup UaExpert-1.5.1-331-x86_64.AppImage &"

#alias vi=vimx
#alias netbeans='/usr/local/netbeans-8.2/bin/netbeans'
#alias smartgit='/home/build/smartgit/bin/smartgit.sh'
