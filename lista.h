#ifndef LISTA_H
#define LISTA_H

#include "obraz.h"

typedef struct element
{
    struct element *next;
    obraz *img;
}element;

element * clear(element *first);
element * push(element * first, element * newone);
int size(element *first);

#endif // LISTA_H
