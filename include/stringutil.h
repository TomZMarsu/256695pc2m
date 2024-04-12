#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <datum.h>

#define NACTI_VSTUP_VELIKOST_BUFFERU 1024

void kopirovat_string(char** cil, char* zdroj);
void vymazat_radek(int pocet_radku);

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
#endif