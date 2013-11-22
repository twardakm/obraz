#ifndef LISTA_H
#define LISTA_H

#include "obraz.h"

typedef struct element
{
    struct element *next;
    obraz *img;
}element;

element * push(element * first, element * newone);
void wyswietl(element * first);
element * clear(element *first);

#endif // LISTA_H
