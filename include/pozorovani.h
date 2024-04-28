#ifndef POZOROVANI_H
#define POZOROVANI_H
#include "datum.h"
#include "ptak.h"
#include <malloc.h>

typedef struct Pozorovani {
    Datum* datum_pozorovani;
    char* poloha;
    char* poznamka;
    int ID;

    // Odkaz na linearni seznam
    Ptak* prvni_ptak;

    // Odkaz na dalsi pozorovani v linearnim seznamu
    struct Pozorovani* dalsi_pozorovani;
} Pozorovani;

// Konstruktor pro Pozorovani
Pozorovani* pozorovani_init();

// Nalezne posledniho ptaka v seznamu
Ptak** posledni_ptak_v_pozorovani(Pozorovani* pozorovani);

// Nalezne posledni pozorovani v seznamu
Pozorovani** posledni_pozorovani_v_seznamu(Pozorovani* prvni_pozorovani);

// Dealokace pozorovani
void smazat_pozorovani(Pozorovani* pozorovani);

// Dealokace seznamu pozorovani
void smazat_seznam_pozorovani(Pozorovani* prvni_pozorovani);

#endif