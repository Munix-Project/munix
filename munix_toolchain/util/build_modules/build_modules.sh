#!/bin/sh
# Go to project root directory:
cd $(dirname $0)
cd ../../../
make -f ./munix_toolchain/util/build_modules/makefile
