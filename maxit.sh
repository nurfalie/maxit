#!/bin/sh

ostype="`uname -s`"

if [ $ostype = "Darwin" ]
then
    open /Applications/Maxit.d/Maxit.app &
else
    cd /usr/local/maxit
    ./Maxit &
fi

exit 0
