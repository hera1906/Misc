anext() {
    alias cdw='cd ~/Source/NExT/webxi'
    alias cdse='cd ~/Source/NExT/webxi/libWebXiServer/Server'
    alias cdpa='cd ~/Source/NExT/webxi/libWebXiServer/Parser'
    alias cdca='cd ~/Source/NExT/webxi/libWebXiServer/Cache'
    alias cdli='cd ~/Source/NExT/webxi/libWebXi'
    alias cdin='cd ~/Source/NExT/webxi/libWebXi/WebXi'
    alias cdco='cd ~/Source/NExT/webxi/Command'
    alias cdne='cd ~/Source/NExT/webxi/NExT'
    alias cdbk='cd ~/Source/NExT/bk_common_library'
    unalias cds
    unalias cdslm
    unalias wse
    unalias wco
    unalias wne
    echo "Aliases set up to NExT (type a2245 or a2255 to switch to 2245 or 2255 aliases)"
}
alias aNExT='anext'
a2245() {
    alias cdw='cd ~/Source/sxu/Software/Shared/webxi'
    alias cdse='cd ~/Source/sxu/Software/Shared/webxi/libWebXiServer/Server'
    alias cdpa='cd ~/Source/sxu/Software/Shared/webxi/libWebXiServer/Parser'
    alias cdca='cd ~/Source/sxu/Software/Shared/webxi/libWebXiServer/Cache'
    alias cdli='cd ~/Source/sxu/Software/Shared/webxi/libWebXi'
    alias cdin='cd ~/Source/sxu/Software/Shared/webxi/libWebXi/WebXi'
    alias cdco='cd ~/Source/sxu/Software/Shared/webxi/Command'
    alias cdne='cd ~/Source/sxu/Software/Shared/webxi/NExT'
    alias cdbk='cd ~/Source/sxu/Software/Shared/bk_common_library'
    alias cds='cd ~/Source/sxu/Software'
    alias cdslm='cd ~/Source/sxu/Software/SLM/SLM/source'
    alias wse='~/Source/sxu/Software/Shared/webxi/buildx86/install_dir/bin/BK_WebXiServer'
    alias wco='~/Source/sxu/Software/Shared/webxi/buildx86/install_dir/bin/BK_WebXiCommand'
    alias wne='~/Source/sxu/Software/Shared/webxi/buildx86/install_dir/bin/WebXiNExT'
    alias BK_2245='BK_SLM'
    echo "Aliases set up to 2245 (type a2255 to switch to 2255 aliases, or anext to switch to NExT aliases)"
}
a2255() {
    alias cdw='cd ~/Source/2255/Software/Shared/webxi'
    alias cdse='cd ~/Source/2255/Software/Shared/webxi/libWebXiServer/Server'
    alias cdpa='cd ~/Source/2255/Software/Shared/webxi/libWebXiServer/Parser'
    alias cdca='cd ~/Source/2255/Software/Shared/webxi/libWebXiServer/Cache'
    alias cdli='cd ~/Source/2255/Software/Shared/webxi/libWebXi'
    alias cdin='cd ~/Source/2255/Software/Shared/webxi/libWebXi/WebXi'
    alias cdco='cd ~/Source/2255/Software/Shared/webxi/Command'
    alias cdne='cd ~/Source/2255/Software/Shared/webxi/NExT'
    alias cdbk='cd ~/Source/2255/Software/Shared/bk_common_library'
    alias cds='cd ~/Source/2255/Software'
    alias cdslm='cd ~/Source/2255/Software/SLM/SLM/source'
    alias wse='~/Source/2255/Software/Shared/webxi/buildx86/install_dir/bin/BK_WebXiServer'
    alias wco='~/Source/2255/Software/Shared/webxi/buildx86/install_dir/bin/BK_WebXiCommand'
    alias wne='~/Source/2255/Software/Shared/webxi/buildx86/install_dir/bin/WebXiNExT'
    echo "Aliases set up to 2255 (type a2245 to switch to 2245 aliases, or anext to switch to NExT aliases)"
}
anext

alias bx="./Buildx86.sh"
alias ix="./Installx86.sh"
alias bt="./BuildTarget.sh clean Release"
alias it="./remoteDebug.sh 169.254.3.29 true"
alias vi=vim
alias cmk='cmake -DCMAKE_BUILD_TYPE=Debug ..'
alias netbeans='/usr/local/netbeans-8.2/bin/netbeans'
alias smartgit='/home/build/smartgit/bin/smartgit.sh'
alias ..='cd ..'
alias ...='cd ../..'
alias ....='cd ../../..'
