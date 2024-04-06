#ifndef DATUM_H
#define DATUM_H
#include <stdio.h>
#include <malloc.h>
#define DELKA_TEXTOVE_REPREZENTACE 18

typedef struct Datum {
    unsigned short int den;
    unsigned short int mesic;
    unsigned short int rok;

    unsigned short int hodiny;
    unsigned short int minuty;

    char* textova_reprezentace;
} Datum;

// String musí mít alespoň 18 znaků
void datum_na_string(Datum* datum);

// Konstruktor pro Datum
Datum* datum_init();



#endif