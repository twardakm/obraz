#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

element * clear(element *first)
{
    if (first == NULL)
        return NULL;
    clear(first->next);
    zwolnij_pamiec_obraz(first->img);
    free(first);

    return NULL;
}

element * position(element *first, int n)
{
    if (n >= size(first))
    {
        if (_DEBUG) printf("Rozmiar: %d\tn: %d\n", size(first), n);
        printf("Nie ma tylu elementów wczytanych do tablicy\n");
        return NULL;
    }
    else if(n <= 0)
    {
        printf("Niepoprawna liczba\n");
        return NULL;
    }
    for (n; n > 0; n--) first = first->next;

    if(_DEBUG) printf("Wybrano: %s", first->img->nazwa_pliku);
    return first;
}

element * push(element *first, element *newone)
{
    element * temp = first;
    if(first == NULL)
        return newone;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next=newone;
    return first;
}

int size(element *first)
{
    int i = 0;
    while(first != NULL)
    {
        i++;
        first = first->next;
    }
    return i;
}
