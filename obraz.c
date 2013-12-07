#include "obraz.h"
#include "lista.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>

void inwersja(obraz *img)
{
    int width, height;

    if (img->rodzaj == 1)
    {
        for(height = 0; height < img->height; height++)
        {
            for (width = 0; width < img->width; width++)
            {
                if (img->dane[height][width])
                    img->dane[height][width] = 0;
                else
                    img->dane[height][width] = 1;
            }
        }
    }
    else
    {
        for(height = 0; height < img->height; height++)
        {
            for (width = 0; width < img->width; width++)
                img->dane[height][width] = img->color - img->dane[height][width];
        }
    }

    img->czy_zmieniane = 1;
    return;
}

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
