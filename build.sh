#!/bin/sh

echo "Compiling assembler stubs..."
nasm -f elf -o bin/isrstub.o src/asm/isrstub.asm
nasm -f elf -o bin/kernel_asm.o src/asm/kernel.asm
nasm -f elf -o bin/irqh.o src/asm/irqh.asm
nasm -f elf -o bin/syscalls.o src/asm/syscalls.asm
echo "Compiling kernel files..."
gcc -ffreestanding -o bin/kernel_c.o -c src/kernel2/kernel.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs -ggdb
gcc -ffreestanding -o bin/video.o -c src/kernel2/video.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/mem.o -c src/kernel2/mem.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/idt.o -c src/kernel2/idt.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/isr.o -c src/kernel2/isr.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/pic.o -c src/kernel2/pic.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/handlers.o -c src/kernel2/handlers.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/gdt.o -c src/kernel2/gdt.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/pio.o -c src/kernel2/pio.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/int.o -c src/kernel2/int.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/rpc.o -c src/kernel2/rpc.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/service.o -c src/kernel2/service.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/debug.o -c src/kernel2/debug.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/csyscalls.o -c src/kernel2/syscalls.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
echo "Compiling drivers..."
gcc -ffreestanding -o bin/drivers/keyboard.o -c src/drivers/keyboard.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/drivers/floppy.o -c src/drivers/floppy.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/drivers/speaker.o -c src/drivers/speaker.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
echo "Compiling nlib..."
gcc -ffreestanding -o bin/nlib/nstring.o -c src/nlib/nstring.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/nlib/nconv.o -c src/nlib/nconv.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/nlib/nflag.o -c src/nlib/nflag.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/nlib/nmem.o -c src/nlib/nmem.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/nlib/nvideo.o -c src/nlib/nvideo.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/nlib/nsyscalls.o -c src/nlib/nsyscalls.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
gcc -ffreestanding -o bin/nlib/ntextio.o -c src/nlib/ntextio.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
echo "Compiling apps..."
gcc -ffreestanding -o bin/apps/nash.o -c src/apps/nash.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs
echo "Linking files..."
ld -T src/link.txt -o bin/kernel.bin bin/kernel_asm.o bin/kernel_c.o bin/isrstub.o bin/video.o bin/mem.o bin/irqh.o bin/idt.o bin/isr.o bin/pic.o bin/handlers.o bin/gdt.o bin/pio.o bin/int.o bin/rpc.o bin/service.o bin/drivers/keyboard.o bin/nlib/nstring.o bin/nlib/nvideo.o bin/nlib/nconv.o bin/nlib/nflag.o bin/nlib/nmem.o bin/nlib/nsyscalls.o bin/debug.o bin/apps/nash.o bin/syscalls.o bin/csyscalls.o bin/drivers/floppy.o bin/drivers/speaker.o bin/nlib/ntextio.o

read -p "Floppy?" basta
dd if=/dev/zero of=floppy.img bs=1024 count=1440
/sbin/mke2fs -F floppy.img
mkdir floppy
mount -o loop floppy.img floppy/
cp bin/kernel.bin floppy/
mkdir floppy/grub
cp /boot/grub/stage1 floppy/grub
cp /boot/grub/stage2 floppy/grub
cp menu.lst floppy/grub/
umount floppy/
./grub.sh
chown -hR roman ../
read -p "Qemu?" basta
qemu -fda floppy.img -d int
 
 
