#include "stringutil.h"

// Kopie stringu s dynamickou paměťovou alokaci
void kopirovat_string(char** cil, char* zdroj) {
    unsigned int delka_stringu = strlen(zdroj);
    *cil = (char*) calloc(delka_stringu + 1, sizeof(char));
    strncpy(*cil, zdroj, delka_stringu);
}

// Vymaze z konzole dany pocet radku
void vymazat_radek(int pocet_radku) {
    for (int i = 0; i < pocet_radku; i++) {
        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line
    }
}

// Nacte vstup jako string od uzivatele. NACTI_VSTUP_VELIKOST_BUFFERU určuje maximální počet znaků
char* nacti_string_od_uzivatele(char* pozadavek, bool vymazat_vstup) {
    char buffer[NACTI_VSTUP_VELIKOST_BUFFERU] = {0};

    printf("%s: ", pozadavek);
    
    // Přečtení vstupu a odstraneni Enteru/noveho radku z retezce
    fgets(buffer, NACTI_VSTUP_VELIKOST_BUFFERU, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    // Vytvoření nového stringu v paměti
    char* precteny_vstup;
    kopirovat_string(&precteny_vstup, buffer);

    if (vymazat_vstup) vymazat_radek(1);

    return precteny_vstup;

}

int nacti_int_od_uzivatele(char* pozadavek, bool vymazat_vstup) {
    int cislo = 0;

    printf("%s: ", pozadavek);

    scanf(" %d", &cislo);
    while ((getchar()) != '\n'); // Vycisti buffer
    if (vymazat_vstup) vymazat_radek(1);

    return cislo;
}