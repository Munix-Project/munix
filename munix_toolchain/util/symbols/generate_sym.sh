#!/bin/sh
# Go to project root directory:
cd $(dirname $0)
cd ../../../

TOOLCHAIN=munix_toolchain
KERNELNAME=munix-kernel
PYPATH=./$TOOLCHAIN/util/symbols/generate_symbols.py
SYMBOLASM=./kernel/symbols.S
NM=i686-munix-nm

# Now generate the symbols:
$NM ./$TOOLCHAIN/$KERNELNAME -g | $PYPATH > $SYMBOLASM
