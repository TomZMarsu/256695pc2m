#include <malloc.h>
#include "ptak.h"
#include "pozorovani.h"
#include "datum.h"
#include "vypisovac.h"
#include "nacitacdat.h"

int main() {
    Pozorovani pozorovani = *nacist_pozorovani("./tests/test_nacteni_pozorovani/pozorovani_cele1.dat");
    vypis_tabulku_z_pozorovani(pozorovani); 

    return 0;
}