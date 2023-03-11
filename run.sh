!/bin/bash

make all ;
rc=$? ;
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
./bin/fs -f $1
