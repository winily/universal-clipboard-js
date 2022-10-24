#!/bin/bash
build_path="$(pwd)/build"
if [ ! -d build_path ]; then
    rm -fr ./build
fi

cmake-js build

echo 'BUILD END!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'
echo ''
