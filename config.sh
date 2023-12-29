#!/bin/bash

while [ ! -z $CONDA_PREFIX ]; do
    conda deactivate
done

if [ ! -z $PROJECT_DIR ]; then
    export PROJECT_DIR_OLD=$PROJECT_DIR
fi
export PROJECT_DIR=$(pwd)

export PATH=$PROJECT_DIR/.bin:$PATH

# not needed as found in cmake
source ~/software/root/bin/thisroot.sh
