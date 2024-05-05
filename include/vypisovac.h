#ifndef VYPISOVAC_H
#define VYPISOVAC_H

#include <stdio.h>
#include <stdbool.h>

#include "ptak.h"
#include "pozorovani.h"

int vypis_informace_o_ptakovi(Ptak ptak);
int vypis_tabulku_z_pozorovani(Pozorovani* pozorovani);
int vypis_tabulku_seznamu_pozorovani(Pozorovani* prvni_pozorovani);



#endif //VYPISOVAC_H