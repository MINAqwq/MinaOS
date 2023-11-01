#!/bin/sh

ARCH=$1

if [ -z $ARCH ];then
    echo "you need to specfiy the target architecture (for example x86_64)"
    exit 1
fi

qemu-system-$ARCH -kernel kernel.bin
