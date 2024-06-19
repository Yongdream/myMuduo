#!/bin/sh

rm -rf build/* lib/*
cd build
cmake ..
make

