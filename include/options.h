#ifndef OPTIONS_H
#define OPTIONS_H

// Définition de la structure pour stocker les informations sur chaque option
typedef struct {
    const char *name;                 // Utilisation de const char * pour les chaînes constantes
    void (*function)(const char *);   // Type de fonction ajusté
    int required_arg;                 // L'option requiert un argument [0, 1]
} Option;

// Déclaration des fonctions liées à chaque option
void print_text_section_hex(const char *content);
void print_section_count(const char *content);
void print_section_name_size(const char *content);
void print_entrypoint_address_program(const char *content);
void option_t(const char *content);
void option_l(const char *content);
void option_c(const char *content);
void option_h();
void print_basic_info(const char *content);

#endif // OPTIONS_H
