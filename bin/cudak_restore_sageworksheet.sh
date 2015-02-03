#!/bin/bash
HOMEDIR=$( getent passwd "$USER" | cut -d: -f6 )
SAGEUSR="$HOMEDIR/sage-git/imid.sagenb/home/macieksk/"
WRKNUM=79
WRKDIR=R_worksheets/sageworksheet 

confirm () {
    # call with a prompt string or use a default
    read -r -p "${1:-Are you sure? [y/N]} " response
    case $response in
        [yY][eE][sS]|[yY]) 
            true
            ;;
        *)
            false
            ;;
    esac
}


confirm "Overwriting sage worksheet $WRKNUM? [y/N]" && rsync -av --delete $WRKDIR/* $SAGEUSR/$WRKNUM/


