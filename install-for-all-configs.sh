#!/bin/bash
mkdir -p ./cmake-build-asan
mkdir -p ./cmake-build-debug
mkdir -p ./cmake-build-release

cd cmake-build-asan || exit
conan install ..
cd ..

cd cmake-build-debug || exit
conan install ..
cd ..

cd cmake-build-release || exit
conan install ..
cd ..
