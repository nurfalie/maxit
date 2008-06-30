#!/bin/csh -x

set BACKUP_DIR = /love/scsi/backup.d/maxit.d

if (! -d $BACKUP_DIR ) then
    mkdir $BACKUP_DIR
endif

if (! -d $BACKUP_DIR/images.d ) then
    mkdir $BACKUP_DIR/images.d
endif

if (! -d $BACKUP_DIR/include.d ) then
    mkdir $BACKUP_DIR/include.d
endif

if (! -d $BACKUP_DIR/ui.d ) then
    mkdir $BACKUP_DIR/ui.d
endif

cp -p *.h $BACKUP_DIR/include.d/.
cp -p *.cc $BACKUP_DIR/.
cp -p *.pro $BACKUP_DIR/.
cp -p *.ui $BACKUP_DIR/ui.d/.
cp -p *.csh $BACKUP_DIR/.
