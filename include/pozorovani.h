#ifndef POZOROVANI_H
#define POZOROVANI_H
#include "datum.h"
#include "ptak.h"

typedef struct Pozorovani {
    Datum* datum_pozorovani;
    char* poloha;
    char* poznamka;

    // Odkaz na linearni seznam
    Ptak* prvni_ptak;
} Pozorovani;

#endif