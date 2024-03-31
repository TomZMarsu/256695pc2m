#ifndef DATUM_H
#define DATUM_H
#include <stdio.h>

typedef struct Datum {
    unsigned short int den;
    unsigned short int mesic;
    unsigned short int rok;

    unsigned short int hodiny;
    unsigned short int minuty;

    char textova_reprezentace[18];
} Datum;

// String musí mít alespoň 18 znaků
void datum_na_string(Datum* datum);

#endif