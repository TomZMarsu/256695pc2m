#ifndef RADEK_H
#define RADEK_H
#include "databazova_polozka.h"

typedef struct radek
{
    // Následující položka lineárního seznamu
    radek* nasledujici_polozka;

    // První položka (lze chápat jako sloupec, vede na lin. seznam)
    databazova_polozka* prvni_polozka;
};

#endif