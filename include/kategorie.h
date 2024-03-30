#ifndef KATEGORIE_H
#define KATEGORIE_H

typedef struct kategorie {
    unsigned short int pocet_kategorii;
    char** nazvy_kategorii;
} kategorie;

typedef struct polozka_kategorie
{
    unsigned short int id;
    kategorie* kategorie;
    
} polozka_kategorie;

#endif