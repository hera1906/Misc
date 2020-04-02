# .bash_profile
echo This is .bash_profile
# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

PATH=$PATH:$HOME/.local/bin:$HOME/bin:.
export PATH

export PATH="$HOME/.cargo/bin:$PATH"

source /home/build/.config/broot/launcher/bash/br
