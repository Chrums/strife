#!/bin/bash

set -e

if [[ $* == *--clean* ]]
then
    rm -rf /project/strife/build/*
fi

if [[ $* == *--emscripten* ]]
then
    build="emcmake cmake"
    buildFlags="-DCMAKE_BUILD_TYPE=DEBUG -DBOOST_ROOT=${BOOST_ROOT} -DBoost_INCLUDE_DIRS=${BOOST_ROOT} -DBoost_LIBRARY_DIRS=/usr/lib/boost"
    compile="emmake make"
    compileFlags=""
    install="emmake make install"
    installFlags=""
else
    build="cmake"
    buildFlags=""
    compile="make"
    compileFlags=""
    install="make install"
    installFlags=""
fi

mkdir -p build
pushd build
eval $build $buildFlags ..
eval $compile $compileFlags
eval $install $installFlags
popd