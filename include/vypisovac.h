#ifndef VYPISOVAC_H
#define VYPISOVAC_H

#include <stdio.h>
#include <stdbool.h>

#include "ptak.h"
#include "pozorovani.h"
#include "spravce_terminalu.h"

// Rezervuje X radku, zbytek je pro volne pouziti vypisu záznamu
#define REZERVACE_RADKU_OPZ 22
#define REZERVACE_RADKU_OPSZ 14

#define NEVYKRESLENA_POLOZKA_ID -1

int vypis_informace_o_ptakovi(Ptak ptak);
int vypis_tabulku_z_pozorovani(Pozorovani* pozorovani, int stranka, int pocet_ptaku_i);
int vypis_tabulku_seznamu_pozorovani(Pozorovani* prvni_pozorovani, int stranka, int pocet_pozorovani_i);



#endif //VYPISOVAC_H