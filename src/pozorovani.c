#include "pozorovani.h"

Pozorovani* pozorovani_init() {
    Pozorovani* pozorovani = (Pozorovani*) malloc(sizeof(Pozorovani));
    pozorovani->datum_pozorovani = datum_init();
    pozorovani->poloha = NULL;
    pozorovani->poznamka = NULL;
    pozorovani->prvni_ptak = NULL;
    pozorovani->dalsi_pozorovani = NULL;
    pozorovani->ID = 0;
    pozorovani->doslo_k_zmene = false;

    kopirovat_string(&(pozorovani->poloha), "");
    kopirovat_string(&(pozorovani->poznamka), "");

    return pozorovani;
}

Ptak** posledni_ptak_v_pozorovani(Pozorovani* pozorovani) {
    Ptak** momentalne_posledni_ptak = &(pozorovani->prvni_ptak);

    while (*momentalne_posledni_ptak != NULL) {
        momentalne_posledni_ptak = &((*momentalne_posledni_ptak)->dalsi_ptak);
    }

    return momentalne_posledni_ptak;
}

Pozorovani** posledni_pozorovani_v_seznamu(Pozorovani* prvni_pozorovani) {
    Pozorovani** momentalni_pozorovani = &(prvni_pozorovani);

    while (*momentalni_pozorovani != NULL) {
        momentalni_pozorovani = &((*momentalni_pozorovani)->dalsi_pozorovani);
    }

    return momentalni_pozorovani;
}

void smazat_pozorovani(Pozorovani* pozorovani) {
    Ptak* prvni_ptak = pozorovani->prvni_ptak;

    while(prvni_ptak != NULL) {
        Ptak* tmp = prvni_ptak->dalsi_ptak;
        smazat_ptaka(prvni_ptak);
        prvni_ptak = tmp;
    }

    smazat_datum(pozorovani->datum_pozorovani);
    free(pozorovani->poloha);
    free(pozorovani->poznamka);
    free(pozorovani);
}

void smazat_seznam_pozorovani(Pozorovani* prvni_pozorovani) {
    Pozorovani* momentalni_pozorovani = prvni_pozorovani;

    while (momentalni_pozorovani != NULL) {
        Pozorovani* tmp = momentalni_pozorovani;
        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;
        smazat_pozorovani(tmp);
        tmp = NULL;
    }
}

Pozorovani* Pozorovani_prohodit_pozorovani(Pozorovani* pozorovani1, Pozorovani* pozorovani2) {
    Pozorovani* tmp = pozorovani2->dalsi_pozorovani;
    pozorovani2->dalsi_pozorovani = pozorovani1;
    pozorovani1->dalsi_pozorovani = tmp;
    
    return pozorovani2;
}

int pocet_pozorovani(Pozorovani* prvni_pozorovani) {
    int pocet = 0;
    Pozorovani* momentalni_pozorovani = prvni_pozorovani;

    while (momentalni_pozorovani) {
        pocet += 1;
        momentalni_pozorovani = momentalni_pozorovani->dalsi_pozorovani;
    }

    return pocet;
}

bool Pozorovani_porovnej_pozorovani(Pozorovani* pozorovani1, Pozorovani* pozorovani2, Pozorovani_radici_podminka radici_podminka) {
    bool vystup = false;
    switch (radici_podminka) {
        case POZOROVANI_DATUM:
            vystup = porovnat_datum(pozorovani1->datum_pozorovani, pozorovani2->datum_pozorovani);
            break;

        case POZOROVANI_POZNAMKA:
            vystup = (strcmp(pozorovani1->poznamka, pozorovani2->poznamka) > 0);
            break;

        case POZOROVANI_MISTO:
            vystup = (strcmp(pozorovani1->poloha, pozorovani2->poloha) > 0);
            break;

        // NEPLATNÁ/NEDEFINOVANÁ TŘÍDÍCÍ PODMÍNKA -> vyvolej paniku programu
        default:
            exit(EXIT_FAILURE);
    }

    return vystup;
}

void Pozorovani_prevratit_seznam(Pozorovani** prvni_pozorovani) {
    // Předchozí pták
    Pozorovani* pred = NULL;

    // Současný pták
    Pozorovani* souc = *prvni_pozorovani;

    // Další pták
    Pozorovani* dalsi = NULL;

    while (souc != NULL) {
        dalsi = souc->dalsi_pozorovani;

        souc->dalsi_pozorovani = pred;

        pred = souc;
        souc = dalsi;
    }

    *prvni_pozorovani = pred;
}

void seradit_seznam_pozorovani(Pozorovani** prvni_pozorovani_arg, Pozorovani_radici_podminka radici_podminka, Smer_trizeni smer_trizeni) {
    Pozorovani** momentalni_pozorovani = NULL;

    int i = 0;
    int j = 0;
    bool vymena = false;

    int pocet = pocet_pozorovani(*prvni_pozorovani_arg);

    for (i = 0; i <= pocet; i++) {
        momentalni_pozorovani = prvni_pozorovani_arg;
        vymena = false;
 
        for (j = 0; j < pocet - i - 1; j++) {
            Pozorovani* pozorovani1 = *momentalni_pozorovani;
            Pozorovani* pozorovani2 = pozorovani1->dalsi_pozorovani;
 
            if (Pozorovani_porovnej_pozorovani(pozorovani1, pozorovani2, radici_podminka)) {
                *momentalni_pozorovani = Pozorovani_prohodit_pozorovani(pozorovani1, pozorovani2);
                vymena = true;
            }
 
            momentalni_pozorovani = &(*momentalni_pozorovani)->dalsi_pozorovani;
        }
 
        // Break if the loop ended without any swap
        if (!vymena)
            break;
    }

    if (smer_trizeni == SESTUPNE)
        Pozorovani_prevratit_seznam(prvni_pozorovani_arg);
}