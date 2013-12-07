#ifndef LISTA_H
#define LISTA_H

#include "obraz.h"

typedef struct element
{
    struct element *next;
    struct obraz *img;
}element;

element * clear(element *first);
element * position(element *first, int n);
element * push(element * first, element * newone);
int size(element *first);
void wyswietl_wczytane_obrazy(element *first);

#endif // LISTA_H
