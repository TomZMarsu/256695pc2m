#ifndef OVLADAC_SEZNAMU_POZOROVANI_H
#define OVLADAC_SEZNAMU_POZOROVANI_H
#include "pozorovani.h"
#include "vypisovac.h"
#include "stringutil.h"
#include <stdbool.h>
#include "ptak.h"
#include "datum.h"
#include "main.h"
#include "ovladac_pozorovani.h"

#define OPSZ_VELIKOST_NABIDKY 6
#define OPSZ_VELIKOST_NABIDKY_TRIZENI 4
#define OPSZ_VELIKOST_NABIDKY_SMERU_TRIZENI 3

// Vykresluje zobrazovac pro hlavni nabidku
Pozorovani* vykreslovat_seznam_pozorovani(Pozorovani** main_prvni_pozorovani_ptr);

// SOUKROMÉ FUNKCE - POLOŽKY MENU
Pozorovani* opsz_nove_pozorovani();
bool opsz_prejit_do_pozorovani(Pozorovani* pozorovani_ptr, int pocet_radku);
bool opsz_odstranit_pozorovani(Pozorovani** pozorovani_ptr);
bool opsz_seradit(Pozorovani* pozorovani);

// SOUKROMÉ VÝČTOVÉ TYPY
typedef enum Opsz_nabidka {
    OPSZ_NOVE_POZOROVANI = 1,
    OPSZ_PREJIT_DO_POZOROVANI,
    OPSZ_ODSTRANIT_POZOROVANI,
    OPSZ_SERADIT,
    OPSZ_UKONCIT
} Opsz_nabidka;

#endif