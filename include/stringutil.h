#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "datum.h"
#include "spravce_terminalu.h"

#define NACTI_VSTUP_VELIKOST_BUFFERU 1024

void kopirovat_string(char** cil, char* zdroj);


// Nacte vstup jako string od uzivatele. NACTI_VSTUP_VELIKOST_BUFFERU určuje maximální počet znaků
void nacti_string_od_uzivatele(char** cil, char* pozadavek, bool vymazat_vstup);

// Nacte vstup jako integer od uzivatele.
int nacti_int_od_uzivatele(char* pozadavek, bool vymazat_vstup);

// Upravi string na zaklade uzivatelskeho vstupu
void uprav_string(char* sloupec, char** string_ktery_upravit);

// Upravi int na zaklade uzivatelskeho vstupu
void uprav_int(char* sloupec, int* int_ktery_upravit);

// Upravi datum na zaklade uzivatelskeho vstupu
void uprav_datum(Datum* datum_ktery_upravit);

// Wrapper pro nacti_int_od_uzivatele, nacte int na zaklade uzivatelskeho vstupu, pricemz int musi lezet v intervalu <min;max>
int nacti_overene_int_od_uzivatele(char* pozadavek, bool vymazat_vstup, int min, int max);

// Vyčet - směr třízení
typedef enum Smer_trizeni {
    VZESTUPNE = 1,
    SESTUPNE = 2
} Smer_trizeni;

#endif