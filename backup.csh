#!/bin/csh -x

set BACKUP_DIR = /love/scsi/backup.d/maxit.d

if ( ! -d $BACKUP_DIR ) then
    mkdir $BACKUP_DIR
endif

if ( ! -d $BACKUP_DIR/images.d ) then
    mkdir $BACKUP_DIR/images.d
endif

if ( ! -d $BACKUP_DIR/include.d ) then
    mkdir $BACKUP_DIR/include.d
endif

if ( ! -d $BACKUP_DIR/ui.d ) then
    mkdir $BACKUP_DIR/ui.d
endif

mkdir $BACKUP_DIR/images.d/ubuntu.d
mkdir $BACKUP_DIR/images.d/monster.d
mkdir $BACKUP_DIR/images.d/sunsplash.d
cp -p include.d/*.h $BACKUP_DIR/include.d/.
cp -p *.cc $BACKUP_DIR/.
cp -p *.pro $BACKUP_DIR/.
cp -p ui.d/*.ui $BACKUP_DIR/ui.d/.
cp -p *.csh $BACKUP_DIR/.
cp -fpR images.d/ubuntu.d/*.png $BACKUP_DIR/images.d/ubuntu.d/.
cp -fpR images.d/monster.d/*.png $BACKUP_DIR/images.d/monster.d/.
cp -fpR images.d/sunsplash.d/*.png $BACKUP_DIR/images.d/sunsplash.d/.
