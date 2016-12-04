#!/bin/sh
losetup -o 1048576 /dev/loop1 disk.img
mount /dev/loop1 /mnt
