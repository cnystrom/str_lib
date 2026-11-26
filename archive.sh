#!/bin/sh

. ../../../build.sh

PROGNAME=str_lib

TAR_FILE=${PROGNAME}.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} ${PROGNAME}

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz olenska.newio.org:/export/home/cnystrom

