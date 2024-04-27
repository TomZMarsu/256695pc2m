#ifndef VYPISOVAC_H
#define VYPISOVAC_H
#include "ptak.h"
#include "pozorovani.h"
#include <stdio.h>
#include <stdbool.h>

int vypis_informace_o_ptakovi(Ptak ptak);
int vypis_tabulku_z_pozorovani(Pozorovani* pozorovani);

#endif