#ifndef OVLADAC_POZOROVANI_H
#define OVLADAC_POZOROVANI_H
#include "pozorovani.h"
#include "vypisovac.h"
#include "stringutil.h"
#include <stdbool.h>
#include "ptak.h"
#include "datum.h"

#define OPZ_VELIKOST_NABIDKY 6

// Vykresluje zobrazovac pro zcela nove pozorovani
Pozorovani* vykreslovat_pozorovani_novy();

// SOUKROMÉ FUNKCE
Ptak* opz_pridat_ptaka();
bool opz_upravit_ptaka(Pozorovani** pozorovani);
bool opz_odstranit_ptaka(Pozorovani** pozorovani_ptr);

#endif