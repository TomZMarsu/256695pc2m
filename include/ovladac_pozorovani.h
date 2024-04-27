#ifndef OVLADAC_POZOROVANI_H
#define OVLADAC_POZOROVANI_H
#include "pozorovani.h"
#include "vypisovac.h"
#include "stringutil.h"
#include <stdbool.h>
#include "ptak.h"
#include "datum.h"

#define OPZ_VELIKOST_NABIDKY 10
#define OPZ_VELIKOST_NABIDKY_TRIZENI 4
#define OPZ_VELIKOST_NABIDKY_SMERU_TRIZENI 3

// Vykresluje zobrazovac pro zcela nove pozorovani
Pozorovani* vykreslovat_pozorovani_novy();

// SOUKROMÉ FUNKCE - POLOŽKY MENU
Ptak* opz_pridat_ptaka();
bool opz_upravit_ptaka(Pozorovani** pozorovani);
bool opz_odstranit_ptaka(Pozorovani** pozorovani_ptr);
bool opz_upravit_udaje_o_pozorovani(Pozorovani* pozorovani);
bool opz_seradit(Pozorovani* pozorovani);

// SOUKROMÉ VÝČTOVÉ TYPY
typedef enum Opz_nabidka {
    PRIDAT_PTAKA = 1,
    UPRAVIT_PTAKA,
    ODSTRANIT_PTAKA,
    UPRAVIT_POZOROVANI,
    VRATIT_SE_ZPET,
    SERADIT,
    UKONCIT
} Opz_nabidka;

#endif