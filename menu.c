#include "menu.h"
#include "obraz.h"
#include "plik.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void ustaw_kodowanie()
{
#ifdef WIN32
    system("chcp 65001");
#endif
}

void wiadomosc_powitalna(element *lista)
{
    printf("ODCZYTYWANIE OBRAZU\n--------------------------------\n");
    odczytaj_plik(lista);
}
