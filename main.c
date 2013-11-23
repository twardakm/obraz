#include <stdio.h>
#include "lista.h"

int main(void)
{
    element *lista = NULL;

    ustaw_kodowanie();
    wiadomosc_powitalna(lista);

    lista = clear(lista);
    return 0;
}

