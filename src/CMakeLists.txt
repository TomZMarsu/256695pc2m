set(skola_SRC
    main.c
    datum.c
    vypisovac.c
)

PREPEND(skola_SRC)

set(skola_SRC ${skola_SRC}  PARENT_SCOPE)
