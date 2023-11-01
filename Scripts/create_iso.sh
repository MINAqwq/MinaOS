#!/bin/sh

rm -r iso
mkdir -p iso/boot/grub

cp kernel.bin iso/boot
echo "set timeout=5" > iso/boot/grub/grub.cfg
echo "set default=0" >> iso/boot/grub/grub.cfg
echo "" >> iso/boot/grub/grub.cfg
echo 'menuentry "MinaOS" {' >> iso/boot/grub/grub.cfg
echo "  multiboot /boot/kernel.bin" >> iso/boot/grub/grub.cfg
echo "  boot" >> iso/boot/grub/grub.cfg
echo "}" >> iso/boot/grub/grub.cfg

grub-mkrescue --output=kernel.iso ./iso
