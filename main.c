#include <stdio.h>
#include "lista.h"
#include "menu.h"

int main(void)
{
    element *lista = NULL;

    ustaw_kodowanie();
    lista = wiadomosc_powitalna(lista);

    lista = clear(lista);
    return 0;
}

