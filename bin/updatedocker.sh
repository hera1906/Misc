#!/bin/sh
# Experimental script to update the local system to match the ones in the docker image. It has been tested on an Ubuntu 20 installation
# Create a script to update system so it corresponds to the docker file...
# Run this where the "Dockerfile" is
SCRIPTFILE=dcnv.sh

sed -e '/FROM/d;/LABEL/d;s/ARG/export/;s/RUN//' Dockerfile > $SCRIPTFILE
chmod +x $SCRIPTFILE
ls -l $SCRIPTFILE
echo SUDO $SCRIPTFILE in some tmp directory to update the system.
