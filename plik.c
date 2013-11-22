#include "plik.h"
#include <stdlib.h>
#include <stdio.h>

void odczytaj_plik()
{
    char *nazwa_pliku;
    printf("Podaj nazwę pliku: ");
    scanf("%s", nazwa_pliku);
    if (_DEBUG) printf ("Nazwa pliku: %s\n", nazwa_pliku);

}
