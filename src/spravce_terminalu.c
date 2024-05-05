#include "spravce_terminalu.h"

// ZISKANI ROZMERU TERMINALU
// Zdroj: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
void ziskej_velikost_terminalu(int* height) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    *height = (int)(w.ws_row);
#endif // Windows/Linux
}
// ZISKANI ROZMERU TERMINALU ^^^^^

// Vymaze z konzole dany pocet radku
void vymazat_radek(int pocet_radku) {
    for (int i = 0; i < pocet_radku; i++) {
        printf("\x1b[1F");
        printf("\x1b[2K");
    }
}