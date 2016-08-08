#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp -r filesystem/* isodir/
cp -r sysroot/* isodir/
grub-mkrescue -d /usr/lib/grub/i386-pc -o zdos.iso isodir/