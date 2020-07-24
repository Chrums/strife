#!/bin/bash

set -e

if [[ $* == *--clean* ]]
then
    rm -rf /project/build/*
fi

if [[ $* == *--emscripten* ]]
then
    build="emcmake cmake"
    buildFlags="-DCMAKE_BUILD_TYPE=DEBUG -DBOOST_ROOT=${BOOST_ROOT} -DBoost_INCLUDE_DIRS=${BOOST_ROOT} -DBoost_LIBRARY_DIRS=/usr/lib/boost"
    compile="emmake make"
    compileFlags=""
else
    build="cmake"
    buildFlags=""
    compile="make"
    compileFlags=""
fi

mkdir -p build
pushd build
eval $build $buildFlags ..
eval $compile $compileFlags
popd