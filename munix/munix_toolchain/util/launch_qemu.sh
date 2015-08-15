#!/bin/bash

MEM_SIZE=1024
MOUNT_PATH=/mnt/munix
KERNEL_FILE=munix-kernel
TOOLCHAIN_PATH=munix_toolchain
HDD_DISK=munix-hdd.img
HDD_START=2048
HDD_OFFSET=$(($HDD_START*512)) #1048576
BOOT_PATH=$TOOLCHAIN_PATH/util/grub

EMU=qemu-system-i386
PR=munix_toolchain/modules

# Sort out dependencies in the proper order:
MODS="serial,procfs,tmpfs,ata,ext2,debug_shell,ps2mouse,ps2kbd,lfbvideo,packetfs,snd,pcspkr,ac97,net,rtl,irc"
MODS=$(echo $MODS | sed "s@ @@g") # Remove empty spaces
MODS=$(echo $MODS | sed "s@,@.ko,$PR/@g") # Replace commas with the prefix and sufixes
MODS="$PR/$MODS.ko" # Fix it up by adding the last two pieces

# Mount Hard Disk Image
printf "Mounting HDD image . . . "
sudo mkdir $MOUNT_PATH
sudo mount -o loop,offset=$HDD_OFFSET $BOOT_PATH/$HDD_DISK $MOUNT_PATH
printf "Done\n"

# Copy kernel binary file into /
printf "Copying kernel into / . . . "
sudo cp $TOOLCHAIN_PATH/$KERNEL_FILE $MOUNT_PATH
printf "Done\n"

# Umount HDD image
printf "Umounting HDD . . . "
sudo umount $MOUNT_PATH
sudo rm -r $MOUNT_PATH
printf "Done\n"

# Launch QEMU
printf "==========\nLaunching QEMU i386 . . .\n==========\n"
$EMU -initrd $MODS -hda toaruos-disk.img -sdl -kernel $TOOLCHAIN_PATH/$KERNEL_FILE -serial stdio -vga std -rtc base=localtime -net nic,model=rtl8139 -net user -soundhw pcspk,ac97 -net dump -no-kvm-irqchip -m $MEM_SIZE -append "logtoserial=1 start=--vga root=/dev/hda"
