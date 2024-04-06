#ifndef OVLADAC_POZOROVANI_H
#define OVLADAC_POZOROVANI_H
#include "pozorovani.h"
#include "vypisovac.h"
#include "stringutil.h"
#include <stdbool.h>
#include "ptak.h"

#define OPZ_VELIKOST_NABIDKY 5

// Vykresluje zobrazovac pro zcela nove pozorovani
Pozorovani* vykreslovat_pozorovani_novy();

// SOUKROMÉ FUNKCE
Ptak* opz_pridat_ptaka();

#endif