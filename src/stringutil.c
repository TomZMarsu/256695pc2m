#include "stringutil.h"

// Kopie stringu s dynamickou paměťovou alokaci
void kopirovat_string(char** cil, char* zdroj) {
    unsigned int delka_stringu = strlen(zdroj);

    // Uvolni predchozi pamet cile, aby se zabranilo memory leaku
    if (*cil != NULL) {
        free(*cil);
        *cil = NULL;
    }

    //*cil = calloc(delka_stringu+1, sizeof(char));
    //strcpy(*cil, zdroj);
    *cil = strdup(zdroj);
}

// Vymaze z konzole dany pocet radku
void vymazat_radek(int pocet_radku) {
    for (int i = 0; i < pocet_radku; i++) {
        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line
    }
}

// Nacte vstup jako string od uzivatele. NACTI_VSTUP_VELIKOST_BUFFERU určuje maximální počet znaků
void nacti_string_od_uzivatele(char** cil, char* pozadavek, bool vymazat_vstup) {
    char buffer[NACTI_VSTUP_VELIKOST_BUFFERU] = {0};

    printf("%s: ", pozadavek);
    
    // Přečtení vstupu a odstraneni Enteru/noveho radku z retezce
    fgets(buffer, NACTI_VSTUP_VELIKOST_BUFFERU, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    // Vytvoření nového stringu v paměti
    char* precteny_vstup = NULL;
    kopirovat_string(cil, buffer);

    if (vymazat_vstup) vymazat_radek(1);
}

int nacti_int_od_uzivatele(char* pozadavek, bool vymazat_vstup) {
    int cislo = 0;
    char prectene_cislo[NACTI_VSTUP_VELIKOST_BUFFERU] = {0};

    printf("%s: ", pozadavek);

    fgets(prectene_cislo, NACTI_VSTUP_VELIKOST_BUFFERU, stdin);
    sscanf(prectene_cislo, " %d", &cislo);

    if (vymazat_vstup) vymazat_radek(1);

    return cislo;
}

void uprav_string(char* sloupec, char** string_ktery_upravit) {
    int delka_vyzva = strlen(" ()") + strlen(*string_ktery_upravit) + strlen(sloupec) + 1;
    char* vyzva = (char*) calloc(delka_vyzva, sizeof(char));
    sprintf(vyzva, "%s (%s)", sloupec, *string_ktery_upravit);
    char* odpoved = NULL;
    nacti_string_od_uzivatele(&odpoved, vyzva, true);
    if(strcmp(odpoved, "")) {
        kopirovat_string(string_ktery_upravit, odpoved);
    }
    free(odpoved);
    free(vyzva);
}

void uprav_int(char* sloupec, int* int_ktery_upravit) {
    // Převod int na string
    char str_int_ktery_upravit[10] = {0};
    sprintf(str_int_ktery_upravit, "%d", *int_ktery_upravit);

    int delka_vyzva = strlen(" ()") + strlen(str_int_ktery_upravit) + strlen(sloupec) + 1;
    char* vyzva = (char*) calloc(delka_vyzva, sizeof(char));
    sprintf(vyzva, "%s (%d)", sloupec, *int_ktery_upravit);
    char* odpoved = NULL;
    nacti_string_od_uzivatele(&odpoved, vyzva, false);
    if(strcmp(odpoved, "")) {
        sscanf(odpoved, "%d", int_ktery_upravit);
    }
    free(odpoved);
    free(vyzva);
}