#include "datum.h"
#include <string.h>

int main() {
    Datum datum = *(datum_init());

    if (datum.den != 0) return 1;
    if (datum.hodiny != 0) return 2;
    if (datum.mesic != 0) return 3;
    if (datum.minuty != 0) return 4;
    if (datum.rok != 0) return 5;
    if (strcmp(datum.textova_reprezentace, "00.00. 0000 00:00")) return 6;
    printf("%s\n", datum.textova_reprezentace);

    return 0;
}