TARGET = ../dist/EFI/BOOT/BOOTX64.efi
ARCH = x86_64
SRCS = $(wildcard *.c)
CFLAGS = -pedantic -Wall -Wextra -Werror -O2 -Wno-comment \
         -fshort-wchar -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti \
         -mno-red-zone

include uefi/Makefile