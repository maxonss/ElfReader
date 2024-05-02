#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "../include/options.h"
#include <fcntl.h>
#include <elf.h>
#include <gelf.h>
#include <libelf.h>
/**
 * Prints the .text section in hexadecimal
 * This function is called when the user passes the -d argument
 *
 * @param content
 * @author Merieme Yaaqobi
 */
void print_text_section_hex(const char *content) {
    Elf *elf;
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    Elf_Data *data;
    size_t n, shstrndx;
    if (elf_version(EV_CURRENT) == EV_NONE) {
        perror("Erreur de version ELF");
        exit(EXIT_FAILURE);
    }
    elf = elf_begin(*content, ELF_C_READ, NULL);
    if (elf == NULL) {
        perror("elf_begin a échoué");
        exit(EXIT_FAILURE);
    }
    if (elf_getshdrstrndx(elf, &shstrndx) != 0) {
        perror("elf_getshdrstrndx a échoué");
        exit(EXIT_FAILURE);
    }
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            perror("gelf_getshdr a échoué");
            exit(EXIT_FAILURE);
        }
        if (shdr.sh_type == SHT_PROGBITS) {
            data = elf_getdata(scn, NULL);
            for (n = 0; n < data->d_size; ++n) {
                printf("%02x ", ((unsigned char*)data->d_buf)[n]);
                if ((n + 1) % 16 == 0)
                    putchar('\n');
            }
            putchar('\n');
            break;
        }
    }
    elf_end(elf);
}

/**
 * Prints sections count.
 * This function is called when the user passes the -s argument.
 *
 * @param content
 * @author Merieme Yaaqobi
 */
void print_section_count(const char *content) {
    Elf *elf;
    size_t shnum;

    if (*content == -1) {
        perror("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }

    if (elf_version(EV_CURRENT) == EV_NONE) {
        perror("Erreur de version ELF");
        exit(EXIT_FAILURE);
    }

    elf = elf_begin(*content, ELF_C_READ, NULL);
    if (elf == NULL) {
        perror("elf_begin a échoué");
        exit(EXIT_FAILURE);
    }

    if (elf_getshdrnum(elf, &shnum) != 0) {
        perror("elf_getshdrnum a échoué");
        exit(EXIT_FAILURE);
    }

    printf("Le fichier contient %zu sections.\n", shnum);

    elf_end(elf);
}

/**
 * Prints the list of sections including their name and size.
 * This function is called when the user passes the -a argument.
 *
 * @param content
 * @author Tristan Salé
 */
void print_section_name_size(const char *content) {
    printf("Option -a appelée\n");
}

/**
 * Prints the entry point address of the given content.
 * This function is called when the user passes the -e argument.
 *
 * @param content
 * @author Tristan Salé
 */
void print_entrypoint_address_program(const char *content) {
    printf("Option -e appelée\n");
}

void option_t(const char *content) {
    printf("Option -t appelée\n");
}

void option_l(const char *content) {
    printf("Option -l appelée\n");
}

void option_c(const char *content) {
    printf("Option -c appelée\n");
}

void option_h() {
    printf("Usage: ./ElfReader [file_name] [-d hexadecimal .text] [-s sections count]\n [-a sections list] [-e program entry address] [-t chains table content]\n [-l dynamic libraries list]\n [--c-wizard file system specs]");
}

// Fonction pour afficher les informations standardes du fichier ELF
void print_basic_info(const char *file_to_open) {
    struct stat file_info;
    if (stat(file_to_open, &file_info) != 0) {
        perror("Erreur lors de la récupération des informations du fichier");
        exit(EXIT_FAILURE);
    }

    printf("Taille du fichier : %lld octets\n", file_info.st_size);
//    printf("Propriétaire : %d, %s\n ", file_info.st_uid, getpwuid(file_info.st_uid)->pw_name);
    printf("Droits: %o\n", file_info.st_mode);
    printf("Nombre de blocs alloués : %llu\n", file_info.st_blocks);
    printf("Taille des blocs alloués : %d octets\n", file_info.st_blksize);
    printf("Inode : %llu\n", file_info.st_ino);
}