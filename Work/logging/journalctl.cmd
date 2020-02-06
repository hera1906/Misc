journalctl -o short-precise --no-hostname -n 30 -t journaldtest -p alert..notice | sed 's/[^ ]*\]//'
