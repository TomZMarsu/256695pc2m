set(skola_HEADER
   main.h
   datum.h
   ptak.h
   pozorovani.h
   vypisovac.h
   nacitacdat.h
   stringutil.h
   ovladac_pozorovani.h
   ovladac_seznamu_pozorovani.h
   spravce_terminalu.h
   ukladac_dat.h
)

PREPEND(skola_HEADER)

set(skola_HEADER ${skola_HEADER}  PARENT_SCOPE)
