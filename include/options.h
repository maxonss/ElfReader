#ifndef OPTIONS_H
#define OPTIONS_H

// Définition de la structure pour stocker les informations sur chaque option
typedef struct {
    const char *name;          // Utilisation de const char * pour les chaînes constantes
    void (*function)(char *);  // Type de fonction ajusté
    int required_arg;          // Indique si l'option requiert un argument (1 = oui, 0 = non)
} Option;

// Déclaration des fonctions liées à chaque option
void option_d(const char *content);
void option_s(const char *content);
void print_section_name_size(const char *content);
void print_entrypoint_address_program(const char *content);
void option_t(const char *content);
void option_l(const char *content);
void option_c(const char *content);
void option_h();
void print_basic_info(const char *content);
#endif // OPTIONS_H
