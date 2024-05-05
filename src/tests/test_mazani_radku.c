#include <stdio.h>
#include "pozorovani.h"
#include "vypisovac.h"
#include "nacitacdat.h"
#include <stdbool.h>
#include "stringutil.h"

int main() {
    printf("==========ZACATEK MAZANI===========\n");
    Pozorovani pozorovani = *nacist_pozorovani("./tests/test_mazani_radku/pozorovani_cele1.dat");
    int p_r = vypis_tabulku_z_pozorovani(&pozorovani, 0, 0); 
    vymazat_radek(p_r);
    printf("==========KONEC MAZANI===========\n");
    printf("Pocet smazanych radku: %d\n", p_r);
    printf("Po mazani by nemelo byt nic po zacatku a pred koncem mazani\n");

    return 0;
}