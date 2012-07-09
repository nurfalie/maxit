#!/bin/sh

if [ -r /usr/local/maxit/Maxit ] && [ -x /usr/local/maxit/Maxit ]
then
    cd /usr/local/maxit && ./Maxit &
    exit $?
else
    exit 1
fi
