tmux new-session -d
tmux split-window -h
tmux select-pane -R
tmux split-window -v
tmux new-window 'mutt'
tmux -2 attach-session -d
