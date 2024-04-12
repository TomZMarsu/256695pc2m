#include "stringutil.h"

// Kopie stringu s dynamickou paměťovou alokaci
void kopirovat_string(char** cil, char* zdroj) {
    // Uvolni predchozi pamet cile, aby se zabranilo memory leaku
    if (*cil != NULL) {
        free(*cil);
        *cil = NULL;
    }

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
    nacti_string_od_uzivatele(&odpoved, vyzva, true);
    if(strcmp(odpoved, "")) {
        sscanf(odpoved, "%d", int_ktery_upravit);
    }
    free(odpoved);
    free(vyzva);
}

void uprav_datum(Datum* datum_ktery_upravit) {
    char* odpoved = NULL;

    // 41 znaků -> Delka stringu VYZVA_ZACATEK
    // 1 -> Delka stringu VYZVA_KONEC
    // DELKA_TEXTOVE_REPREZENTACE -> delka data včetně \0
    char vyzva[41+2+DELKA_TEXTOVE_REPREZENTACE] = {0};

    // Konstatni retezce
    const char VYZVA_ZACATEK[] = "Zadej datum ve formatu DD.MM.RRRR HH:MM (";
    const char VYZVA_KONEC[] = ")";

    // Aktualizace soucasneho data
    datum_na_string(datum_ktery_upravit);

    // Slouceni retezce
    sprintf(vyzva, "%s%s%s", VYZVA_ZACATEK, datum_ktery_upravit->textova_reprezentace, VYZVA_KONEC);

    // Nacteni vstupu od uzivatele
    nacti_string_od_uzivatele(&odpoved, vyzva, true);

    // Zpracovani odpovedi
    if (strcmp(odpoved, "")) {
        sscanf(odpoved, "%2d.%2d.%4d %2d:%2d", 
            &(datum_ktery_upravit->den),
            &(datum_ktery_upravit->mesic),
            &(datum_ktery_upravit->rok),
            &(datum_ktery_upravit->hodiny),
            &(datum_ktery_upravit->minuty)
        );

        // Aktualizace noveho data
        datum_na_string(datum_ktery_upravit);
    }

    free(odpoved);
}