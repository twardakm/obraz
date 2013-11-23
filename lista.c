#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


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

element * clear(element *first)
{
    if (first == NULL)
        return NULL;
    clear(first->next);
    free(first);

    return NULL;
}
