# .bash_profile
echo alskdfjlaksdjflaksdjflaksjdflakjsdfl
# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

PATH=$PATH:$HOME/.local/bin:$HOME/bin:.
export PATH

export PATH="$HOME/.cargo/bin:$PATH"

source /home/build/.config/broot/launcher/bash/br
