set(skola_SRC
    main.c
    datum.c
    vypisovac.c
    nacitacdat.c
    stringutil.c
    ptak.c
    pozorovani.c
    ovladac_pozorovani.c
    ovladac_seznamu_pozorovani.c
    spravce_terminalu.c
)

PREPEND(skola_SRC)

set(skola_SRC ${skola_SRC}  PARENT_SCOPE)
