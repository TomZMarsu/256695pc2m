# Tomáš Svoboda - PC2M Projekt - Databáze pozorování ptáků

# Popis programu
Program slouží jako záznamník pro ptačkaře (případně pro pozorovatele jiných zvířat). Pozorovatel si zde může vytvářet **pozorování**, což může být nějaký procházka, náhodné koukání z okna nebo jiná přiležitost, kdy chce pozorovatel zapisovat pozorované zvěrstvo. 

Program je z 95% hotový, poslední věcí by bylo jen zprovoznění načítání pozorování při spuštění programu (nicméně v testech \[podrobně později\] se nachází funkční program na načtení souboru do pozorovani). Důvodem je nestíhání studenta. 

Program byl programován za pomocí kompilátoru GCC (pro Windows MinGW GCC) v **Linuxu Fedora 39**, s užitím CMake (nástroj pro kompilování a testování), VSCode (IDE/textový editor) a Valgrind (debugování paměti/detekce memory leaků).

# Funkce programu

## Zobrazovací systém
- program reaguje na změny velikosti terminálu, při zadání volby z nabídky se program přizpůsobí velikosti terminálu
- pokud se zobrazení nevleze do terminálu, začíná stránkovat vypsané položky (pozorování nebo ptáci)
- položka mají ID. **ID není unikátní pro každou položku, ale slouží pro vybírání položky v seznamu**
- program je celkem odolný vůči neplatnému vstupu, při špatném vstupu nereaguje nebo nechá zopakovat vstup
- NEPODCHYCENÁ CHYBA: Při přiliš malé velikosti terminálu dochází ke špatnému stránkování

## Seznam pozorování
- objeví se při spuštění programu
- uživatel má možnost třídit seznam podle jednotlivých sloupců
- lze přidávat nové pozorování, odstraňovat, třídit nebo vcházet do pozorování
- ukončením programu se vyčistí paměť a uloží pozorování do souborů

## Pozorování
- Při tvorbě pozorování se program ptá uživatele na datum, místo pozorování a případné poznámky. Veškeré kolonky se mohou nechat prázdné
- Lze přidávat ptáky, odstraňovat je, setřizovat podle sloupců a připadně upravovat údaje o pozorování podle potřeby.
- Také je možné se vrátit zpět do seznamu pozorování nebo ukončit program
- NEPODCHYCENÝ DETAIL: Datum nemá ohraničenou horní a dolní hranici, proto lze zadávat i nultý nebo čtyrycátý měsíc...

# Plnění kriterií (co je splněno a co ne)
- práce se souborem (soubory) **(na 90% splněno, chybí pouze implementace načítání souboru při otevření programu. Samotné načítání funguje v testech)**
- databáze ve formátu seznam (lineární seznam, strom) **(splněno)**
- přidat položku **(splněno)**
- odebrat položku **(splněno)**
- hledat (podle různých polí)
- setřídit (podle různých kriterií) **(splněno)**

**Bonusy:**
- upravit existující položku **(splněno)**
- filtry
- import a export do .csv formátu (položek, podvýběru atd…)

# Popis fungování programu
## Popis souboru
| Soubor                       | Účel                                                                                                          |
| ---------------------------- | ------------------------------------------------------------------------------------------------------------- |
| datum.h                      | Struktura data, a práce s ním spojená (inicializace, dealokace v paměti, převod na text)                      |
| main.h                       | Hlavní funkce main (načítá seznam pozorování) a funkce pro ukončnení programu (uložení dat, vyčištění paměti) |
| nacitacdat.h                 | Slouží pro načtení souboru do struktury Pozorovani                                                            |
| ovladac_pozorovani.h         | Vykresluje pozorovani a řeší ovládání (seznam ptáků)                                                          |
| ovladac_seznamu_pozorovani.h | Vykresluje seznam pozorovaní a řeší ovládání                                                                  |
| pozorovani.h                 | Obsahuje definici struktury Pozorovani a obsahuje funkce pro praci s pozorováním (dealokace, třízení...)      |
| ptak.h                       | Obsahuje definici struktury Ptak a podobně jako Pozorovani.h obsahuje funkce pro praci se strukturou          |
| spravce_terminalu.h          | Řeší čistění obrazovky, mazání řádků, velikost okna terminálu                                                 |
| stringutil.h                 | Obsahuje pomocné funkce pro práci se stringy, včetně funkci pro úpravu položek (funkce uprav_string apod.)    |
| ukladac_dat.h                | Ukládá struktury Pozorování do souboru                                                                        |
| vypisovac.h                  | Vypisuje tabulky (seznam pozorování, ptáků)                                                                   |

## Popis složek a některých souborů
| Složka/Soubor  | Účel                                                                         |
| -------------- | ---------------------------------------------------------------------------- |
| CMakeLists.txt | Soubory pro kompilační/testovací systém CMake/CTest                          |
| .gitignore     | Seznam složek, které má Git ignorovat                                        |
| src/           | Zde jsou zdrojové soubory (.c) a testy                                       |
| src/tests/     | Umístění testů                                                               |
| include/       | Hlavičkové soubory (.h)                                                      |
| build/         | Složka, kde je ideální použít příkaz ```cmake ..``` a ```make```             |
| bin/           | Složka, se zkompilovanýma binárkama                                          |

## Popis testů
| Soubor                                   | Účel testu                                                           |
| ---------------------------------------- | -------------------------------------------------------------------- |
| test_datum_textova_reprezentace          | Datum by se měl správně naformátovat do textu                        |
| test_mazani_radku                        | Vizuální kontrola, že se správně mažou řádky                         |
| test_nacteni_pozorovani_cele             | Mělo by se načíst celé pozorování a uložit do struktury, jinak selže |
| test_nacteni_pozorovani_hlavicka_prazdne | Prázdná hlavička by se měla načíst v pořádku                         |
| test_nacteni_pozorovani_hlavicka         | Hlavička by se měla správně načíst                                   |
| test_vypis_ptaka (Nepoužité)             | Mělo by to vypsat informace o ptákovi                                |
| test_vypis_tabulky                       | Vizualní kontrola, že se seznam ptáků správně vypisuje               |

