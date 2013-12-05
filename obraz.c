#include "obraz.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>

void wyswietl_obraz(obraz *img)
{
    if (img == NULL)
        return;
    printf("\n---------------\nWyswietlanie obrazu: %s\n---------------\n"
           "Rodzaj: P%d\tWysokość: %d\tSzerokość: %d\n"
           "Maksymalna wartość składowa koloru: %d\n---------------\n",
           img->nazwa_pliku, img->rodzaj, img->height, img->width, img->color);

    if (img->rodzaj == 1)
    {
        int wiersz, kolumna;

        for (wiersz = 0; wiersz < img->height; wiersz++)
        {
            for (kolumna = 0; kolumna < img->width; kolumna++)
            {
                if (img->dane[wiersz][kolumna] == 0)
                    printf("  ");
                else
                    printf("%c ", 35);
            }
            printf("\n");
        }
    }
}

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

int zwolnij_pamiec_obraz(obraz *img)
{
    int i;
    if (_DEBUG) printf("zwalnianie pamieci... ");
    free(img->nazwa_pliku);

    for(i = 0; i < img->height; i++)
        free(img->dane[i]);
    free(img->dane);

    if (_DEBUG) printf("OK\n");

    return FREE_MEM_OK;
}
