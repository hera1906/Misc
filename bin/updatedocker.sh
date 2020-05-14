#!/bin/sh
# Create a script to update system so it corresponds to the docker file...
# Run this where the "Dockerfile" is
SCRIPTFILE=dcnv.sh

sed -e '/FROM/d;/LABEL/d;s/ARG/export/;s/RUN//' Dockerfile > $SCRIPTFILE
chmod +x $SCRIPTFILE
ls -l $SCRIPTFILE
echo SUDO $SCRIPTFILE in some tmp directory to update the system.
