#!/bin/bash
# Building image
hdiutil create -fs fat32 -ov -size 48m -volname EFIBOOT -format UDTO -srcfolder ./dist uefi.cdr

# Starting QEMU
qemu-system-x86_64 -cpu qemu64 -bios uefi.fd -drive file=uefi.cdr,format=raw,if=ide -device VGA,vgamem_mb=128 -m 256