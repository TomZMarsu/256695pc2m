#ifndef POZOROVANI_H
#define POZOROVANI_H
#include "datum.h"
#include <stdbool.h>
#include "ptak.h"

typedef struct Pozorovani {
    Datum* datum_pozorovani;
    char* poloha;
    char* poznamka;
    int ID;

    // Odkaz na linearni seznam
    Ptak* prvni_ptak;

    // Odkaz na dalsi pozorovani v linearnim seznamu
    struct Pozorovani* dalsi_pozorovani;

    // Priznak pro ukladaci system. Jesliže ano, přepiš soubor
    bool doslo_k_zmene;
} Pozorovani;

#include <malloc.h>
#include "stringutil.h"

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

typedef enum Pozorovani_radici_podminka {
    POZOROVANI_DATUM = 1,
    POZOROVANI_MISTO,
    POZOROVANI_POZNAMKA
} Pozorovani_radici_podminka;

Pozorovani* Pozorovani_prohodit_pozorovani(Pozorovani* pozorovani1, Pozorovani* pozorovani2);

int pocet_pozorovani(Pozorovani* prvni_pozorovani);

bool Pozorovani_porovnej_pozorovani(Pozorovani* pozorovani1, Pozorovani* pozorovani2, Pozorovani_radici_podminka radici_podminka);

void Pozorovani_prevratit_seznam(Pozorovani** prvni_pozorovani);

void seradit_seznam_pozorovani(Pozorovani** prvni_pozorovani_arg, Pozorovani_radici_podminka radici_podminka, Smer_trizeni smer_trizeni);

#endif