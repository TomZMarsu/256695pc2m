#ifndef POZOROVANI_H
#define POZOROVANI_H
#include "datum.h"
#include "ptak.h"
#include <malloc.h>

typedef struct Pozorovani {
    Datum* datum_pozorovani;
    char* poloha;
    char* poznamka;

    // Odkaz na linearni seznam
    Ptak* prvni_ptak;
} Pozorovani;

// Konstruktor pro Pozorovani
Pozorovani* pozorovani_init();

// Nalezne posledniho ptaka v seznamu
Ptak** posledni_ptak_v_pozorovani(Pozorovani* pozorovani);

// Dealokace pozorovani
void smazat_pozorovani(Pozorovani* pozorovani);

#endif