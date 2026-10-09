#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

static const char *type_phdr(Elf64_Word type)
{
    switch (type) {
        case PT_NULL:         return "NULL";
        case PT_LOAD:         return "LOAD";
        case PT_DYNAMIC:      return "DYNAMIC";
        case PT_INTERP:       return "INTERP";
        case PT_NOTE:         return "NOTE";
        case PT_PHDR:         return "PHDR";
        case PT_TLS:          return "TLS";
        case PT_GNU_EH_FRAME: return "GNU_EH_FRAME";
        case PT_GNU_STACK:    return "GNU_STACK";
        case PT_GNU_RELRO:    return "GNU_RELRO";
        case PT_GNU_PROPERTY: return "GNU_PROPERTY";
        default:              return "AUTRE";
    }
}

static int lire_entete(FILE *f, Elf64_Ehdr *ehdr)
{
    if (fread(ehdr, sizeof(*ehdr), 1, f) != 1) {
        fprintf(stderr, "Lecture en-tete impossible.\n");
        return -1;
    }

    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Pas un ELF.\n");
        return -1;
    }

    if (ehdr->e_ident[EI_CLASS] != ELFCLASS64) {
        fprintf(stderr, "Pas un ELF 64 bits.\n");
        return -1;
    }

    return 0;
}

static int afficher_program_headers(FILE *f, const Elf64_Ehdr *ehdr)
{
    if (fseek(f, (long)ehdr->e_phoff, SEEK_SET) != 0) {
        perror("fseek");
        return -1;
    }

    printf("  #   Type          Offset     VirtAddr     Flags\n");

    unsigned int i = 0;

    while (i < ehdr->e_phnum) {
        Elf64_Phdr phdr;

        if (fread(&phdr, sizeof(phdr), 1, f) != 1) {
            fprintf(stderr, "Lecture phdr %u impossible.\n", i);
            return -1;
        }

        printf("  %-2u  %-12s  0x%08lx  0x%09lx  %c%c%c\n",
               i,
               type_phdr(phdr.p_type),
               (unsigned long)phdr.p_offset,
               (unsigned long)phdr.p_vaddr,
               (phdr.p_flags & PF_R) ? 'R' : '-',
               (phdr.p_flags & PF_W) ? 'W' : '-',
               (phdr.p_flags & PF_X) ? 'E' : '-');

        i++;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage : %s <fichier_elf>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "rb");

    if (f == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    Elf64_Ehdr ehdr;
    int resultat = EXIT_FAILURE;

    if (lire_entete(f, &ehdr) != 0) {
        goto nettoyage;
    }

    printf("Point d'entree : 0x%lx\n",
           (unsigned long)ehdr.e_entry);

    printf("%u program headers, table a l'offset %lu\n\n",
           ehdr.e_phnum,
           (unsigned long)ehdr.e_phoff);

    if (afficher_program_headers(f, &ehdr) != 0) {
        goto nettoyage;
    }

    resultat = EXIT_SUCCESS;

nettoyage:
    fclose(f);
    return resultat;
}