#include "obraz.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>

int zarezerwuj_pamiec_dane(obraz *img)
{
    int i;
    if (_DEBUG) printf("width: %d\n", img->width);
    if (_DEBUG) printf("height: %d\n", img->height);
    img->dane = (int **)malloc(sizeof(int *) * img->height);
    if(_DEBUG) printf("Zaalokowano y = %d\n", img->height);
    for(i = 0; i < img->height; i++)
        img->dane[i] = (int *)malloc(sizeof(int) * img->width);
    if(_DEBUG) printf("Zaalokowano x = %d\n", img->width);
    return MALLOC_OK;
}
