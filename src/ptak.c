#include "ptak.h"

Ptak* ptak_init() {
    Ptak* ptak = malloc(sizeof(Ptak));

    ptak->dalsi_ptak = NULL;
    ptak->ID = 0;
    ptak->pocet_nalezu = 0;

    ptak->nazev = NULL;
    ptak->popis_vzhledu = NULL;
    ptak->poznamky = NULL;
    ptak->vyskyt = NULL;

    // Stringy se berou jako dynamicky alokované, aby se zabranilo nedefinovanému chování v případě dealokace
    kopirovat_string(&(ptak->nazev), "NEDEFINOVANY PTAK");
    kopirovat_string(&(ptak->popis_vzhledu), "");
    kopirovat_string(&(ptak->poznamky), "");
    kopirovat_string(&(ptak->vyskyt), "");
    
    return ptak;
}

Ptak* Ptak_prohodit_ptaky(Ptak* ptak1, Ptak* ptak2) {
    Ptak* tmp = ptak2->dalsi_ptak;
    ptak2->dalsi_ptak = ptak1;
    ptak1->dalsi_ptak = tmp;
    
    return ptak2;
}

int Ptak_pocet_ptaku(Ptak* prvni_ptak) {
    int pocet = 0;
    Ptak* momentalni_ptak = prvni_ptak;

    while (momentalni_ptak) {
        pocet += 1;
        momentalni_ptak = momentalni_ptak->dalsi_ptak;
    }

    return pocet;
}

bool Ptak_porovnej_ptaky(Ptak* ptak1, Ptak* ptak2, Ptak_radici_podminka radici_podminka) {
    bool vystup = false;
    switch (radici_podminka) {
        case POCET:
            vystup = ptak1->pocet_nalezu > ptak2->pocet_nalezu;
            break;

        case POZNAMKA:
            vystup = (strcmp(ptak1->poznamky, ptak2->poznamky) > 0);
            break;

        case DRUH:
            vystup = (strcmp(ptak1->nazev, ptak2->nazev) > 0);
            break;

        // NEPLATNÁ/NEDEFINOVANÁ TŘÍDÍCÍ PODMÍNKA -> vyvolej paniku programu
        default:
            exit(EXIT_FAILURE);
    }

    return vystup;
}

void Ptak_prevratit_seznam(Ptak** prvni_ptak) {
    // Předchozí pták
    Ptak* pred = NULL;

    // Současný pták
    Ptak* souc = *prvni_ptak;

    // Další pták
    Ptak* dalsi = NULL;

    while (souc != NULL) {
        dalsi = souc->dalsi_ptak;

        souc->dalsi_ptak = pred;

        pred = souc;
        souc = dalsi;
    }

    *prvni_ptak = pred;
}

void seradit_ptaky(Ptak** prvni_ptak_arg, Ptak_radici_podminka radici_podminka, Smer_trizeni smer_trizeni) {
    Ptak** momentalni_ptak = NULL;

    int i = 0;
    int j = 0;
    bool vymena = false;

    int pocet = Ptak_pocet_ptaku(*prvni_ptak_arg);

    for (i = 0; i <= pocet; i++) {
        momentalni_ptak = prvni_ptak_arg;
        vymena = false;
 
        for (j = 0; j < pocet - i - 1; j++) {
            Ptak* ptak1 = *momentalni_ptak;
            Ptak* ptak2 = ptak1->dalsi_ptak;
 
            if (Ptak_porovnej_ptaky(ptak1, ptak2, radici_podminka)) {
                *momentalni_ptak = Ptak_prohodit_ptaky(ptak1, ptak2);
                vymena = true;
            }
 
            momentalni_ptak = &(*momentalni_ptak)->dalsi_ptak;
        }
 
        // Break if the loop ended without any swap
        if (!vymena)
            break;
    }

    if (smer_trizeni == SESTUPNE)
        Ptak_prevratit_seznam(prvni_ptak_arg);
}

void smazat_ptaka(Ptak* ptak) {
    free(ptak->nazev);
    ptak->nazev = NULL;
    free(ptak->popis_vzhledu);
    ptak->popis_vzhledu = NULL;
    free(ptak->poznamky);
    ptak->poznamky = NULL;
    free(ptak->vyskyt);
    ptak->vyskyt = NULL;
    free(ptak);
    ptak=NULL;
}