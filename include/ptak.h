#ifndef PTAK_H
#define PTAK_H
#include "malloc.h"
#include "stringutil.h"

typedef struct Ptak {
    char* nazev;
    char* popis_vzhledu;
    char* vyskyt;

    // Hodnoty pro pozorovani
    unsigned int pocet_nalezu;
    char* poznamky;

    // Odkaz na další položku lineárního seznamu
    struct Ptak* dalsi_ptak;

    // ID pro odkazovani pri vypisu
    unsigned int ID;
} Ptak;

// Konstruktor pro Ptak
Ptak* ptak_init();

// Dealokace ptaka
void smazat_ptaka(Ptak* ptak);

// Vycet: Radici podminka pro ptaka
typedef enum Ptak_radici_podminka {
    PTAK_DRUH = 1,
    PTAK_POCET,
    PTAK_POZNAMKA
} Ptak_radici_podminka;

// Funkce pro serazeni ptaku
void seradit_pozorovani(Ptak** prvni_ptak_arg, Ptak_radici_podminka radici_podminka, Smer_trizeni smer_trizeni);
#endif