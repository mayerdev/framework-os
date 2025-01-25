#include <uefi.h>

#define EFI_PRINT(str) ST->ConOut->OutputString(ST->ConOut, str);
#define ERROR_WAITING sleep(15);

typedef struct {
    uint8_t  e_ident[16];   /* Магическое число и другие сведения */
    uint16_t e_type;        /* Тип объектного файла */
    uint16_t e_machine;     /* Архитектура */
    uint32_t e_version;     /* Версия объектного файла */
    uint64_t e_entry;       /* Виртуальный адрес точки входа */
    uint64_t e_phoff;       /* Смещение таблицы заголовков программы */
    uint64_t e_shoff;       /* Смещение таблицы заголовков секций */
    uint32_t e_flags;       /* Флаги, специфические для процессора */
    uint16_t e_ehsize;      /* Размер заголовка ELF */
    uint16_t e_phentsize;   /* Размер элемента таблицы заголовков программы */
    uint16_t e_phnum;       /* Количество элементов таблицы заголовков программы */
    uint16_t e_shentsize;   /* Размер элемента таблицы заголовков секций */
    uint16_t e_shnum;       /* Количество элементов таблицы заголовков секций */
    uint16_t e_shstrndx;    /* Индекс таблицы строк заголовков секций */
} ELF64_Ehdr;

typedef struct {
    uint32_t p_type;        /* Тип сегмента */
    uint32_t p_flags;       /* Флаги сегмента */
    uint64_t p_offset;      /* Смещение сегмента */
    uint64_t p_vaddr;       /* Виртуальный адрес сегмента */
    uint64_t p_paddr;       /* Физический адрес сегмента */
    uint64_t p_filesz;      /* Размер сегмента в файле */
    uint64_t p_memsz;       /* Размер сегмента в памяти */
    uint64_t p_align;       /* Выравнивание сегмента */
} ELF64_Phdr;
