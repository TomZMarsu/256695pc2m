#ifndef DATABAZOVA_POLOZKA_H
#define DATABAZOVA_POLOZKA_H

// Typ databázové položky pro správné rozeznání a práci s položkou
typedef enum typ_databazove_polozky {
    INT,
    FLOAT,
    STRING,
    KATEGORIE
} typ_databazove_polozky;

typedef struct databazova_polozka {
    // Ukazatel na hodnotu databázové položky
    void* ptr;

    typ_databazove_polozky typ;
} databazova_polozka;

#endif