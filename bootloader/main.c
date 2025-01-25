#include "main.h"

efi_status_t result;

void load_kernel(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("[Frameboot] Failed to open %s\r\n", path);
        ERROR_WAITING
        result = EFI_LOAD_ERROR;
        return;
    }

    ELF64_Ehdr header;
    if (fread(&header, 1, sizeof(header), file) != sizeof(header)) {
        printf("[Frameboot] Failed to read ELF header\r\n");
        ERROR_WAITING
        fclose(file);
        result = EFI_LOAD_ERROR;
        return;
    }

    if (memcmp(header.e_ident, "\x7F""ELF", 4) != 0) {
        printf("[Frameboot] Invalid ELF file\r\n");
        ERROR_WAITING
        fclose(file);
        result = EFI_LOAD_ERROR;
        return;
    }

    fseek(file, header.e_phoff, SEEK_SET);
    for (int i = 0; i < header.e_phnum; i++) {
        ELF64_Phdr phdr;

        if (fread(&phdr, 1, sizeof(phdr), file) != sizeof(phdr)) {
            printf("[Frameboot] Failed to read program header\r\n");
            ERROR_WAITING
            fclose(file);
            result = EFI_LOAD_ERROR;
            return;
        }

        if (phdr.p_type != 1) {
            continue;
        }

        void *segment = malloc(phdr.p_memsz);
        if (!segment) {
            printf("[Frameboot] Failed to allocate memory for segment\r\n");
            ERROR_WAITING
            fclose(file);
            result = EFI_LOAD_ERROR;
            return;
        }

        fseek(file, phdr.p_offset, SEEK_SET);
        if (fread(segment, 1, phdr.p_filesz, file) != phdr.p_filesz) {
            printf("[Frameboot] Failed to load segment\r\n");
            ERROR_WAITING
            free(segment);
            fclose(file);
            result = EFI_LOAD_ERROR;
            return;
        }

        if (phdr.p_memsz > phdr.p_filesz) {
            memset((char *)segment + phdr.p_filesz, 0, phdr.p_memsz - phdr.p_filesz);
        }

        printf("[Frameboot] Loaded segment at %p, size: 0x%lx\r\n", segment, phdr.p_memsz);
    }

    fclose(file);

    void (*entry_point)(void) = (void (*)(void)) header.e_entry;
    printf("[Frameboot] Jumping to kernel entry point: 0x%lx\r\n", header.e_entry);
    entry_point();

    result = EFI_SUCCESS;
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    EFI_PRINT(L"[Frameboot] The Framework OS will be loaded in 5 seconds.\r\n");

    sleep(5);

    EFI_PRINT(L"[Frameboot] Loading the Framework OS...\r\n");

    // todo: hardware pre-validation? с одной стороны можно, с другой стороны на arm64 всё равно не получится запустить x86_64-elf... Надо подумать.
    // todo: kernel integrity check, чтобы не случился вспыш, лоу левел всё таки
    load_kernel("/os/kernel");

    if(result == EFI_SUCCESS) {
        ST->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
        EFI_PRINT(L"[Frameboot] The watchdog timer has been disabled\r\n");
    }


    return result;
}


