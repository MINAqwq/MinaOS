#!/bin/sh

make
sh Scripts/create_iso.sh
qemu-system-i386 -cdrom kernel.iso -machine type=pc-i440fx-3.1
