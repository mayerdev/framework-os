# Framework OS

Здесь когда нибудь будет описание того, что здесь происходит.

## Структура

| Файл / Директория | Описание                                  |
|-------------------|-------------------------------------------|
| bootloader/       | Загрузчик ОС                              |
| uefi.fd           | Образ UEFI для тестирования (TianoCore)   |
| qemu.sh           | Скрипт для сборки образа и запуска в UEFI |

## macOS

```bash
brew tap nativeos/i386-elf-toolchain
brew install llvm
brew install binutils
brew install x86_64-elf-binutils x86_64-elf-gcc
brew install lld
brew install gcc make nasm
export PATH="/usr/local/opt/binutils/bin:$PATH"
export PATH="/usr/local/opt/llvm/bin:$PATH"
```