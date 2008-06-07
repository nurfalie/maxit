#!/bin/csh -x

set BACKUP_DIR = /love/scsi/backup.d/maxit.d

if (! -d $BACKUP_DIR ) then
    mkdir $BACKUP_DIR
endif

cp -p *.h $BACKUP_DIR/.
cp -p *.cc $BACKUP_DIR/.
cp -p *.pro $BACKUP_DIR/.
cp -p *.ui $BACKUP_DIR/.
cp -p *.csh $BACKUP_DIR/.
