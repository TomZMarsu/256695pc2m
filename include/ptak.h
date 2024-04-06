#ifndef PTAK_H
#define PTAK_H
#include "malloc.h"

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

#endif