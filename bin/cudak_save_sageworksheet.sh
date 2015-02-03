#!/bin/bash
HOMEDIR=$( getent passwd "$USER" | cut -d: -f6 )
SAGEUSR="$HOMEDIR/sage-git/imid.sagenb/home/macieksk/"
WRKNUM=79
WRKDIR=R_worksheets/sageworksheet 

rsync -av --delete $SAGEUSR/$WRKNUM/* $WRKDIR/

git add $WRKDIR

